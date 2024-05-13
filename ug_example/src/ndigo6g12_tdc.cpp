#include <stdio.h>
#include "ndigo6g12_app.h"

void Ndigo6GApp::ProcessTDCPacket(crono_packet *pkt) {
    // TDC packet timestamp relates to end of packet
    // adjust for timespan covered
    double packetTs =
        (double)(pkt->timestamp - pi->tdc_packet_timestamp_offset);

    // calculate packet timestamp in picoseconds
    packetTs *= pi->packet_ts_period;

    // packet length is number of 64 bit words of data
    // 2 TDC events are stored in each 64 bit chunk of packet data
    uint32_t tdcEventCount = pkt->length * 2;


    // event encoding:
    // Bits 31 downto 8: event timestamp in TDC bins relative to packet
    // timestamp Bits  7 downto 4: event flags Bits  3 downto 0: channel number
    uint32_t *tdcEventData = (uint32_t *)(pkt->data);

    // each TDC packet covers up to 3 coarse TDC periods
    // the end of one period is marked by an event on channel 15
    uint32_t rolloverEra = 0;
    // print all TDC timestamps of the packet
    for (uint32_t i = 0; i < tdcEventCount; i++) {
        // TDC channel number
        // 0 - 3: LEMO inputs
        // 15: internal marker: end of current TDC time frame
        uint32_t tdcChannel = tdcEventData[i] & 0xf;
        // event flags
        uint32_t flags = (tdcEventData[i] >> 4) & 0xf;
        // 24 bit timestamp
        uint32_t event_ts = tdcEventData[i] >> 8;

        // valid input channel?
        if (tdcChannel < 4) {
            // add accumulated rollovers since start of packet
            event_ts += rolloverEra;
            // calculate timestamp of TDC event in picoseconds
            double edgeTsPs = event_ts * pi->tdc_period;
            edgeTsPs += packetTs;
            ProcessTDCTimestamp(tdcChannel, edgeTsPs);
            printf("TDC event on channel %d timestamp: packet without "
                        "shift %.3f ns, "
                "with shift %.3f ns, edge %.3f ns  \n",
                   tdcChannel, (double)(pkt->timestamp * pi->packet_ts_period) / 1000.0,
                   packetTs / 1000., edgeTsPs / 1000.);

        }

        if (tdcChannel == 14) {
            // dummy data, can be ignored
        }

        // rollover marker
        if (tdcChannel == 15) {
            rolloverEra += pi->tdc_rollover_period;
        }
    }
}

void Ndigo6GApp::ConfigureTDC(ndigo6g12_configuration *config) {
    // enable TDC channels
    for (int i = 0; i < NDIGO6G12_TDC_CHANNEL_COUNT; i++) {
        // for NIM pulses: trigger at -350 mV
        config->tdc_trigger_offsets[i] = NDIGO6G12_DC_OFFSET_N_NIM ;

        // enable TDC channel
        config->tdc_configuration.channel[i].enable = (tdcChannelMask & (1<<i)) != 0;
        // trigger on falling edges
        config->tdc_configuration.channel[i].rising = false;

        // enable falling edge trigger as input to trigger matrix for selected
        // TDC channel only required if used as trigger source for Gating, TiGer
        // or ADC trigger blocks
        config->trigger[NDIGO6G12_TRIGGER_TDC0 + i].edge = true;
        config->trigger[NDIGO6G12_TRIGGER_TDC0 + i].rising = false;
        // threshold not applicable for TDC inputs
        // trigger threshold is set via tdc_trigger_offsets[i]
        config->trigger[NDIGO6G12_TRIGGER_TDC0 + i].threshold = 0;
    }
}