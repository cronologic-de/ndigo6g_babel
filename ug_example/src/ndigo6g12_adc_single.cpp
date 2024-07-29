#include "ndigo6g12_app.h"
#include <stdio.h>

// a simple application that measures the distance of two packets and computes
// the frequency of the signal
 double Ndigo6GAppSingle::ProcessADCPacket(crono_packet *pkt) {

    double fallingEdgeTs = ComputeFallingEdge(pkt);

    if (fallingEdgeTs > 0) {
        if (lastFallingEdgeTs > 0) {
            double packetRate = (1.0 / (fallingEdgeTs - lastFallingEdgeTs));
            double packetRateKHz = packetRate * 1e9;
            printf("ADC packet rate: %.3f kHz\n", packetRateKHz);
        }
        lastFallingEdgeTs = fallingEdgeTs;
    }
    return fallingEdgeTs;
}

void Ndigo6GAppSingle::ConfigureADC(ndigo6g12_configuration *config,
                                    int adcThreshold) {
    this->adcThreshold = adcThreshold;
    // single channel mode with 6.4 Gsps
    config->adc_mode = NDIGO6G12_ADC_MODE_A;

    // ADC sample value range -32768 .. 32767
    config->output_mode = NDIGO6G12_OUTPUT_MODE_SIGNED16;

    // enable ADC channel A and trigger on the falling edge of ADC data
    // shift baseline of analog inputs to +350 mV
    config->analog_offsets[0] = NDIGO6G12_DC_OFFSET_N_NIM * -1;

    // trigger on falling edge of ADC data
    config->trigger[NDIGO6G12_TRIGGER_A0].edge = true;
    config->trigger[NDIGO6G12_TRIGGER_A0].rising = false;
    config->trigger[NDIGO6G12_TRIGGER_A0].threshold = adcThreshold;

    // enable channel A
    config->trigger_block[0].enabled = true;
    // multiples of 32 ADC samples (5 ns recording time)
    config->trigger_block[0].length = 1;
    // multiples of 32 ADC samples, gets added to packet length

    config->trigger_block[0].precursor = PRECURSOR;

    // select ADC data as trigger source of the channel
    config->trigger_block[0].sources = NDIGO6G12_TRIGGER_SOURCE_A0;

}