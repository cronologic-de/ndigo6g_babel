#pragma once
#include "delay.h"
#include "ndigo6g12_interface.h"
#include <map>
#include <string>
#include <vector>

// Base class for Ndigo6G applications
// contains common code for packet processing
class Ndigo6GApp {
  protected:
    const int PRECURSOR = 1;
    // contains the timing parameters of the current mode like sample period
    ndigo6g12_param_info *pi;
    int adcThreshold;
    int tdcChannelMask;
    // convenience method for adding the TDC channels to the channel map
    void AddTDCChannels(std::map<int, std::string> &channelMap) {
        for (int i = 0; i < 4; i++) {
            if (tdcChannelMask & (1 << i)) {
                channelMap[4 + i] = (char)'E' + (char)i;
            }
        }
    }

  public:
    Ndigo6GApp(int tdcChannelMask) { this->tdcChannelMask = tdcChannelMask; }

    // configure the Ndigo6G with the appropiate mode and triggers
    virtual void ConfigureADC(ndigo6g12_configuration *config,
                              int adcThreshold) = 0;

    virtual void ConfigureTDC(ndigo6g12_configuration *config);

    // react to an ADC incoming packet
    virtual double ProcessADCPacket(crono_packet *pkt) = 0;

    // set the parameters after configuration was successful
    virtual void SetParamInfo(ndigo6g12_param_info *pi) { this->pi = pi; }

    // called by the main loop on a TDC packet arrival
    virtual void ProcessTDCPacket(crono_packet *pkt);

    // react to an TDC incoming packet called by default implementation of
    // ProcessTDCPacket
    virtual void ProcessTDCTimestamp(int tdcChannel, double timestamp) {
        printf("TDC event on channel %d timestamp: %.3f ns\n", tdcChannel,
               timestamp / 1000.0);
    };

    // helper method to find the time stamp of the current packet
    double ComputePacketTimestamp(volatile crono_packet *pkt) {
        // calculate packet timestamp in picoseconds
        // the precursor time is constant in the modes, but the amount of
        // samples is different (32/16/8 for 1/2/4)
        double packet_ts =
            pkt->timestamp * pi->packet_ts_period - PRECURSOR * 5e3 ;
        return packet_ts;
    }

    /* Computes the falling edge in the given data, returns the absolute ps
    value, -1 if threshold was not passed in the packet. */
    double ComputeFallingEdge(crono_packet *pkt) {
        // packet length is number of 64 bit words of data
        double packetTs = ComputePacketTimestamp(pkt);
        // 4 ADC samples are stored in each 64 bit chunk of packet data
        uint32_t sampleCount = (pkt->length * 4);

        // ADC data is a signed 16 bit integer
        int16_t *adc_data = (int16_t *)(pkt->data);

        // find first falling edge in ADC data
        for (uint32_t i = 0; i < (sampleCount - 1); i++) {
            if (adc_data[i] >= adcThreshold && adc_data[i + 1] < adcThreshold) {
                // calculate threshold crossing relative to start of packet
                double feOffset = i;
                // linear interpolation of trigger threshold crossing
                feOffset += (double)(adc_data[i] - adcThreshold) /
                            (adc_data[i] - adc_data[i + 1]);
                // convert to picoseconds
                feOffset *= pi->sample_period;

                // calculate timestamp of threshold crossing in picoseconds
                double fallingEdgeTs = packetTs + feOffset;
                // adjust for ADC pipeline delay
                fallingEdgeTs -= pi->adc_sample_delay;

                return fallingEdgeTs;
            }
        }
        return -1;
    }


};
// maximum distance of two pulses, so that they are considered to be a cable delay
static const double MAX_DELAY_PS = 500000.;

class Ndigo6GAppSingle : public Ndigo6GApp {
  private:
    // last falling edge to compute the difference  to
    double lastFallingEdgeTs = 0;

  public:
    Ndigo6GAppSingle(int tdcChannelMask) : Ndigo6GApp(tdcChannelMask) {
    }
    virtual void ConfigureADC(ndigo6g12_configuration *config,
                              int adc_threshold);
    virtual double ProcessADCPacket(crono_packet *pkt);
    virtual void ProcessTDCTimestamp(int tdcChannel, double timestamp) {}
};



// Implementation of the different sample applications
class Ndigo6GAppDual : public Ndigo6GApp {
  private:
    DelayMeasurement delayMeasure;

  public:
    Ndigo6GAppDual(int tdcChannelMask) : Ndigo6GApp(tdcChannelMask) {
        std::map<int, std::string> channelMap = {{0, "A"}, {3, "D"}};
        AddTDCChannels(channelMap);
        delayMeasure.Init(0, MAX_DELAY_PS, channelMap);
    }
    virtual void ConfigureADC(ndigo6g12_configuration *config,
                              int adc_threshold);

    virtual double ProcessADCPacket(crono_packet *pkt);

    virtual void ProcessTDCTimestamp(int tdcChannel, double timestamp);
    virtual void SetParamInfo(ndigo6g12_param_info *pi) {
        Ndigo6GApp::SetParamInfo(pi);
        // we have to wait for 3 TDC period to make sure, that the TDC data has
        // arrived
        delayMeasure.SetMaxWaitTime(pi->tdc_rollover_period * 3.5 *
                                    pi->tdc_period);
    }
};

class Ndigo6GAppQuad : public Ndigo6GApp {
  private:
    DelayMeasurement delayMeasure;

  public:
    Ndigo6GAppQuad(int tdcChannelMask) : Ndigo6GApp(tdcChannelMask) {

        std::map<int, std::string> channelMap = {
            {0, "A"}, {1, "B"}, {2, "C"}, {3, "D"}};
        AddTDCChannels(channelMap);
        delayMeasure.Init(0, MAX_DELAY_PS, channelMap);
    }

    virtual void ConfigureADC(ndigo6g12_configuration *config,
                              int adc_threshold);

    virtual  void SetParamInfo(ndigo6g12_param_info *pi) {
        Ndigo6GApp::SetParamInfo( pi);
        // we have to wait for 3 TDC period to make sure, that the TDC data has arrived
        delayMeasure.SetMaxWaitTime(pi->tdc_rollover_period * 3.5 *
                                    pi->packet_ts_period);
    }

    virtual double ProcessADCPacket(crono_packet *pkt);

    virtual void ProcessTDCTimestamp(int tdcChannel, double timestamp);
};

class Ndigo6GAppAverager : public Ndigo6GApp {
  private:
    // last falling edge to compute the difference  to
    double lastFallingEdgeTs = 0;

  public:
    Ndigo6GAppAverager(int tdcChannelMask) : Ndigo6GApp(tdcChannelMask) {}
    virtual void ConfigureADC(ndigo6g12_configuration *config,
                              int adc_threshold);
    virtual double ProcessADCPacket(crono_packet *pkt);
};
