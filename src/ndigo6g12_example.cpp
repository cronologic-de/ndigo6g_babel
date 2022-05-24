// ndigo6g12_example.cpp : Example application for the Ndigo6G-12
//
#include "ndigo6g12_interface.h"
#include "stdlib.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

ndigo6g12_device initialize_ndigo6g12(int buffer_size, int board_id,
                                      int card_index) {
    // prepare initialization
    ndigo6g12_init_parameters params;
    // fill initialization data structure with default values
    // so that the data is valid and only parameters
    // of interest have to be set explicitly
    ndigo6g12_get_default_init_parameters(&params);

    params.buffer_size[0] = buffer_size; // size of the packet buffer
    params.board_id = board_id; // value copied to "card" field of every packet,
                                // allowed range 0..255
    params.card_index = card_index; // which of the Ndigo6G-12 board found in
                                    // the system to be used

    // initialize card
    int error_code;
    const char *error_message;
    ndigo6g12_device device;
    error_code = ndigo6g12_init(&device, &params, &error_message);
    if (error_code != CRONO_OK) {
        printf("Could not init Ndigo6G-12: %s\n", error_message);
        ndigo6g12_close(&device);
        exit(1);
    }

    return device;
}

int configure_ndigo6g12(ndigo6g12_device *device, int adc_threshold,
                        bool enable_gating) {
    // prepare configuration
    ndigo6g12_configuration config;

    // fill configuration data structure with default values
    // so that the configuration is valid and only parameters
    // of interest have to be set explicitly
    if (CRONO_OK != ndigo6g12_get_default_configuration(device, &config)) {
        printf("Could not configure Ndigo6G-12: %s\n",
               ndigo6g12_get_last_error_message(device));
        ndigo6g12_close(device);
        return 1;
    }

    //*********************************************************************************************
    // configuration for the TDC channels

    // enable TDC channels
    for (int i = 0; i < NDIGO6G12_TDC_CHANNEL_COUNT; i++) {
        config.tdc_trigger_offsets[i] =
            NDIGO6G12_DC_OFFSET_N_NIM; // for NIM pulses: trigger at -350 mV

        config.tdc_configuration.channel[i].enable = true; // enable TDC channel
        config.tdc_configuration.channel[i].rising =
            false; // trigger on falling edges

        // enable falling edge trigger as input to trigger matrix for selected
        // TDC channel only required if used as trigger source for Gating, TiGer
        // or ADC trigger blocks
        config.trigger[NDIGO6G12_TRIGGER_TDC0 + i].edge = true;
        config.trigger[NDIGO6G12_TRIGGER_TDC0 + i].rising = false;
        // threshold not applicable for TDC inputs
        // trigger threshold is set via tdc_trigger_offsets[i]
        config.trigger[NDIGO6G12_TRIGGER_TDC0 + i].threshold = 0;
    }

    if (enable_gating) {
        // Enable gates for TDC channels 1 to 3
        // TDC channel 0 is used as trigger source
        // to control the gating.
        for (int i = 1; i < NDIGO6G12_TDC_GATE_COUNT; i++) {
            // open Gate for approx. 150 ns
            // starting 50 ns after a falling edge
            // is detected on TDC input 0
            config.tdc_configuration.gating_block[i].enable = true;
            config.tdc_configuration.gating_block[i].sources =
                NDIGO6G12_TRIGGER_SOURCE_TDC0;
            config.tdc_configuration.gating_block[i].start = 10;
            config.tdc_configuration.gating_block[i].stop = 40;
            config.tdc_configuration.gating_block[i].negate = false;
        }
    }

    //*********************************************************************************************
    // configuration for the ADC channels

    // single channel mode with 6.4 Gsps
    config.adc_mode = NDIGO6G12_ADC_MODE_A;

    // sample value range: -2048 .. 2048
    config.output_mode = NDIGO6G12_OUTPUT_MODE_SIGNED16;

    // enable ADC channel A and trigger on the falling edge
    // shift baseline of analog inputs to +350 mV
    config.analog_offsets[0] = NDIGO6G12_DC_OFFSET_N_NIM * -1;

    // trigger on falling edge of ADC data
    config.trigger[NDIGO6G12_TRIGGER_A0].edge = true;
    config.trigger[NDIGO6G12_TRIGGER_A0].rising = false;
    config.trigger[NDIGO6G12_TRIGGER_A0].threshold = adc_threshold;

    // enable channel
    config.trigger_block[0].enabled = true;
    // multiples of 32 ADC samples (5 ns recording time)
    config.trigger_block[0].length = 1;
    // multiples of 32 ADC samples, gets added to packet length
    config.trigger_block[0].precursor = 1;

    // select ADC data as trigger source of the channel
    config.trigger_block[0].sources = NDIGO6G12_TRIGGER_SOURCE_A0;

    if (enable_gating) {
        // use GATE 0 to control data recording
        config.trigger_block[0].gates = NDIGO6G12_TRIGGER_GATE_0;

        // open ADC GATE 0 for approx. 150 ns
        // starting 50 ns after a falling edge
        // is detected on TDC input 0
        config.gating_block[0].sources = NDIGO6G12_TRIGGER_SOURCE_TDC0;
        config.gating_block[0].start = 10;
        config.gating_block[0].stop = 40;
        config.gating_block[0].negate = false;
    } else {
        config.trigger_block[0].gates = NDIGO6G12_TRIGGER_GATE_NONE;
    }

    // write configuration to board
    int error_code = ndigo6g12_configure(device, &config);
    if (error_code != CRONO_OK) {
        printf("Could not configure Ndigo6G-12: %s\n",
               ndigo6g12_get_last_error_message(device));
        return (1);
    }
    return 0;
}

// print some basic information about the Ndigo6G-12 device
void print_device_information(ndigo6g12_device *device) {
    ndigo6g12_static_info si;
    ndigo6g12_get_static_info(device, &si);
    printf("Firmware revision %d.%d - Type %d\n", si.fw_revision,
           si.svn_revision, si.application_type);
    printf("Firmware Bitstream Timestamp : %s\n", si.bitstream_date);
    printf("Calibration date             : %s\n", si.calibration_date);
    printf("Board serial                 : %d.%d\n", si.board_serial >> 24,
           si.board_serial & 0xffffff);
    printf("Board revision               : %d\n", si.board_revision);
    printf("Board configuration          : %d\n", si.board_configuration);
    printf("Driver Revision              : %d.%d.%d\n",
           ((si.driver_revision >> 16) & 255),
           ((si.driver_revision >> 8) & 255), (si.driver_revision & 255));
    printf("Driver Build Revision        : %d\n", si.driver_build_revision);

    ndigo6g12_fast_info fi;
    ndigo6g12_get_fast_info(device, &fi);
    printf("TDC temperature              : %.2f C\n", fi.tdc1_temp);
    printf("ADC temperature              : %.2f C\n", fi.ev12_temp);
    printf("FPGA temperature             : %.2f C\n", fi.fpga_temperature);
    printf("PCIe link speed              : Gen. %d\n", fi.pcie_link_speed);
    printf("PCIe link width              : %d lanes\n", fi.pcie_link_width);
    printf("PCIe payload                 : %d bytes\n", fi.pcie_max_payload);

    ndigo6g12_param_info pi;
    ndigo6g12_get_param_info(device, &pi);
    printf("Sample rate                  : %.0f Msps\n",
           pi.sample_rate / 1000000.0);
    printf("Resolution                   : %d Bit\n", pi.resolution);
    printf("Sample period                : %.2f ps\n", pi.sample_period);
    printf("TDC bin size                 : %.2f ps\n", pi.tdc_period);
    printf("Packet Timestamp period      : %.2f ps\n", pi.packet_ts_period);
    printf("ADC Sample delay             : %.2f ps\n", pi.adc_sample_delay);
}

int ProcessADCPacket(volatile crono_packet *pkt, ndigo6g12_param_info *pi,
                     int threshold) {
    // calculate packet timestamp in picoseconds
    // not adjusted for ADC data precursor
    double packet_ts = pkt->timestamp * pi->packet_ts_period;

    printf("ADC packet - TS: %.3f ns\r\n", (packet_ts / 1000.0));

    // packet length is number of 64 bit words of data
    // 4 ADC samples are stored in each 64 bit chunk of packet data
    uint32_t sample_count = (pkt->length * 4);

    // ADC data is a signed 16 bit integer
    int16_t *adc_data = (int16_t *)(pkt->data);

    // find first falling edge in ADC data
    for (uint32_t i = 0; i < (sample_count - 1); i++) {
        if ((adc_data[i] >= threshold) && (adc_data[i + 1] < threshold)) {
            // calculate threshold crossing relative to start of packet
            double fe_offset = i;
            // linear interpolation of trigger threshold crossing
            fe_offset += (double)(adc_data[i] - threshold) /
                         (adc_data[i] - adc_data[i + 1]);
            // convert to picoseconds
            fe_offset *= pi->sample_period;

            // calculate timestamp of threshold crossing in picoseconds
            double falling_edge_ts = packet_ts + fe_offset;
            // adjust for ADC pipeline delay
            falling_edge_ts -= pi->adc_sample_delay;

            printf("ADC packet falling edge event - TS: %.3f ns\r\n",
                   (falling_edge_ts / 1000.0));
            break;
        }
    }
    printf("\n");
    return 0;
}

int ProcessTDCPacket(volatile crono_packet *pkt, ndigo6g12_param_info *pi) {
    // TDC packet timestamp relates to end of packet
    // adjust for timespan covered
    double packet_ts =
        (double)(pkt->timestamp - pi->tdc_packet_timestamp_offset);
    // calculate packet timestamp in picoseconds
    packet_ts *= pi->packet_ts_period;

    // packet length is number of 64 bit words of data
    // 2 TDC events are stored in each 64 bit chunk of packet data
    uint32_t tdc_event_cnt = pkt->length * 2;

    printf("TDC packet with %d events (may include rollover) - TS: %.3f ns\r\n",
           tdc_event_cnt, (packet_ts / 1000.0));

    // event encoding:
    // Bits 31 downto 8: event timestamp in TDC bins relative to packet
    // timestamp Bits  7 downto 4: event flags Bits  3 downto 0: channel number
    uint32_t *tdc_event_data = (uint32_t *)(pkt->data);

    // each TDC packet covers up to 3 coarse TDC periods
    // the end of one period is marked by an event on channel 15
    uint32_t rollover_era = 0;

    // print all TDC timestamps of the packet
    for (uint32_t i = 0; i < tdc_event_cnt; i++) {
        // TDC channel number
        // 0 - 3: LEMO inputs
        // 15: internal marker: end of current TDC time frame
        uint32_t tdc_channel = tdc_event_data[i] & 0xf;
        // event flags
        uint32_t flags = (tdc_event_data[i] >> 4) & 0xf;
        // 24 bit timestamp
        uint32_t event_ts = tdc_event_data[i] >> 8;

        // valid input channel?
        if (tdc_channel < 4) {
            // add accumulated rollovers since start of packet
            event_ts += rollover_era;
            // calculate timestamp of TDC event in picoseconds
            double edge_ts_ps = event_ts * pi->tdc_period;
            edge_ts_ps += packet_ts;
            printf("TDC event on channel %d - TS: %.3f ns\r\n", tdc_channel,
                   edge_ts_ps / 1000.0);
        }

        if (tdc_channel == 14) {
            // dummy data, can be ignored
        }

        // rollover marker
        if (tdc_channel == 15) {
            rollover_era += pi->tdc_rollover_period;
        }
    }
    printf("\n");
    return 0;
}

int main(int argc, char *argv[]) {
    // use 128 MB to buffer incoming data
    // largest ADC data packet has about 500 KiByte
    const int64_t BUFFER_SIZE = 128 * 1024 * 1024;

    // use first Ndigo6G-12 device found in the system
    const int CARD_INDEX = 0;

    // set board id in all packets to 0
    // can be used to distinguish packets of multiple devices
    const int BOARD_ID = 0;

    printf("cronologic ndigo6g12_example using driver: %s\n",
           ndigo6g12_get_driver_revision_str());

    // create and initialize the device
    // may fail if the device is already in use by an other process
    // or the device driver is not installed
    ndigo6g12_device device =
        initialize_ndigo6g12(BUFFER_SIZE, BOARD_ID, CARD_INDEX);

    print_device_information(&device);

    // set the configuration required for capturing data
    int adc_threshold = 0;
    bool enable_gating = false;
    int status = configure_ndigo6g12(&device, adc_threshold, enable_gating);

    // configure readout behaviour
    // automatically acknowledge all data as processed
    // on the next call to ndigo6g12_read()
    // old packet pointers are invalid after calling ndigo6g12_read()
    ndigo6g12_read_in read_config;
    read_config.acknowledge_last_read = 1;

    // structure with packet pointers for read data
    ndigo6g12_read_out read_data;

    // start data capture
    status = ndigo6g12_start_capture(&device);
    if (status != CRONO_OK) {
        printf("Could not start capturing: %s",
               ndigo6g12_get_last_error_message(&device));
        ndigo6g12_close(&device);
        return status;
    }

    // get current sample rate to calculate event timestamps
    ndigo6g12_param_info param_info;
    ndigo6g12_get_param_info(&device, &param_info);

    // some book keeping
    int packet_count = 0;
    // ADC data is provided in packets, one packet per ADC channel and trigger
    // TDC data is provided in a singe packet for all TDC inputs in a certain
    // timespan
    int pkt_cnt[5];
    for (int i = 0; i < 5; i++) {
        pkt_cnt[i] = 0;
    }

    printf("\nReading packets:\n");

    const int PACKET_COUNT = 10;
    while ((packet_count < PACKET_COUNT)) {
        // get pointers to acquired packets
        status = ndigo6g12_read(&device, &read_config, &read_data);
        if (status != CRONO_OK) {
            Sleep(200);
            printf(" - No data! -\n");
        } else {
            // iterate over all packets received with the last read
            volatile crono_packet *p = read_data.first_packet;
            while (p <= read_data.last_packet) {
                if (p->channel < 5)
                    pkt_cnt[p->channel]++;

                if (p->channel < 4) {
                    // packets with channel number < 4 are ADC data
                    ProcessADCPacket(p, &param_info, adc_threshold);
                } else {
                    // packets with channel number 4 are TDC data
                    ProcessTDCPacket(p, &param_info);
                }

                // go to next packet
                p = crono_next_packet(p);

                packet_count++;
            } // end: iterate over received packets
        }     // end: Got any packets?
    }         // end: while

    // shut down packet generation and DMA transfers
    ndigo6g12_stop_capture(&device);

    // deactivate Ndigo6G-12
    ndigo6g12_close(&device);

    return 0;
}