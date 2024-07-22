#include "ndigo6g12_app.h"
#include <stdio.h>
#include <cmath>
#include <array>


// an application that measures the delay between a start signal (A)
// stop signals on channels B-D
double Ndigo6GAppQuad::ProcessADCPacket(crono_packet *pkt) {

    double falling_edge_ts = ComputeFallingEdge(pkt);

    // gather data
    if (falling_edge_ts > 0) {
        delayMeasure.InsertTimestamp(pkt->channel, falling_edge_ts);
    }

    Delays *delays = delayMeasure.MeasureDelays();

    delayMeasure.PrintDelays(delays);

    return falling_edge_ts;
}

void Ndigo6GAppQuad::ProcessTDCTimestamp(int tdcChannel, double timestamp) {
    // insert TDC as channel 4-7
    delayMeasure.InsertTimestamp(4 + tdcChannel, timestamp);

    Delays *delays = delayMeasure.MeasureDelays();

    delayMeasure.PrintDelays(delays);
}

void Ndigo6GAppQuad::ConfigureADC(ndigo6g12_configuration *config,
                                  int adcThreshold) {
    this->adcThreshold = adcThreshold;
    // quad channel mode with 1.6 Gsps
    config->adc_mode = NDIGO6G12_ADC_MODE_ABCD;

    // ADC sample value range -32768 .. 32767
    config->output_mode = NDIGO6G12_OUTPUT_MODE_SIGNED16;
    // trigger on falling edge of ADC data
    for (int index : {NDIGO6G12_TRIGGER_A0, NDIGO6G12_TRIGGER_B0,
                      NDIGO6G12_TRIGGER_C0, NDIGO6G12_TRIGGER_D0}) {
        config->trigger[index].edge = true;
        config->trigger[index].rising = false;
        config->trigger[index].threshold = adcThreshold;
    }

    // the sources of each channel (they should trigger on the input data 
    // of the channel)
    std::array<int, 4> sources = {
        NDIGO6G12_TRIGGER_SOURCE_A0, NDIGO6G12_TRIGGER_SOURCE_B0,
        NDIGO6G12_TRIGGER_SOURCE_C0, NDIGO6G12_TRIGGER_SOURCE_D0};

    // enable ADC channels A-D and trigger on the falling edge of ADC data
    // shift baseline of analog inputs to +350 mV
    for (int c = 0; c < 4; c++) {
        config->analog_offsets[c] = NDIGO6G12_DC_OFFSET_N_NIM * -1;

        // enable channel 
        config->trigger_block[c].enabled = true;

        // in multiples of 8 ADC samples (5 ns recording time) after trigger
        config->trigger_block[c].length = 1;

        // in multiples of 8 ADC samples, gets added to packet length
        config->trigger_block[c].precursor = PRECURSOR;

        // select ADC data as trigger source of the channel
        config->trigger_block[c].sources = sources[c];
    }
}