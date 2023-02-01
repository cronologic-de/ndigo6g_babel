// ndigo6g12_averager_example.cpp
// Example application for the Ndigo6G-12 Averager
//
#include "ndigo6g12_interface.h"
#include "stdlib.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

// initialize Ndigo6G-12 Averager device
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
    params.card_index = card_index; // which of the Ndigo6G-12 Averager board
                                    // found in the system to be used

    // initialize card
    int error_code;
    const char *error_message;
    ndigo6g12_device device;
    error_code = ndigo6g12_init(&device, &params, &error_message);
    if (error_code != CRONO_OK) {
        printf("Could not init Ndigo6G-12 Averager: %s\n", error_message);
        ndigo6g12_close(&device);
        exit(1);
    }

    // check if firmware supports Averager mode
    ndigo6g12_static_info si;
    ndigo6g12_get_static_info(&device, &si);
    if (si.application_type != 5) {
        printf(
            "Installed Ndigo6G-12 firmware does not support Averager mode.\n");
        ndigo6g12_close(&device);
        exit(1);
    }

    return device;
}

int configure_ndigo6g12(ndigo6g12_device *device, int averaging_count) {
    // prepare configuration
    ndigo6g12_configuration config;

    // fill configuration data structure with default values
    // so that the configuration is valid and only parameters
    // of interest have to be set explicitly
    if (CRONO_OK != ndigo6g12_get_default_configuration(device, &config)) {
        printf("Could not get default configuration: %s\n",
               ndigo6g12_get_last_error_message(device));
        ndigo6g12_close(device);
        return 1;
    }

    //*********************************************************************************************
    // configuration for the ADC channel

    // single channel mode with 6.4 Gsps
    config.adc_mode = NDIGO6G12_ADC_MODE_A;

    // ADC sample value range -32768 .. 32767
    // averating data saturates at +/- 2^21 - 1
    config.output_mode = NDIGO6G12_OUTPUT_MODE_SIGNED32;

    // enable ADC channel A and trigger on the falling edge of FPGA0 input
    // shift baseline of analog inputs to +350 mV
    config.analog_offsets[0] = NDIGO6G12_DC_OFFSET_N_NIM * -1;

    // trigger on falling edge of FPGA0 input
    config.trigger[NDIGO6G12_TRIGGER_FPGA0].edge = true;
    config.trigger[NDIGO6G12_TRIGGER_FPGA0].rising = false;
    // config.trigger[NDIGO6G12_TRIGGER_FPGA0].threshold is not applicable for
    // TDC[0..3]/FPGA0/FPGA1 inputs

    // set trigger level on FPGA0 input to -350 mV
    config.tdc_trigger_offsets[NDIGO6G12_TIGER_FPGA0] =
        NDIGO6G12_DC_OFFSET_N_NIM;

    // enable channel
    config.trigger_block[0].enabled = true;
    // multiples of 32 ADC samples (5 ns recording time)
    config.trigger_block[0].length = 32764;

    // select FPGA0 as trigger source of the channel
    config.trigger_block[0].sources = NDIGO6G12_TRIGGER_SOURCE_FPGA0;

    // enable tiger output with autotrigger as source
    config.tdc_configuration.tiger_block[NDIGO6G12_TIGER_FPGA0].sources =
        NDIGO6G12_TRIGGER_SOURCE_AUTO;

    // 1 kHz pulse interval
    config.auto_trigger_period = 200000;
    // disable random pulse interval
    config.auto_trigger_random_exponent = 0;

    // configuration of the Averaging features

    // number of events that are averaged
    config.average_configuration.iterations = averaging_count;

    // saturate averaging data instead of overflow
    config.average_configuration.use_saturation = true;

    // don't stop averaging if next iteration could lead to sample data overflow
    config.average_configuration.stop_on_overflow = false;

    // write configuration to board
    int error_code = ndigo6g12_configure(device, &config);
    if (error_code != CRONO_OK) {
        printf("Could not configure Ndigo6G-12 Averager: %s\n",
               ndigo6g12_get_last_error_message(device));
        return 1;
    }
    return 0;
}

// print some basic information about the Ndigo6G-12 Averager device
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

double ProcessPacket(volatile crono_packet *pkt, ndigo6g12_param_info *pi) {
    // calculate packet timestamp in picoseconds
    // not adjusted for ADC data precursor
    double packet_ts = pkt->timestamp * pi->packet_ts_period;

    printf("\nPacket timestamp: %.3f ns\n", (packet_ts / 1000.0));

    // packet length is number of 64 bit words of data
    // the first two 64 bit packet data words are additional header information
    uint32_t data_offset = 2;
    // only the first currently carries valid information
    uint64_t averaging_header0 = *(pkt->data);

    // if bit is set less than the requested number of iterations have been
    // performed before writing the packet due to possible data overflow on the
    // next iteration
    bool stopped_due_to_overflow = (averaging_header0 >> 32) & 0x1;

    // if bit is set the averaged data contains saturated or overflowed samples
    // does NOT indicate that the input signal has not exceeded the ADC range
    bool averaging_overflow = (averaging_header0 >> 32) & 0x2;

    // number of iterations, may be less than requested
    int iterations_performed = (averaging_header0 & 0xffffff);
    printf("Averaging iterations: %d\n", iterations_performed);

    // 2 averaged ADC samples are stored in each 64 bit chunk of packet data
    uint32_t sample_count = ((pkt->length - data_offset) * 2);

    // ADC data is a signed 32 bit integer
    int32_t *adc_data = (int32_t *)(pkt->data + data_offset);

    // find first falling edge in Averaging data
    for (uint32_t i = 0; i < (sample_count - 1); i++) {
        if ((adc_data[i] >= 0) && (adc_data[i + 1] < 0)) {
            // calculate threshold crossing relative to start of packet
            double fe_offset = i;
            // linear interpolation of trigger threshold crossing
            fe_offset +=
                (double)(adc_data[i] - 0) / (adc_data[i] - adc_data[i + 1]);
            // calculate timestamp of threshold crossing in picoseconds
            fe_offset *= pi->sample_period;

            printf("Falling edge event - offset to packet start: %.3f ns\n",
                   (fe_offset / 1000.0));
            break;
        }
    }
    return packet_ts;
}

int main(int argc, char *argv[]) {
    // use 128 MiByte to buffer incoming data
    // largest Averaging data packet has about 4 MiByte
    const int64_t BUFFER_SIZE = 128 * 1024 * 1024;

    // use the first Ndigo6G-12 Averager device found in the system
    const int CARD_INDEX = 0;

    // set board id in all packets to 0
    // can be used to distinguish packets of multiple devices
    const int BOARD_ID = 0;

    printf("cronologic ndigo6g12_averager_example using driver: %s\n",
           ndigo6g12_get_driver_revision_str());

    // create and initialize the device
    // may fail if the device is already in use by an other process
    // or the device driver is not installed
    ndigo6g12_device device =
        initialize_ndigo6g12(BUFFER_SIZE, BOARD_ID, CARD_INDEX);

    print_device_information(&device);

    // set the configuration required for capturing data
    int averaging_count = 16; // average 16 trigger events

    int status = configure_ndigo6g12(&device, averaging_count);
    if (status != 0) {
        exit(1);
    }

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
        exit(1);
    }

    // get current sample rate to calculate event timestamps
    ndigo6g12_param_info param_info;
    ndigo6g12_get_param_info(&device, &param_info);

    // some book keeping
    // Averaging data is provided in a single packet
    int packet_count = 0;
    double last_packet_timestamp = 0;

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
                if (p->channel == 0) {
                    // packets with channel number 0 are Averaging data
                    double packet_ts = ProcessPacket(p, &param_info);
                    if (last_packet_timestamp > 0) {
                        double packet_rate =
                            (1.0 / (packet_ts - last_packet_timestamp));
                        double packet_rate_kHz =
                            packet_rate * 1000 * 1000 * 1000;
                        printf("Packet rate: %.3f kHz\n", packet_rate_kHz);
                    }
                    last_packet_timestamp = packet_ts;
                }

                // go to next packet
                p = crono_next_packet(p);

                packet_count++;
            } // end: iterate over received packets
        }     // end: Got any packets?
    }         // end: while

    // shut down packet generation and DMA transfers
    ndigo6g12_stop_capture(&device);

    // deactivate Ndigo6G-12 Averager
    ndigo6g12_close(&device);

    return 0;
}