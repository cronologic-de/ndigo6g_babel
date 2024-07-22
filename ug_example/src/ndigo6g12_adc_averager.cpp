#include <stdio.h>
#include "ndigo6g12_app.h"

const int AVERAGING_COUNT = 16;

double Ndigo6GAppAverager::ProcessADCPacket(crono_packet* pkt) {

	// calculate packet timestamp in picoseconds
	// not adjusted for ADC-data precursor
	double packet_ts = pkt->timestamp * pi->packet_ts_period;

	printf("\nPacket timestamp: %.3f ns\n", (packet_ts / 1000.0));

	// packet length is number of 64-bit words of data
	// the first two 64-bit packet data words are additional header
	// information
	uint32_t data_offset = 2;
	// only the first currently carries valid information
	uint64_t averaging_header0 = *(pkt->data);

	// if bit is set, less than the requested number of iterations have been
	// performed before writing the packet due to possible data overflow on
	// the next iteration
	bool stopped_due_to_overflow = (averaging_header0 >> 32) & 0x1;

	// if bit is set, the averaged data contains saturated or overflowed
	// samples does NOT indicate that the input signal has not exceeded the
	// ADC range
	bool averaging_overflow = (averaging_header0 >> 32) & 0x2;

	// number of iterations; may be less than requested
	int iterations_performed = (averaging_header0 & 0xffffff);

	// 2 averaged ADC samples are stored in each 64-bit chunk of packet data
	uint32_t sample_count = ((pkt->length - data_offset) * 2);

	// ADC data is a signed 32-bit integer
	int32_t* adc_data = (int32_t*)(pkt->data + data_offset);

	// find first falling edge in averaging data
	for (uint32_t i = 0; i < sample_count - 1; i++) {
		if (adc_data[i] >= 0 && adc_data[i + 1] < 0) {
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

void Ndigo6GAppAverager::ConfigureADC(ndigo6g12_configuration* config,
								      int adcThreshold) {
	// adcThreshold not used here, 0 is used as threshold for the data
	config->adc_mode = NDIGO6G12_ADC_MODE_A;

	// ADC sample value range -32768 .. 32767
	// averaging data saturates at +/- 2^21 - 1
	config->output_mode = NDIGO6G12_OUTPUT_MODE_SIGNED32;

	// enable ADC channel A and trigger on the falling edge of TRG input
	// shift baseline of analog inputs to +350 mV
	config->analog_offsets[0] = NDIGO6G12_DC_OFFSET_N_NIM * -1;

	// trigger on falling edge of TRG input
	config->trigger[NDIGO6G12_TRIGGER_TRG].edge = true;
	config->trigger[NDIGO6G12_TRIGGER_TRG].rising = false;

	// set trigger level on TRG input to -350 mV
	config->tdc_trigger_offsets[4] = NDIGO6G12_DC_OFFSET_N_NIM;

	// enable channel
	config->trigger_block[0].enabled = true;
	// multiples of 32 ADC samples (5 ns recording time)
	config->trigger_block[0].length = 32764;

	// select TRG as trigger source of the channel
	config->trigger_block[0].sources = NDIGO6G12_TRIGGER_SOURCE_TRG;

	// configuration of the Averaging features
	// number of events that are averaged/summed
	config->average_configuration.iterations = AVERAGING_COUNT;

	// saturate averaging data instead of overflow
	config->average_configuration.use_saturation = true;

	// don't stop averaging if next iteration could lead to sample data overflow
	config->average_configuration.stop_on_overflow = false;
}