// Example application for the Ndigo6G-12
//
#include "ndigo6g12_app.h"
#include "ndigo6g12_interface.h"
#include <map>
#include <stdio.h>
#include <stdlib.h>

std::map<int, std::string> appTypeMap = {{1, "One ADC channels @6.4 Gsps"},
                                         {2, "Two ADC channels @3.2 Gsps"},
                                         {4, "Four ADC channels @1.6 Gsp"},
                                         {5, "Averaging mode @6.4 Gsps"}};

std::map<int, std::string> requirementsMap = {
    {0,
     "Starts the test of the currently configured app type"},
    {1,
     "Measure time distance between passing of "
        "threshold, calculates the frequency, requires NIM signal on channel A"},
    {2, "Dual channel application that measures delay between start "
        "pulse on channel A and stop pulse on channel D (NIM)"},
    {4, "Quad channel application that measures delay between start "
        "pulse on channel A and stop pulses on channels B-D (NIM)"},
    {5, "Measure time distance between averaged start on FPGA0 (NIM) and stop on channel A(falling) by summing data of 16 runs,"
        "to increase precision of measurement for signal with low amplitude"}};

Ndigo6GApp *adcApp;
ndigo6g12_param_info paramInfo;

// initialize Ndigo6G-12 device
ndigo6g12_device initialize_ndigo6g12(int bufferSize, int boardId,
                                      int cardIndex, int appType, int tdcChannels) {
    // prepare initialization
    ndigo6g12_init_parameters params;
    // fill initialization data structure with default values
    // so that the data is valid and only parameters
    // of interest have to be set explicitly
    ndigo6g12_get_default_init_parameters(&params);
    params.application_type = appType;

    params.buffer_size[0] = bufferSize; // size of the packet buffer
    params.board_id = boardId; // value copied to "card" field of every packet,
                               // allowed range 0..255
    params.card_index = cardIndex; // which of the Ndigo6G-12 board found in
                                   // the system to be used
    // this specifies the directories or the specific .cronorom if dynamic
    // switching of appType is required, if not specified the example will
    // return an error, if the appType does not match the current appType in the
    // firmware 
    params.firmware_locations =
        "//diskstation/cronologic/RudolfJ/cronorom/current";

    // initialize card
    int errorCode;
    const char *errorMessage;
    ndigo6g12_device device;
    errorCode = ndigo6g12_init(&device, &params, &errorMessage);

    if (errorCode != CRONO_OK) {
        printf("Could not init Ndigo6G-12: %s\n", errorMessage);
        printf("Please change path to the .cronorom in ndigo6g12_example.cpp\n");
        exit(1);
    }

    // check if firmware now supports the chose application type
    ndigo6g12_static_info si;
    ndigo6g12_get_static_info(&device, &si);
    if (si.application_type != appType) {
        printf("The switch to appType did not work, please make sure that that "
               "the firmware file is provided");
        ndigo6g12_close(&device);
        exit(1);
    }
    if (appType == 0) {
        appType = si.application_type;
    }
    switch (appType) {
    case 1:
        adcApp = new Ndigo6GAppSingle(tdcChannels);
        break;
    case 2:
        adcApp = new Ndigo6GAppDual(tdcChannels);
        break;
    case 4:
        adcApp = new Ndigo6GAppQuad(tdcChannels);
        break;
    case 5:
        adcApp = new Ndigo6GAppAverager(tdcChannels);
        break;
    default:
        printf("Not supported appType %d'\n", appType);
        ndigo6g12_close(&device);
        exit(1);
    }
    printf("Running in %s\n%s\n", appTypeMap[appType].c_str(),
           requirementsMap[appType].c_str());
    return device;
}

int configure_ndigo6g12(ndigo6g12_device *device, int adcThreshold) {
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
    // configuration for the TDC channels
    adcApp->ConfigureTDC(&config);

    //*********************************************************************************************
    // configuration for the ADC channels
    adcApp->ConfigureADC(&config, adcThreshold);

    // write configuration to board
    int error_code = ndigo6g12_configure(device, &config);
    if (error_code != CRONO_OK) {
        printf("Could not configure Ndigo6G-12: %s\n",
               ndigo6g12_get_last_error_message(device));
        return 1;
    }
    ndigo6g12_get_param_info(device, &paramInfo);
    adcApp->SetParamInfo(&paramInfo);
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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ndigo6g12_example <appType> [<tdcMask>]\n");
        for (auto atPair : appTypeMap) {
            int at = atPair.first;
            printf("AppType %d: %s\n  %s\n", at, appTypeMap[at].c_str(),
                   requirementsMap[at].c_str());
        }
        printf("tdcMask: Bit flag for TDC channels E-H\n");
        exit(1);
    }
    
    int appType = atoi(argv[1]);
    int tdcChannelMask = 0;
    if (argc > 2) {
        tdcChannelMask = atoi(argv[2]);    
    }
    // use 128 MiByte to buffer incoming data
    // largest ADC data packet has about 500 KiByte
    const int64_t BUFFER_SIZE = 128 * 1024 * 1024;

    // use the first Ndigo6G-12 device found in the system
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
        initialize_ndigo6g12(BUFFER_SIZE, BOARD_ID, CARD_INDEX, appType, tdcChannelMask);

    print_device_information(&device);

    // set the configuration required for capturing data
    // the base line is shifted by +350mV, target is to trigger at the middle of the NIM pulse edge
    int adcThreshold = 0;
    int status = configure_ndigo6g12(&device, adcThreshold);
    if (status != 0) {
        exit(1);
    }

    // configure readout behaviour
    // automatically acknowledge all data as processed
    // on the next call to ndigo6g12_read()
    // old packet pointers are invalid after calling ndigo6g12_read()
    ndigo6g12_read_in readConfig;
    readConfig.acknowledge_last_read = 1;

    // structure with packet pointers for read data
    ndigo6g12_read_out readData;

    // start data capture
    status = ndigo6g12_start_capture(&device);
    if (status != CRONO_OK) {
        printf("Could not start capturing: %s",
               ndigo6g12_get_last_error_message(&device));
        ndigo6g12_close(&device);
        exit(1);
    }

    // get current sample rate to calculate event timestamps
    ndigo6g12_param_info paramInfo;
    ndigo6g12_get_param_info(&device, &paramInfo);

    // ADC data is provided in packets, one packet per ADC channel and trigger
    // TDC data is provided in a single packet for all TDC inputs in a certain
    // timespan
    printf("\nReading packets:\n");

    const int MAX_PACKET_COUNT = 70;
    int packetCount = 0;
    bool noDataLastTime = false;
    while ((packetCount < MAX_PACKET_COUNT)) {
        // get pointers to acquired packets
        status = ndigo6g12_read(&device, &readConfig, &readData);
        if (status != CRONO_OK) {
            if (!noDataLastTime) {
                printf(" - No data! -\n");
            }
            noDataLastTime = true;

        } else {
            noDataLastTime = false;
            // iterate over all packets received with the last read
            volatile crono_packet *p = readData.first_packet;
            while (p <= readData.last_packet) {

                if (p->channel < 4) {
                    // packets with channel number < 4 are ADC data
                    double packet_ts =
                        adcApp->ProcessADCPacket(const_cast<crono_packet *>(p));
                } else {
                    // packets with channel number 4 are TDC data
                    adcApp->ProcessTDCPacket(const_cast<crono_packet *>(p));
                }

                // go to next packet
                p = crono_next_packet(p);

                packetCount++;
            } // end: iterate over received packets
        }     // end: Got any packets?
    }         // end: while

    // shut down packet generation and DMA transfers
    ndigo6g12_stop_capture(&device);

    // deactivate Ndigo6G-12
    ndigo6g12_close(&device);

    return 0;
}