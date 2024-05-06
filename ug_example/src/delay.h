#include <deque>
#include <map>
#include <string>
#include <vector>
#include <float.h>

// this utility class manages the arrival of timestamps for 
// a number of channels and tries to group them to a start
// signal on one channels and stop signals on the other channels

// delay status
enum DelayStatus { 
    NotEnoughData, // we do not know, if the following signal has already arrived
    StopsMissing, // some of the stops have to arrived after a maximum wait time
    Complete,      // start and all expected stops were processed correctly
    StartMissing 
};

class ChannelInfo {
  public:
    size_t index;
    int channel;
    std::string name;
    // contains the timestamps of pulse
    std::deque<double> timestamps;
    bool early;
    bool ok;
    bool HasData() const { return timestamps.size() > 0; }
};

// per channel output of delay measurement
class ChannelDelay {
  public:
    int channel;
    bool missing;
    bool isStart;
    std::string name;
    double delayPs;
    // number of events that were ignored because of missing start
    int ignoredCount;
};

// output of delay measurement
class Delays {
  public:
    DelayStatus status;
    std::vector<ChannelDelay> channelDelays;
    double startTimestamp;
};

// class for measurement of delays between given number of channels
class DelayMeasurement {
    std::vector<ChannelInfo> channels;
    // map from channel to the index in channels
    std::map<int, size_t> channelIndexes;
    //
    Delays delays;
    size_t startIndex;
    double maxDelay;
    // maxWaitTime is the time to wait after a signal, to know that a following
    // signal has been received, this allow deciding, if a group is complete
    double maxWaitTime;

  public:
      // maxDelay is the time that two timestamps are considered to be in the same group
      // e.g. the maximum delay for a simple cable delay time
    void Init(int startChannel, double maxDelay,
              std::map<int, std::string> channelMap) {
        channels.resize(channelMap.size());
        this->maxDelay = maxDelay;
        maxWaitTime = 10 * maxDelay;

        delays.channelDelays.resize(channelMap.size());
        size_t i = 0;
        for (auto const &e : channelMap) {
            int channel = e.first;
            std::string name = e.second;
            channels[i].index = i;
            channels[i].channel = channel;
            channels[i].name = name;
            delays.channelDelays[i].channel = channel;
            delays.channelDelays[i].name = name;
            delays.channelDelays[i].isStart = startChannel == channel;
            channelIndexes[channel] = i;
            i++;
        }
        startIndex = channelIndexes[startChannel];
    }

    void SetMaxWaitTime(double maxWaitTime) { 
        this->maxWaitTime = maxWaitTime;
    }
    // write the current timestamp in ps to the structure
    void InsertTimestamp(int channel, double timestamp) {
        size_t index = channelIndexes[channel];
        channels[index].timestamps.push_back(timestamp);
    }

    // the parameter is returned by pointer to avoid memory allocations
    Delays *MeasureDelays() {
        size_t maxSize = channels[0].timestamps.size();
        size_t earliestIndex = 0;
        double earliestTimestamp = DBL_MAX;
        double latestTimestamp = 0;
        delays.channelDelays.resize(channels.size());

        for (const ChannelInfo &ci : channels) {
            maxSize = std::max(maxSize, ci.timestamps.size());
            if (ci.timestamps.size() > 0 &&
                ci.timestamps.front() < earliestTimestamp) {
                earliestTimestamp = ci.timestamps.front();
                earliestIndex = ci.index;
            }
            if (ci.timestamps.size() > 0 &&
                ci.timestamps.back() > latestTimestamp) {
                latestTimestamp = ci.timestamps.back();
            }
            delays.channelDelays[ci.index].missing = false;
            delays.channelDelays[ci.index].ignoredCount = 0;
        }

        // process the queues if enough data is expected
        if (maxSize > 0 && latestTimestamp - earliestTimestamp > maxWaitTime) {
            int channelsTooEarly = 0;
            int channelsTooLate = 0;
            int channelsOk = 0;
            int channelsMissing = 0;
            bool startPresent = channels[startIndex].HasData();
            double startTimestamp = startPresent
                                        ? channels[startIndex].timestamps[0]
                                        : latestTimestamp - 2 * maxDelay;

            for (ChannelInfo &ci : channels) {
                ci.early = false;
                ci.ok = false;
                if (ci.HasData()) {
                    double diffToStart = ci.timestamps[0] - startTimestamp;
                    delays.channelDelays[ci.index].delayPs = diffToStart;
                    if (diffToStart < -maxDelay) {
                        ci.early = true;
                        channelsTooEarly++;
                    } else if (diffToStart > maxDelay) {
                        channelsTooLate++;
                        delays.channelDelays[ci.index].missing = true;
                    } else {
                        ci.ok = true;
                        channelsOk++;
                    }
                } else {
                    if (latestTimestamp > startTimestamp + maxWaitTime) {
                        // if there was data it should have arrived by now
                        delays.channelDelays[ci.index].missing = true;
                        channelsMissing++;
                    }
                }
            }

            if (channelsOk + channelsTooLate + channelsMissing ==
                channels.size()) {
                // best case every stop and start is included or some channels
                // are missing/ too later
                for (ChannelInfo &ci : channels) {
                    if (ci.ok) {
                        ci.timestamps.pop_front();
                    }
                }
                delays.startTimestamp = startTimestamp;
                delays.status = Complete;
            } else if (channelsTooEarly > 0 || !startPresent) {
                // cut away
                double cutOffTimestamp = startPresent
                                             ? startTimestamp - maxDelay
                                 : latestTimestamp - maxWaitTime;

                bool removed = false;
                for (ChannelInfo &ci : channels) {
                    while (ci.timestamps.size() > 0 &&
                           ci.timestamps[0] < cutOffTimestamp) {
                        ci.timestamps.pop_front();
                        delays.channelDelays[ci.index].ignoredCount++;
                        removed = true;
                    }
                }
                delays.startTimestamp = earliestTimestamp;

                delays.status = removed ? StartMissing : NotEnoughData;
            } else {
                delays.status = NotEnoughData;
            }
        } else {
            // else not enough data, process during next process packets
            delays.status = NotEnoughData;
        }
        return &delays;
    }

    // the parameter is passed by reference to avoid memory allocations
    void PrintDelays(Delays *delays) {
        if (delays->status == NotEnoughData) {
            return;
        }
        if (delays->status == Complete || delays->status == StopsMissing) {
            for (const ChannelDelay &cd : delays->channelDelays) {
                if (cd.isStart) {
                    printf("---\n%s: Start %.3lf ns\n", cd.name.c_str(),
                           delays->startTimestamp / 1000.);
                } else if (!cd.missing) {
                    printf("%s: Delay %.3lf ns\n", cd.name.c_str(),
                           cd.delayPs / 1000.);
                } else {
                    printf("%s: Missing\n", cd.name.c_str());
                }
            }
        }
        if (delays->status == StartMissing) {

            printf("---\n Start missing at  %.3lf ns\n", 
                delays->startTimestamp / 1000.);
            for (const ChannelDelay &cd : delays->channelDelays) {
                if (cd.isStart) {
                    // ignore
                } else if (cd.ignoredCount > 0) {
                    printf("%s: Ignored %d\n", cd.name.c_str(),
                           cd.ignoredCount);
                }
            }
        }
    }
};
