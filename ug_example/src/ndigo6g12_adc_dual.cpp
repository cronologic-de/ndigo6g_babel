#include "ndigo6g12_app.h"
#include <stdio.h>
#include <cmath>


// an application that measure the delay between a signal on start (A)
// to stop (D)
double Ndigo6GAppDual::ProcessADCPacket(crono_packet *pkt) {

    double falling_edge_ts = ComputeFallingEdge(pkt);

    // gather data
    if (falling_edge_ts > 0) {
        delayMeasure.InsertTimestamp(pkt->channel, falling_edge_ts);
    }
    Delays *delays = delayMeasure.MeasureDelays();

    delayMeasure.PrintDelays(delays);

    return falling_edge_ts;
}
void Ndigo6GAppDual::ProcessTDCTimestamp(int tdcChannel, double timestamp) {
    //TDC channels are mapped as 4-7
    delayMeasure.InsertTimestamp(4 + tdcChannel, timestamp);

    Delays *delays = delayMeasure.MeasureDelays();

    delayMeasure.PrintDelays(delays);
}


void Ndigo6GAppDual::ConfigureADC(ndigo6g12_configuration *config,
                                     int adcThreshold) {
    this->adcThreshold = adcThreshold;
    // dual channel mode with 3.2 Gsps
    config->adc_mode = NDIGO6G12_ADC_MODE_AD;

    // ADC sample value range -32768 .. 32767
    config->output_mode = NDIGO6G12_OUTPUT_MODE_SIGNED16;

    // enable ADC channel A and trigger on the falling edge of ADC data
    // shift baseline of analog inputs to +350 mV
    // do the same for channel D
    config->analog_offsets[0] = NDIGO6G12_DC_OFFSET_N_NIM * -1;
    config->analog_offsets[3] = NDIGO6G12_DC_OFFSET_N_NIM * -1;

    // trigger on falling edge of ADC data
    config->trigger[NDIGO6G12_TRIGGER_A0].edge = true;
    config->trigger[NDIGO6G12_TRIGGER_A0].rising = false;
    config->trigger[NDIGO6G12_TRIGGER_A0].threshold = adcThreshold;
    config->trigger[NDIGO6G12_TRIGGER_D0].edge = true;
    config->trigger[NDIGO6G12_TRIGGER_D0].rising = false;
    config->trigger[NDIGO6G12_TRIGGER_D0].threshold = adcThreshold;

    // enable channel A
    config->trigger_block[0].enabled = true;
    // multiples of 16 ADC samples (5 ns recording time)
    config->trigger_block[0].length = 1;
    // multiples of 16 ADC samples, gets added to packet length

    config->trigger_block[0].precursor = PRECURSOR;

    // select ADC data as trigger source of the channel
    config->trigger_block[0].sources = NDIGO6G12_TRIGGER_SOURCE_A0;

    // enable channel D
    config->trigger_block[3].enabled = true;
    // multiples of 16 ADC samples (5 ns recording time)
    config->trigger_block[3].length = 1;
    // multiples of 16 ADC samples, gets added to packet length

    config->trigger_block[3].precursor = PRECURSOR;

    // select ADC data as trigger source of the channel
    config->trigger_block[3].sources = NDIGO6G12_TRIGGER_SOURCE_D0;
}