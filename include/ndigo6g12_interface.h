/*
 * Header file containing structs and #defines specific for the Ndigo6G-12
 * board.
 * The current driver version for Ndigo6G-12 devices is 1.3.0.0
 */

/*!
 * @file
 * @brief   The functions provided by the API are declared in
 *          `ndigo6G12_interface.h`.
 * @details The API is a DLL with C linkage.
 */
#ifndef NDIGO6G12_INTERFACE_H
#define NDIGO6G12_INTERFACE_H
#include "crono_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) || defined(_WIN64)
#ifdef NDIGO6G12_DRIVER_EXPORTS
#define NDIGO6G12_API __declspec(dllexport)
#else
#define NDIGO6G12_API __declspec(dllimport)
#endif
#else
#define NDIGO6G12_API
#endif

/*!
 * @defgroup constants Constants
 * @brief    Constants
 * @{
 */
/*! The current API version. */
#define NDIGO6G12_API_VERSION 1

/*! The number of ADC and TDC triggers, including AUTO and ONE. */
#define NDIGO6G12_TRIGGER_COUNT 16

/*! The number of analog input channels. */
#define NDIGO6G12_ADC_CHANNEL_COUNT 4

/*! The number of gating blocks. */
#define NDIGO6G12_GATE_COUNT 4

/*! The number of high and low resolution TDC input channels. */
#define NDIGO6G12_TDC_CHANNEL_COUNT 6

/*! Bitstream date format: YYYY-MM-DD hh:mm:ss */
#define NDIGO6G12_BITSTREAM_DATE_LEN 20

/*! Calibration date format: YYYY-MM-DD hh:mm */
#define NDIGO6G12_CALIBRATION_DATE_LEN 20

/*! Length of Ndigo6G-12 flash signature */
#define NDIGO6G12_FLASH_SIG_LEN 60

/*!
 * @brief   ADC sample FIFO depth.
 * @details It is the maximum recording length in multiples of 5 ns.
 */
#define NDIGO6G12_FIFO_DEPTH 16364
/*!
 * @}
 */

/*!
 * @defgroup triggerblockdefs
 * @brief    Defines for @link ndigo6g12_trigger_block @endlink.
 * @{
 */
/*! Maximum for @link ndigo6g12_trigger_block::precursor @endlink. */
#define NDIGO6G12_MAX_PRECURSOR 28

/*! Maximum for @link ndigo6g12_trigger_block::multi_shot_count @endlink. */
#define NDIGO6G12_MAX_MULTISHOT 65535
/*!
 * @}
 */

/*!
 * @defgroup clockmodes Defines for ndigo6g12_init_parameters
 * @brief    Clock modes of the Ndigo6G-12.
 * @details  Used for @link ndigo6g12_init_parameters::clock_source @endlink.
 * @{
 */
/*! Device is using the internal 10 MHz clock. */
#define NDIGO6G12_CLOCK_SOURCE_INTERNAL 0

/*!
 *  Use an external 10&nbsp;MHz clock as reference. The input is the SMA
 *  socket located on the board.
 */
#define NDIGO6G12_CLOCK_SOURCE_SMA 1

/*!
 * Use an external 10&nbsp;MHz clock as reference. The inputs are the bracket
 * LEMO connectors.
 */
#define NDIGO6G12_CLOCK_SOURCE_AUX2 2
/*!
 * @}
 */

/*!
 * @defgroup apptypes Application Types
 * @brief    Type of application.
 * @details  Used for @link ndigo6g12_init_parameters::application_type
 *           @endlink.
 * @{
 */
/*!
 * @brief Averaging mode.
 * @verbatim embed:rst:leading-asterisk
 *        For more information, see :numref:`Section %s<Averaging Mode>`.
 * @endverbatim
 */
#define NDIGO6G12_APP_TYPE_AVRG 5

/*! Four ADC channels at 1.6 Gsps. */
#define NDIGO6G12_APP_TYPE_4CH 4

/*! Two ADC channels at 3.2 Gsps. */
#define NDIGO6G12_APP_TYPE_2CH 2

/*! One ADC channel at 6.4 Gsps. */
#define NDIGO6G12_APP_TYPE_1CH 1

/*! Use currently installed application type. */
#define NDIGO6G12_APP_TYPE_CURRENT 0
/*!
 * @}
 */

/*!
 * @defgroup alertdefs Defines for alerts
 * @brief   Alert bits from the system monitor.
 * @details Used for @link ndigo6g12_fast_info::alerts @endlink.
 * @{
 */
/*!
 * @brief   FPGA temperature alert (>&nbsp;70&deg;C)
 */
#define NDIGO6G12_ALERT_FPGA_TEMPERATURE 1

/*!
 * @brief   Internal FPGA voltage out of range (<&nbsp;0.83&nbsp;V or
 *          >&nbsp;0.88&nbsp;V).
 */
#define NDIGO6G12_ALERT_VCCINT 2

/*!
 * @brief   FPGA auxiliary voltage out of range (<&nbsp;1.75&nbsp;V or
 *          >&nbsp;1.89&nbsp;V).
 */
#define NDIGO6G12_ALERT_VCCAUX 4

/*!
 * @brief   FPGA temperature critical (>&nbsp;80&deg;C)
 */
#define NDIGO6G12_ALERT_FPGA_TEMPERATURE_CRITICAL 8

/*!
 * @brief THS temperature critical (>&nbsp;140&deg;C)
 */
#define NDIGO6G12_ALERT_THS_TEMPERATURE_CRITICAL 16
/*!
 * @}
 */

/*!
 * @defgroup adcdefs Defines for adc_mode
 * @brief    Defines for @link ndigo6g12_configuration::adc_mode @endlink
 * @{
 */
#define NDIGO6G12_ADC_MODE_ABCD 0 //!< 4 channel mode at sample rate 1600 Msps
#define NDIGO6G12_ADC_MODE_AADD 1 //!< 4 channel mode at sample rate 1600 Msps
#define NDIGO6G12_ADC_MODE_AAAA 2 //!< 4 channel mode at sample rate 1600 Msps
#define NDIGO6G12_ADC_MODE_DDDD 3 //!< 4 channel mode at sample rate 1600 Msps
#define NDIGO6G12_ADC_MODE_AD 4   //!< 2 channel mode at sample rate 3200 Msps
#define NDIGO6G12_ADC_MODE_AA 5   //!< 2 channel mode at sample rate 3200 Msps
#define NDIGO6G12_ADC_MODE_DD 6   //!< 2 channel mode at sample rate 3200 Msps
#define NDIGO6G12_ADC_MODE_A 7    //!< 1 channel mode at sample rate 6400 Msps
#define NDIGO6G12_ADC_MODE_D 8    //!< 1 channel mode at sample rate 6400 Msps
/*!
 * @}
 */

/*!
 * @defgroup outputdefs Defines for output_mode
 * @brief   Defines for @link ndigo6g12_configuration::output_mode @endlink
 * @{
 */

/*!
 * @brief   Return the native range (0 to 4095).
 */
#define NDIGO6G12_OUTPUT_MODE_RAW 0

/*!
 * @brief   Return a signed16 integer.
 * @details The range is &minus;32768 to 32767.
 */
#define NDIGO6G12_OUTPUT_MODE_SIGNED16 1

/*!
 * @brief   Output in signed32 integer format.
 * @details Only applicable for averaging mode.
 *          The range is &minus;2<sup>31</sup> to 2<sup>31</sup> &minus; 1.
 */
#define NDIGO6G12_OUTPUT_MODE_SIGNED32 2
/*!
 * @}
 */

/*!
 * @defgroup gatedefs Defines for trigger_gate
 * @brief   Bitmask for configuration of @link ndigo6g12_trigger_block::gates
 *          @endlink.
 * @details Bit definitions for trigger sources used in the timing generator
 *          and gating configuration.
 * @{
 */
#define NDIGO6G12_TRIGGER_GATE_NONE 0x0000
#define NDIGO6G12_TRIGGER_GATE_0 0x0001
#define NDIGO6G12_TRIGGER_GATE_1 0x0002
#define NDIGO6G12_TRIGGER_GATE_2 0x0004
#define NDIGO6G12_TRIGGER_GATE_3 0x0008
/*!
 * @}
 */

/*!
 * @defgroup sourcedefs defines for trigger_source
 * @brief   Bitmasks for trigger sources.
 * @details Used for @link ndigo6g12_trigger_block::sources @endlink,
 *          @link ndigo6g12_gating_block::sources @endlink,
 *          @link ndigo6g12_tdc_gating_block::sources @endlink,
 *          and @link ndigo6g12_tdc_tiger_block::sources @endlink.
 * @{
 */

/*!
 * @brief   All trigger sources disabled.
 */
#define NDIGO6G12_TRIGGER_SOURCE_NONE 0x00000000

#define NDIGO6G12_TRIGGER_SOURCE_A0 0x00000001
#define NDIGO6G12_TRIGGER_SOURCE_A1 0x00000002
#define NDIGO6G12_TRIGGER_SOURCE_B0 0x00000004
#define NDIGO6G12_TRIGGER_SOURCE_B1 0x00000008
#define NDIGO6G12_TRIGGER_SOURCE_C0 0x00000010
#define NDIGO6G12_TRIGGER_SOURCE_C1 0x00000020
#define NDIGO6G12_TRIGGER_SOURCE_D0 0x00000040
#define NDIGO6G12_TRIGGER_SOURCE_D1 0x00000080

#define NDIGO6G12_TRIGGER_SOURCE_TDC0 0x00000100
#define NDIGO6G12_TRIGGER_SOURCE_TDC1 0x00000200
#define NDIGO6G12_TRIGGER_SOURCE_TDC2 0x00000400
#define NDIGO6G12_TRIGGER_SOURCE_TDC3 0x00000800

#define NDIGO6G12_TRIGGER_SOURCE_FPGA0 0x00001000
#define NDIGO6G12_TRIGGER_SOURCE_FPGA1 0x00002000

#define NDIGO6G12_TRIGGER_SOURCE_AUTO 0x00004000

/*!
 * @brief Trigger signal is active each clock cycle.
 */
#define NDIGO6G12_TRIGGER_SOURCE_ONE 0x00008000
/*!
 * @}
 */

/*!
 * @defgroup tdcpacketflags TDC Packet flags
 * @brief   Flags of a TDC packet reporting error conditions.
 * @details Used for @ref crono_packet::flags\.
 * @{
 */

#define NDIGO6G12_TDC_PACKET_FLAG_RESERVED 1

/*!
 * @brief   Packet contains at least one TDC event
 */
#define NDIGO6G12_TDC_PACKET_FLAG_CONTAINS_DATA 2

/*!
 * @brief   At least one packet was lost due to full FIFO.
 */
#define NDIGO6G12_TDC_PACKET_FLAG_LOST 4

/*!
 * @brief   The trigger unit has shortend the current packet due to full FIFO.
 */
#define NDIGO6G12_TDC_PACKET_FLAG_SHORTENED 8

/*!
 * @brief   DMA FIFO was full.
 * @details This does not necessarily mean that packets were dropped.
 */
#define NDIGO6G12_TDC_PACKET_FLAG_DMA_FIFO_FULL 16

/*!
 * @brief   Host buffer was full.
 * @details This does not necessarily mean that packets were dropped.
 */
#define NDIGO6G12_TDC_PACKET_FLAG_HOST_BUFFER_FULL 32
/*!
 * @}
 */

/*!
 * @defgroup tdchitflags TDC Hit flags
 * @brief   Flags of TDC-hit error conditions.
 * @{
 */
/*!
 * @brief   At least one preceding event was lost due to full FIFO.
 */
#define NDIGO6G12_TDC_HIT_FLAG_LOST 1

/*!
 * @brief   Rollover has been lost due to full FIFO.
 * @details Results in a fatal error.
 */
#define NDIGO6G12_TDC_HIT_FLAG_ROLLOVER_LOST 2

/*!
 * @brief   Timestamp is a valid TDC event.
 */
#define NDIGO6G12_TDC_HIT_FLAG_VALID 4

/*!
 * @brief   Timestamp is a rollover marker.
 * @details Add @link ndigo6g12_param_info::tdc_rollover_period @endlink to
 *          all subsequent timestamps in the packet.
 */
#define NDIGO6G12_TDC_HIT_FLAG_GROUP_TIME_ROLLOVER 8

/*!
 * @brief   TDC hit flag mask for error reporting.
 */
#define NDIGO6G12_TDC_HIT_ERROR_MASK (NDIGO6G12_TDC_HIT_FLAG_ROLLOVER_LOST | NDIGO6G12_TDC_HIT_FLAG_LOST)

/*!
 * @brief   TDC hit flags mask for timestamp type
 */
#define NDIGO6G12_TDC_HIT_TYPE_MASK (NDIGO6G12_TDC_HIT_FLAG_GROUP_TIME_ROLLOVER | NDIGO6G12_TDC_HIT_FLAG_VALID)

/*!
 * @brief   TDC hit channel number for padding-data.
 * @details Padding-data can be ignored. Does not contain any usefull
 *          information. Padding-data has
 *          @link NDIGO6G12_TDC_HIT_FLAG_GROUP_TIME_ROLLOVER @endlink and
 *          @link NDIGO6G12_TDC_HIT_FLAG_VALID @endlink always cleared.
 */
#define NDIGO6G12_TDC_PADDING_DATA_CHANNEL 14

/*!
 * @brief   TDC hit channel number for rollover marker
 * @details Rollover marker has
 *          @link NDIGO6G12_TDC_HIT_FLAG_GROUP_TIME_ROLLOVER @endlink always
 *          set.
 */
#define NDIGO6G12_TDC_ROLLOVER_CHANNEL 15
/*!
 * @}
 */

/*!
 * @defgroup triggerdefs #defines for trigger
 * @brief Defines for @link ndigo6g12_configuration::trigger @endlink.
 * @{
 */
#define NDIGO6G12_TRIGGER_A0 0
#define NDIGO6G12_TRIGGER_A1 1
#define NDIGO6G12_TRIGGER_B0 2
#define NDIGO6G12_TRIGGER_B1 3
#define NDIGO6G12_TRIGGER_C0 4
#define NDIGO6G12_TRIGGER_C1 5
#define NDIGO6G12_TRIGGER_D0 6
#define NDIGO6G12_TRIGGER_D1 7
#define NDIGO6G12_TRIGGER_TDC0 8
#define NDIGO6G12_TRIGGER_TDC1 9
#define NDIGO6G12_TRIGGER_TDC2 10
#define NDIGO6G12_TRIGGER_TDC3 11
#define NDIGO6G12_TRIGGER_FPGA0 12
#define NDIGO6G12_TRIGGER_FPGA1 13
#define NDIGO6G12_TRIGGER_AUTO 14
#define NDIGO6G12_TRIGGER_ONE 15
/*!
 * @}
 */

/*!
 * @defgroup defdcoffset defines for tdc_trigger_offsets
 * @brief Defines for @link ndigo6g12_configuration::tdc_trigger_offsets
 *        @endlink.
 * @{
 */
#define NDIGO6G12_DC_OFFSET_N_NIM -0.35
/*!
 * @}
 */

/*!
 * @defgroup devicestates defines for ndigo6g12_device_state
 * @brief   Defines for @link ndigo6g12_fast_info::state @endlink.
 * @details A device must be configured before data-capturing is started.
 * @{
 */

/*!
 * @brief   Device is initialized but not yet configured for data capture.
 */
#define NDIGO6G12_DEVICE_STATE_INITIALIZED CRONO_DEVICE_STATE_INITIALIZED

/*!
 * @brief   Device is ready for data capture.
 */
#define NDIGO6G12_DEVICE_STATE_CONFIGURED CRONO_DEVICE_STATE_CONFIGURED

/*!
 * @brief   Device has started data capture.
 */
#define NDIGO6G12_DEVICE_STATE_CAPTURING CRONO_DEVICE_STATE_CAPTURING
/*!
 * @}
 */

/*!
 * @defgroup tigerdefs Defines for TiGer blocks
 * @brief   Defines for @link ndigo6g12_tdc_tiger_block::mode @endlink.
 * @{
 */
/*!
 * @brief   TiGeR deactivated.
 */
#define NDIGO6G12_TIGER_OFF 0

/*!
 * @brief   Pulse height is approximately 2&nbsp;V.
 * @details LEMO is only usable as output.
 */
#define NDIGO6G12_TIGER_OUTPUT 1

/*!
 * @brief   Pulse height is approximately 1&nbsp;V.
 * @details LEMO may be used as input with OR function if external pulse rate
 *          is low.
 */
#define NDIGO6G12_TIGER_BIDI 2

/*!
 * @brief   TiGer pulses are bipolar.
 * @details LEMO connectors are only usable as outputs. Not supported for FPGA0 and FPGA1.
 */
#define NDIGO6G12_TIGER_BIPOLAR 3

/*!
 * @brief   Maximum length of bipolar TiGeR pulses.
 */
#define NDIGO6G12_TIGER_MAX_BIPOLAR_PULSE_LENGTH 15
/*!
 * @}
 */

/*!
 * @brief   Contains information of the Ndigo6G-12 device in use.
 */
typedef struct {
    bool is_valid;
    void *ndigo6g12;
} ndigo6g12_device;

/*!
 * @brief   Struct for the initialization of the Ndigo6G-12.
 * @details This structure MUST be completely initialized.
 */
typedef struct {
    /*!
     * @brief   The version number.
     * @details It is increased when the definition of the structure is
     *          changed. The increment can be larger than 1 to match driver
     *          version numbers or similar. Set to 0 for all versions up to
     *          first release.
     * @details Must be set to @link NDIGO6G12_API_VERSION @endlink.
     */
    int version;

    /*!
     * @brief   The index in the list of Ndigo6G-12 boards that should be
     *          initialized.
     * @details There might be multiple boards installed in the system that
     *          are handled by this driver as reported by
     *          @link ndigo6g12_count_devices() @endlink. This index selects
     *          one of them. Boards are enumerated depending on the PCIe slot.
     *          The lower the bus number and the lower the slot number the
     *          lower the card index.
     */
    int card_index;

    /*!
     * @brief   The global index in the list of all cronologic devices.
     * @details This 8-bit number is filled into each packet created by the
     *          board and is useful if data-streams of multiple boards will be
     *          merged. If only Ndigo6G-12 boards are used, this number can be
     *          set to @link card_index @endlink. If boards of different types
     *          that use a compatible data format are used in a system, each
     *          board should get a unique ID.
     */
    int board_id;

    /*!
     * @brief   The minimum size of the DMA buffer.
     * @details If set to 0, the default size of 64 MiBytes is used.
     *          For the Ndigo6G-12 only the first entry is used.
     */
    int64_t buffer_size[8];

    /*!
     * @brief   The update delay of the writing pointer after a packet has
     *          been send over PCIe.
     * @details Default is 8192. Do not change.
     */
    int dma_read_delay;

    /*!
     * @brief   Default 0, corresponding to  1.6, 3.2, or 6.4&nbsp;Gsps
     *          (depending on `application_type`).
     * @details For internal use only. Do not change.
     */
    int perf_derating;

    /*!
     * @brief   Controls the LED flashing mode.
     * @details Define what LEDs do during initialization:
     *          - 0: LEDs are off
     *          - 1: LEDs light up once
     */
    int led_flashing_mode;

    /*!
     * @brief   Defines which clock source is used (internal, SMA, AUX2).
     * @details See @ref clockmodes "NDIGO6G12_CLOCK_SOURCE" defines.
     */
    int clock_source;

    /*!
     * @brief   Select the application type.
     * @details See @ref apptypes "NDIGO6G12_APP_TYPE_*"\.
     * @details Note that @link ndigo6g12_configuration::adc_mode @endlink must match
     *          the application type chosen here.
     */
    uint32_t application_type;

    /*!
     * @brief   Force a bitstream update that configures the FPGA.
     * @details During the initialization of the board, a bitstream configures
     *          the FPGA of the Ndigo6G-12. This is only done if during the
     *          initialization of the Ndigo6G-12, `application_type` is
     *          different from the `application_type` that the Ndigo6G-12 is
     *          currently configured in. That is, the FPGA is only
     *          reconfigured, if `application_type` changes.
     * @details By setting `force_bitstream_update` to `true`, one can force
     *          a reconfiguration of the FPGA.
     */
    crono_bool_t force_bitstream_update;

    /*!
     * @brief   Size of @link partial_bitstream @endlink.
     * @details Reserved for future expandability.
     */
    int partial_bitstream_size;

    /*!
     * @brief   Pointer to a buffer with partial bitstream data.
     * @details Can be @c nullptr if @link application_type @endlink matches
     *          `application_type` of currently installed firmware.
     * @details Reserved for future expandability.
     */
    uint32_t *partial_bitstream;

    /*!
     * @brief   Location where firmware is installed.
     * @details Pointer to a list of paths (separated by `;`) Can be `nullptr`
     *          if @ref application_type matches `application_type` of
     *          currently installed firmware.
     */
    const char *firmware_locations;
} ndigo6g12_init_parameters;

/*!
 * @brief   Contains configuration changes.
 * @details Structure filled by @link ndigo6g12_get_param_info() @endlink.
 *          This structure contains information that may change indirectly due
 *          to configuration changes.
 */
typedef struct {
    /*!
     * @brief   Bandwidth.
     * @details 4.5 or 6.5&nbsp;GHz depending on
     *          @link ndigo6g12_configuration::extended_bandwidth @endlink.
     */
    double bandwidth;

    /*!
     * @brief   ADC sample resolution.
     * @details Always 12&nbsp;bit.
     */
    int resolution;

    /*!
     * @brief   Actual ADC sample rate of currently sampled data.
     * @details Depending on @link ndigo6g12_configuration::adc_mode @endlink,
     *          that is, `sample_rate` = 6.4&nbsp;GHz / @ref channels.
     */
    double sample_rate;

    /*!
     * @brief   The period that one sample in the data represents in
     *          picoseconds.
     */
    double sample_period;

    /*!
     * @brief   The period that one TDC bin in the data represents in
     *          picoseconds
     */
    double tdc_period;

    /*!
     * @brief   The period that one tick of the packet timestamp represents in
     *          picoseconds
     */
    double packet_ts_period;

    /*!
     * @brief   The TDC packet timestamp offset.
     * @details Since TDC packets carry the timestamp of the end of the
     *          packet, to calculate the start, `tdc_packet_timestamp_offset`
     *          has to be subtracted.
     */
    uint64_t tdc_packet_timestamp_offset;

    /*!
     * @brief   Time span of one TDC timestamp rollover period in
     *          units of the TDC binsize.
     * @details All TDC hits within this period are written to one
     *          @ref crono_packet\.
     */
    uint32_t tdc_rollover_period;

    /*!
     * @brief   The delay of the ADC samples due to pipelining in picoseconds.
     */
    double adc_sample_delay;

    /*!
     * @brief   The ID the board uses to identify itself in the output data
     *          stream.
     * @details Takes values 0 to 255.
     */
    int board_id;

    /*!
     * @brief   Number of ADC channels in the current mode.
     * @details See @link ndigo6g12_configuration::adc_mode @endlink.
     */
    int channels;

    /*!
     * @brief   Mask with a set bit for each enabled input channel.
     */
    int channel_mask;

    /*!
     * @brief   Number of TDC channels in the current mode.
     */
    int tdc_channels;

    /*!
     * @brief   The total amount of the DMA buffer in bytes.
     */
    int64_t total_buffer;

    /*!
     * @brief  The number of samples in one clock cycle in the current mode.
     */
    int samples_per_clock;
} ndigo6g12_param_info;

/*!
 * @brief   Structure contains static information.
 * @details This structure contains information about the board that does not
 *          change during run time. It is provided by
 *          @link ndigo6g12_get_static_info() @endlink.
 */
typedef struct {
    /*!
     * @brief   Bitstream creation date
     * @details DIN EN ISO 8601 string YYYY-MM-DD HH:DD:SS describing the time
     *          when the bitstream was created.
     */
    char bitstream_date[NDIGO6G12_BITSTREAM_DATE_LEN];

    /*!
     * @brief   Describes the schematic configuration of the board.
     * @details The same board schematic can be populated in multiple
     *          variants. This is a 8-bit code that can be read from a
     *          register.
     */
    int board_configuration;

    /*!
     * @brief   Board revision number.
     * @details The board revision number can be read from a register. It is a
     *          four bit number that changes when the schematic of the board
     *          is changed.
     *          - 0: Experimental version of the first board. Labeled
     *               &ldquo;Rev.&nbsp;1&rdquo;.
     *          - 2: First commercial version.
     *               Labeled &ldquo;Rev.&nbsp;2&rdquo;
     */
    int board_revision;

    /*!
     * @brief   The board's serial number.
     * @details With year and running number in 8.24 format (yy.nnn; 8 bits
     *          are used to encode the year, 24 bits to encode the number).
     * @details The number is identical to the one printed on the silvery
     *          sticker on the board.
     */
    int board_serial;

    /*!
     * @brief   Calibration date.
     * @details DIN EN ISO 8601 string YYYY-MM-DD HH:DD describing the time
     *          when the card was calibrated.
     */
    char calibration_date[NDIGO6G12_CALIBRATION_DATE_LEN];

    /*!
     * @brief   16-bit factory ID of the ADC chip.
     * @details This is the chipID as read from the 16-bit ADC chip-ID
     *          register.
     */
    int chip_id;

    /*!
     * @brief   Shows if the inputs are DC-coupled.
     * @details Default is `false`, that is, AC-coupled.
     */
    crono_bool_t dc_coupled;

    /*!
     * @brief   Encoded version number for the driver.
     * @details The lower three bytes contain a triple-level hierarchy of
     *          version numbers. E.g., 0x010103 encodes version 1.1.3.
     * @details A change in the first digit generally requires a recompilation
     *          of user applications. Change in the second digit denote
     *          significant improvements or changes that don't break
     *          compatibility and the third digit changes with minor bugfixes
     *          and the like (see https://semver.org/).
     */
    int driver_revision;

    /*!
     * @brief   The build number of the driver according to cronologic's
     *          internal versioning system.
     */
    int driver_build_revision;

    /*!
     * @brief   Calibration data read from flash is valid.
     * @details If not `false`, the driver found valid calibration data in the
     *          flash on the board and is using it.
     */
    crono_bool_t flash_valid;

    /*!
     * @brief   Revision number of the FPGA configuration.
     */
    int fw_revision;

    /*!
     * @brief   Type of firmware, always 5 -> Ndigo6G-12.
     */
    int fw_type;

    /*!
     * @brief   Trenz serial number.
     */
    int pcb_serial;

    /*!
     * @brief   Subversion revision ID of the FPGA configuration.
     * @details A number to track builds of the firmware in more detail than
     *          the firmware revision. It changes with every change in the
     *          firmware, even if there is no visible effect for the user.
     *          The subversion revision number can be read from a register.
     */
    int svn_revision;

    /*!
     * @brief   Shows the initialized mode.
     * @details See @ref apptypes "NDIGO6G12_APP_TYPE_*" constants.
     */
    int application_type;

    /*!
     * @brief   Shows the signature of the primary flash.
     */
    char config_flash_signature_primary[NDIGO6G12_FLASH_SIG_LEN];

    /*!
     * @brief   Shows the signature of the secondary flash.
     */
    char config_flash_signature_secondary[NDIGO6G12_FLASH_SIG_LEN];

    /*!
     * @brief   Auto trigger clock frequency.
     * @details The clock frequency of the auto trigger in Hz
     *          used for the calculations of
     *          @ref ndigo6g12_configuration::auto_trigger_period\.
     * @details Fixed at 200&nbsp;MHz.
     */
    double auto_trigger_ref_clock;
} ndigo6g12_static_info;

/*!
 * @brief   Contains fast dynamic information.
 * @details This structure is filled by @link ndigo6g12_get_fast_info()
 *          @endlink. This information can be obtained within a few
 *          microseconds.
 */
typedef struct {
    /*!
     * @brief   The current state of the device.
     * @details Should be one of the values
     *          @ref devicestates "NDIGO6G12_DEVICE_STATE_*"
     */
    int state;

    /*!
     * @brief   Speed of the FPGA fan in rounds per minute.
     * @details Reports 0 if no fan is present.
     */
    int fan_speed;

    /*!
     * @brief   Temperature of the FPGA in &deg;C.
     */
    double fpga_temperature;

    /*!
     * @brief   Internal Voltage of the FPGA in V.
     *          Useful debugging information.
     */
    double fpga_vccint;

    /*!
     * @brief   Auxillary Voltage of the FPGA in V.
     *          Useful debugging information.
     */
    double fpga_vccaux;

    /*!
     * @brief   BRAM Voltage of the FPGA in V.
     *          Useful debugging information.
     */
    double fpga_vccbram;

    /*!
     * @brief   Shows measured voltage for the mgt_0v9 power supply in V.
     *          Useful debugging information.
     */
    double mgt_0v9;

    /*!
     * @brief   Shows measured Voltage for the mgt_1v2 power supply in V.
     *          Useful debugging information.
     */
    double mgt_1v2;

    /*!
     * @brief   Shows measured voltage for the 2v5 power supply in V.
     *          Useful debugging information.
     */
    double adc_2v5;

    /*!
     * @brief   Shows measured voltage for the clk_3v3 power supply in V.
     *          Useful debugging information.
     */
    double clk_3v3;

    /*!
     * @brief   Shows measured voltage for the adc_3v3 power supply in V.
     *          Useful debugging information.
     */
    double adc_3v3;

    /*!
     * @brief   Shows measured voltage for the pcie_3v3 power supply in V.
     *          Useful debugging information.
     */
    double pcie_3v3;

    /*!
     * @brief   Shows measured voltage for the opamp_5v2 power supply in V.
     *          Useful debugging information.
     */
    double opamp_5v2;

    /*!
     * @brief   Shows temperature of temp4633_1 in &deg;C.
     */
    double temp4633_1;

    /*!
     * @brief   Shows temperature of temp4633_2 in &deg;C.
     */
    double temp4633_2;

    /*!
     * @brief   Shows temperature of temp4644 in &deg;C.
     */
    double temp4644;

    /*!
     * @brief   Temperature of the TDC-chip in &deg;C.
     */
    double tdc1_temp;

    /*!
     * @brief   Shows voltage for ev12_cmiref power supply in V.
     * @details Measured or calibration target
     *          depending on board revision and assembly variant.
     */
    double ev12_cmiref;

    /*!
     * @brief   Temperature of the ADC in &deg;C.
     */
    double ev12_temp;

    /*!
     * @brief   Alert bits from temperature sensor and the system monitor.
     * @details Bit 0 is set if the TDC temperature exceeds 140&deg;C. In this
     *          case the TDC shut down and the device needs to be
     *          reinitialized.
     * @details See @link alertdefs NDIGO6G12_ALERT_* @endlink.
     */
    int alerts;

    /*!
     * @brief   Number of PCIe lanes the card uses.
     * @details Should always be 8 for the Ndigo6G-12.
     */
    int pcie_link_width;

    /*!
     * @brief   Data rate of the PCIe card.
     * @details Should always be 3 for the Ndigo6G-12.
     */

    int pcie_link_speed;
    /*!
     * @brief    Maximum size for a single PCIe transaction in bytes.
     * @details  Depends on the system configuration.
     */
    int pcie_max_payload;

    /*!
     * @brief   ADC data clock is PLL locked.
     */
    crono_bool_t adc_data_pll_locked;

    /*!
     * @brief   ADC data clock PLL lost lock (Sticky Bit).
     */
    crono_bool_t adc_data_pll_lost_lock;

    /*!
     * @brief   Shows the synced ADC lanes.
     * @details Each bit corresponds to one lane
     */
    int adc_lanes_synced;

    /*!
     * @brief   Shows the ADC lanes that lost sync.
     * @details Each bit corresponds to one lane.
     */
    int adc_lanes_lost_sync;

    /*!
     * @brief   Shows which ADC lanes have an empty FIFO.
     * @details Each bit corresponds to one lane.
     */
    int adc_lanes_fifo_empty;

    /*!
     * @brief   Shows which ADC lanes have a full FIFO.
     * @details Each bit corresponds to one lane.
     */
    int adc_lanes_fifo_full;

    /*!
     * @brief   Shows which ADC lanes are running
     * @details Each bit corresponds to one lane.
     */
    int adc_lanes_running;

    /*!
     * @brief   Shows which ADC lanes were unable to sync before a timeout
     * @details Each bit corresponds to one lane.
     */
    int adc_lanes_sync_timeout;

    /*!
     * @brief   The number of ADC lane synchronization retries.
     * @details Default is set to 0.
     */
    int adc_sync_retry_count;

    /*!
     * @brief   The number of ADC strobe synchronization retries.
     * @details Default is set to 0.
     */
    int adc_sync_strobe_retry_count;

    /*!
     * @brief   16 Bit number showing when the last ADC lane synchronization
     *          was achieved.
     */
    int adc_sync_delay_count;

    /*!
     * @brief   Shows if the supplied mgt power is sufficient.
     *          Useful debugging information.
     */
    crono_bool_t adc_mgt_power_good;

    /*!
     * @brief   Shows if lmk_pll1 is locked. Useful debugging information.
     */
    crono_bool_t lmk_pll1_locked;

    /*!
     * @brief   Shows if lmk_pll2 is locked. Useful debugging information.
     */
    crono_bool_t lmk_pll2_locked;

    /*!
     * @brief   Shows if lmk lost lock. Useful debugging information.
     */
    crono_bool_t lmk_lost_lock;

    /*!
     * @brief   Wait count of the lmk. Useful debugging information.
     */
    int lmk_lock_wait_count;

    /*!
     * @brief   Usefull for hardware debugging.
     */
    int lmk_ctrl_vcxo;

    /*!
     * @brief   lmx locked. Useful debugging information.
     */
    crono_bool_t lmx_locked;

    /*!
     * @brief   lmx lost lock. Useful debugging information.
     */
    crono_bool_t lmx_lost_lock;

    /*!
     * @brief   lmx lock wait count. Useful debugging information.
     */
    int lmx_lock_wait_count;
} ndigo6g12_fast_info;

/*!
 * @brief   The parameters of the read commands.
 */
typedef struct {
    /*!
     * @brief   Automatically acknowledge packets from the previous call of
     *          @ref ndigo6g12_read\.
     * @details Only acknowledged packets will release the memory of the DMA
     *          buffer.
     */
    crono_bool_t acknowledge_last_read;
} ndigo6g12_read_in;

/*!
 * @brief   Struct for the read-out of the Ndigo6G-12 packets.
 */
typedef struct {
    /*!
     * @brief   Pointer to the first packet.
     * @details That is, the pointer that was captured by the call of
     *          @link ndigo6g12_read @endlink.
     */
    volatile crono_packet *first_packet;

    /*!
     * @brief   Pointer to the last packet.
     */
    volatile crono_packet *last_packet;

    /*!
     * @brief   Error code.
     * @details The assignments of the error codes can be found
     *          @link readerrors here @endlink.
     */
    int error_code;

    /*!
     * @brief   Plain text error message.
     */
    const char *error_message;
} ndigo6g12_read_out;

/*!
 * @brief   Structure that contains trigger settings.
 */
typedef struct {
    /*!
     * @brief   Threshold controlling when the ADC channel is active.
     * @details Sets the threshold for the trigger block within the range of
     *          the ADC data. The range depends on
     *          @link ndigo6g12_configuration::output_mode @endlink:
     *          - @link NDIGO6G12_OUTPUT_MODE_RAW @endlink : 0 to 4096
     *          - @link NDIGO6G12_OUTPUT_MODE_SIGNED16 @endlink : &minus;32768
     *            to 32767
     *          .
     *          For trigger indices @link triggerdefs NDIGO6G12_TRIGGER_TDC
     *          @endlink to @link triggerdefs NDIGO6G12_TRIGGER_ONE @endlink
     *          the threshold is ignored.
     * @details For the TDC channels, the trigger threshold is controlled by
     *          @link ndigo6g12_configuration::tdc_trigger_offsets @endlink.
     */
    short threshold;

    /*!
     * @brief   Enables edge-trigger functionality.
     * @details For trigger indices @link NDIGO6G12_TRIGGER_AUTO @endlink
     *          and @link NDIGO6G12_TRIGGER_ONE @endlink this is ignored.
     *          - `false`: Use a level trigger. The level trigger triggers as
     *            long as the signal is above or below (depending on `rising`)
     *            the set threshold. Followingly, the trigger gives the sign
     *            of the signal in reference to the threshold.
     *          - `true`: Use an edge trigger. The edge trigger triggers as
     *            soon as its set threshold is crossed by the signal. Thus,
     *            the roots in reference to the threshold are recorded.
     *          .
     *          Default is `true`.
     */
    crono_bool_t edge;

    /*!
     * @brief   Sets rising-edge trigger functionality.
     * @details For trigger indices @link NDIGO6G12_TRIGGER_AUTO @endlink and
     *          @link NDIGO6G12_TRIGGER_ONE @endlink, this is ignored.
     *          - If `edge` is `true` (i.e., an edge trigger is used):
     *              - `false`: Trigger when the signal crosses from above to
     *                below the threshold.
     *              - `true`: Trigger when the signal crosses from below to
     *                above the threshold.
     *          - If `edge` is `false` (i.e., a level trigger is used):
     *              - `false`: Triggers the part of the signal below the
     *                threshold.
     *              - `true`: Triggers the part of the signal above the
     *                threshold.
     *              .
     *          .
     *          Default is `false`.
     */
    crono_bool_t rising;
} ndigo6g12_trigger;

/*!
 * @brief   Configuration of the trigger block.
 */
typedef struct {
    /*!
     * @brief   Activates triggers on this channel.
     */
    crono_bool_t enabled;

    /*!
     * @brief   Enable retrigger functionality.
     * @details If a new trigger condition occurs while the postcursor is
     *          acquired (i.e., within the time frame controlled by
     *          @link length @endlink), the packet is extended by starting a
     *          new postcursor. Otherwise the new trigger is ignored and the
     *          packet ends after the precursor of the first trigger.
     */
    crono_bool_t retrigger;

    /*!
     * @brief   Number of packets created in single-shot mode (i.e.,
     *          @ref ndigo6g12_single_shot() was called) before packet
     *          generation stops.
     * @details This value is ignored if `enabled` is `true`.
     * @details Maximum is @link NDIGO6G12_MAX_MULTISHOT @endlink.
     */
    int multi_shot_count;

    /*!
     * @brief   Precursor in multiples of 5&nbsp;ns.
     * @details The amount of data preceding a trigger that is captured. The
     *          maximum is @link NDIGO6G12_MAX_PRECURSOR @endlink.
     */
    int precursor;

    /*!
     * @brief   Length of the postcursor in multiples of 5&nbsp;ns.
     * @details The total amount of data that is recorded in addition to the
     *          trigger window is controlled by `length` and `precursor`.
     *          `precursor` determines the amount of data before the trigger
     *          window, `length` the amount of data after the trigger
     *          condition was false the first time.
     * @details In @link ndigo6g12_trigger::edge edge-trigger mode @endlink,
     *          the _trigger window_ is always 1 (i.e., 5&nbsp;ns long).
     *          Otherwise, (level-trigger mode) the trigger window is as long
     *          as the trigger condition was fulfilled.
     * @details The maximum value is @link NDIGO6G12_FIFO_DEPTH @endlink minus
     *          @link ndigo6g12_trigger_block::precursor @endlink minus
     *          _trigger window_.
     */
    int length;

    /*!
     * @brief   A @ref sourcedefs "bit mask" with a bit set for all
     *          trigger sources that can trigger this channel.
     * @details Default @ref sourcedefs "NDIGO6G12_TRIGGER_SOURCE_<channel>0"
     *          (@ref NDIGO6G12_TRIGGER_SOURCE_A0 for ADC channel A,
     *          @ref NDIGO6G12_TRIGGER_SOURCE_B0 for ADC channel B, etc).
     */
    int sources;

    /*!
     * @brief   A @ref gatedefs "bit mask" with a bit set for all trigger
     *          gates.
     * @details Mask which selects the gates that have to be 1 for the trigger
     *          block to use.
     * @details Default @ref NDIGO6G12_TRIGGER_GATE_NONE\.
     */
    int gates;

    /*!
     * @brief   Number of packets that fit into the FIFO
     * @details This parameter sets how many packets are supposed to fit into
     *          the on-board FIFO before a new packet is recorded after the
     *          FIFO was full, i.e., a certain amount of free space in the
     *          FIFO is demanded before a new packet is written after the FIFO
     *          was full. As a measure for the packet length the gatelength
     *          set by the user is used. The on-board algorithm checks the
     *          free FIFO space only in case the FIFO is full. Therefore, if
     *          this number is 1.0 or more at least every second packet in the
     *          DMA buffer is guaranteed to have the full length set by the
     *          gatelength parameters. In many cases smaller values will also
     *          result in full length packets. But below a certain value
     *          multiple packets that are cut off at the end will show up.
     */
    double minimum_free_packets;
} ndigo6g12_trigger_block;

/*!
 * @brief   Contains settings of the gating block.
 * @details After a signal at one of the `sources` is detected, a timer starts
 *          running. Once the timer reaches the value specified by `start`, a
 *          gate is opened (or closed, depending on `negate`) until the timer
 *          reaches the time specified by `stop`.
 * @details What happens in the event that another signal before `stop` is
 *          detected is controlled by `retrigger`.
 */
typedef struct {
    /*!
     * @brief   Invert output polarity.
     * @details If `false` (`true`) the gate is opened (closed) inbetween the
     *          times specified by `start` and `stop`.
     * @details Default is `false`.
     */
    crono_bool_t negate;

    /*!
     * @brief   Enable retriggering.
     * @details If enabled:
     *          - If the timer surpassed the time corresponding to `start`,
     *            it is reset to `start`.
     *          - If the timer did not surpass the time corresponding to
     *            `start`, it is reset to zero.
     *          .
     *          Otherwise signals at the input `sources` are ignored
     *          until `stop` is reached.
     * @details Default is `false`.
     */
    crono_bool_t retrigger;

    /*!
     * @brief   The time from the first input signal seen in the idle state
     *          until the gating output is set.
     * @details In multiples of 5&nbsp;ns. 0 &le; `start` &lt; 2<sup>16</sup>,
     *          while `start` &le; `stop`.
     * @details Default is 0.
     */
    int start;

    /*!
     * @brief   The number of samples from leaving the idle state until the
     *          gating output is reset.
     * @details In multiples of 5&nbsp;ns. 0 &le; `stop` &lt; 2<sup>16</sup>,
     *          while `stop` &ge; `start`.
     * @details Default is 1000.
     */
    int stop;

    /*!
     * @brief   @ref sourcedefs "Bit mask" with a bit set for all trigger
     *          sources that can trigger this channel.
     * @details Default @ref sourcedefs "NDIGO6G12_TRIGGER_SOURCE_<channel>0"
     *          (@ref NDIGO6G12_TRIGGER_SOURCE_A0 for ADC channel A,
     *          @ref NDIGO6G12_TRIGGER_SOURCE_B0 for ADC channel B, etc).
     */
    int sources;
} ndigo6g12_gating_block;

/*!
 * @brief   Contains settings of the gating blocks specifically for the TDCs.
 * @details The functionality is similiar to @ref ndigo6g12_gating_block.
 */
typedef struct {
    /*!
     * @brief   Activates gating block.
     */
    crono_bool_t enable;

    /*!
     * @brief   Inverts output polarity.
     * @details Default is `false`.
     */
    crono_bool_t negate;

    /*!
     * @brief   Enable retriggering.
     * @details If enabled:
     *          - If the timer surpassed the time corresponding to `start`,
     *            it is reset to `start`.
     *          - If the timer did not surpass the time corresponding to
     *            `start`, it is reset to zero.
     *          .
     *          Otherwise signals at the input `sources` are ignored until
     *          `stop` is reached.
     * @details Defaults to `false`.
     */
    crono_bool_t retrigger;

    /*!
     * @brief   The time from the first input signal seen in the idle state
     *          until the gating output is set.
     * @details In multiples of 5&nbsp;ns. 0 &le; `start` &lt; 2<sup>16</sup>,
     *          while `start` &le; `stop`.
     * @details Default is 0.
     */
    int start;

    /*!
     * @brief   The number of samples from leaving the idle state until the
     *          gating output is reset.
     * @details In multiples of 5&nbsp;ns. 0 &le; `stop` &lt; 2<sup>16</sup>,
     *          while `stop` &ge; `start`.
     * @details Default is 1000.
     */
    int stop;

    /*!
     * @brief   @ref sourcedefs "Bit mask" with a bit set for all trigger
     *          sources that can trigger this channel.
     * @details Default @ref sourcedefs "NDIGO6G12_TRIGGER_SOURCE_<channel>0"
     *          (@ref NDIGO6G12_TRIGGER_SOURCE_A0 for ADC channel A,
     *          @ref NDIGO6G12_TRIGGER_SOURCE_B0 for ADC channel B, etc).
     */
    int sources;
} ndigo6g12_tdc_gating_block;

/*!
 * @brief   Contains settings of TiGer block.
 * @details The configuration is similiar to @ref ndigo6g12_gating_block.
 */
typedef struct {
    /*!
     * @brief   Enables the desired mode of operation for the TiGeR.
     * @details It is of one of the values @link tigerdefs NDIGO6G12_TIGER_*
     *          @endlink.
     * @details Default is @link NDIGO6G12_TIGER_OFF @endlink.
     */
    int mode;

    /*!
     * @brief   Set pulse polarity.
     * @details The TiGeR creates a high pulse from `start` to
     *          `stop` unless negated.
     * @details Default is `true`.
     */
    crono_bool_t negate;

    /*!
     * @brief   Enable retriggering.
     * @details If enabled:
     *          - If the timer surpassed the time corresponding to `start`, it
     *            is reset to `start`.
     *          - If the timer did not surpass the time corresponding to
     *            `start`, it is reset to zero.
     *          .
     *          Otherwise signals at the input `sources` are ignored until
     *          `stop` is reached.
     * @details Defaults to `false`.
     */
    crono_bool_t retrigger;

    /*!
     * @brief   The time from the first input signal seen in the idle state
     *          until the TiGer outputs a signal.
     * @details In multiples of 5&nbsp;ns. 0 &le; `start` &lt; 2<sup>16</sup>,
     *          while `start` &le; `stop`.
     * @details Default is 0.
     */
    int start;

    /*!
     * @brief   The number of samples from leaving the idle state until the
     *          TiGer output is reset.
     * @details In multiples of 5&nbsp;ns. 0 &le; `stop` &lt; 2<sup>16</sup>,
     *          while `stop` &ge; `start`.
     * @details Default is 1.
     */
    int stop;

    /*!
     * @brief   @ref sourcedefs "Bit mask" with a bit set for all trigger
     *          sources that can trigger this channel.
     * @details Default @ref sourcedefs "NDIGO6G12_TRIGGER_SOURCE_<channel>0"
     *          (@ref NDIGO6G12_TRIGGER_SOURCE_A0 for ADC channel A,
     *          @ref NDIGO6G12_TRIGGER_SOURCE_B0 for ADC channel B, etc).
     */
    int sources;
} ndigo6g12_tdc_tiger_block;

/*!
 * @brief Contains averaging settings.
 */
typedef struct {
    /*!
     * @brief Set the number of trigger events that are averaged.
     * @details Must be 0 if no averaging application is installed on the
     *          Ndigo6G-12 (see
     *          @link ndigo6g12_init_parameters::application_type @endlink).
     * @details Default is 0.
     */
    int iterations;

    /*!
     * @brief   Stops averaging before an overflow can happen.
     * @details Stops the averaging once _averaging_value_ &ge;
     *          _max_averaging_value_ &minus; _max_ADC_value_
     *          or _averaging_value_ &le; _min_averaging_value_ &minus;
     *          _min_ADC_value_ to prevent overflow.
     * @details .
     *          - _max(min)_averaging_value_ is 2097151 (&minus;2097152)
     *          - _max(min)_ADC_value_ is 32768 (&minus;32767)
     *          .
     * @details Default is `false`.
     */
    crono_bool_t stop_on_overflow;

    /*!
     * @brief   Stops the averaging manually.
     * @details Software stop for averaging. If an averaging iteration has
     *          already started it is finished before the averaging will stop.
     * @details Default is `false`.
     */
    crono_bool_t stop_manual;

    /*!
     * @brief   Determines if saturation arithmetic is used by the averager.
     * @details .
     *          - `true`: Instead of _averaging_value_ over(under)flowing once
     *            _max(min)_averaging_value_ is reached, the maximum (minimum)
     *            value is kept.
     *          - `false`: Once _averaging_value_ reaches
     *            _max(min)_averaging_value_, _averaging_value_ will
     *            over(under)flow and wrap around.
     *          .
     * @details See @link ndigo6g12_averager_configuration::stop_on_overflow
     *          stop_on_overflow @endlink for the values of
     *          _averaging_value_ and _max(min)_averaging_value_.
     * @details Default is `true`.
     */
    crono_bool_t use_saturation;

    /*!
     * @brief   Determine if the averager stops on timeout.
     * @details The timeout time is configured by @ref timeout_threshold\.
     * @details Default is `false`.
     */
    crono_bool_t stop_on_timeout;

    /*!
     * @brief   Set the number of microseconds until timeout.
     * @details Must be 0 if no averaging application is installed on the
     *          Ndigo6G-12 board.
     * @details Default is 0.
     */
    int timeout_threshold;
} ndigo6g12_averager_configuration;

/*!
 * @brief   Contains TDC channel settings
 */
typedef struct {
    /*!
     * @brief   Enable TDC channel.
     * @details Default is `false`.
     */
    crono_bool_t enable;

    /*!
     * @brief   Reserved for future extension.
     */
    crono_bool_t reserved3;

    /*!
     * @brief   Reserved for future extension.
     */
    crono_bool_t reserved2;

    /*!
     * @brief   Reserved for future extension.
     */
    crono_bool_t reserved1;

    /*!
     * @brief   Configuration of the gating blocks.
     */
    ndigo6g12_tdc_gating_block gating_block;

    /*!
     * @brief   Configuration of the TiGer blocks.
     */
    ndigo6g12_tdc_tiger_block tiger_block;
} ndigo6g12_tdc_channel;

/*!
 * @brief   Contains configuration information of the TDC channels.
 */
typedef struct {
    /*!
     * @brief   Configure polarity, type and threshold for the TDC channels.
     */
    ndigo6g12_tdc_channel channel[NDIGO6G12_TDC_CHANNEL_COUNT];

    /*!
     * @brief   Configure THS788 calibration.
     * @details .
     *          - `true`: Skip THS788 calibration.
     *          - `false`: Do THS788 calibration (default).
     *          .
     *          Default is `false`.
     */
    crono_bool_t skip_alignment;

    /*!
     * @brief   Align TDC channels
     * @details Default is `false`.
     */
    crono_bool_t alignment_mode;

    /*!
     * @brief Default is `false`.
     */
    crono_bool_t alignment_pin_high_z;

    /*!
     * @brief   Default is `false`.
     */
    crono_bool_t alignment_pin_invert;

    /*!
     * @brief   Default is 12.
     */
    int alignment_phase_steps;

    /*!
     * @brief   Default is `false`.
     */
    crono_bool_t send_empty_packets;
} ndigo6g12_tdc_configuration;

/*!
 * @brief   Structure that contains the configuration values for the
 *          Ndigo6G-12.
 * @details This structure contains the configuration information. It is used
 *          in conjunction with  @ref ndigo6g12_get_default_configuration()
 *          and @ref ndigo6g12_configure()\.
 */
typedef struct {
    /*!
     * @brief   ADC mode as defined in @ref adcdefs "NDIGO6G12_ADC_MODE_*"\.
     * @details The chosen ADC mode has to be supported by the current
     *          @ref apptypes "NDIGO6G12_APP_TYPE"\.
     * @details For example, if @c NDIGO6G12_APP_TYPE_1CH is used, one
     *          *cannot* choose, e.g.,  `adc_mode = NDIGO6G12_ADC_MODE_AA`,
     *          but one has to either choose `NDIGO6G12_ADC_MODE_A` or
     *          `NDIGO6G12_ADC_MODE_D`.
     * @details Default value depends on
     *          @ref ndigo6g12_init_parameters::application_type.
     *          - @link NDIGO6G12_APP_TYPE_4CH @endlink:
     *            @ref NDIGO6G12_ADC_MODE_A
     *          - @link NDIGO6G12_APP_TYPE_2CH @endlink:
     *            @ref NDIGO6G12_ADC_MODE_AD
     *          - @link NDIGO6G12_APP_TYPE_1CH @endlink:
     *            @ref NDIGO6G12_ADC_MODE_ABCD
     *          .
     * @verbatim embed:rst:leading-asterisk
     *          For more information, see :numref:`Section %s<ADC Modes>`.
     * @endverbatim
     */
    int adc_mode;

    /*!
     * @brief   Select ADC calibration set.
     * @details Default is 3. Do not change.
     */
    int adc_cal_set;

    /*!
     * @brief   Set the offsets of the ADC inputs in V.
     * @details The indices 0 to 3 of the array correspond to ADC channels A
     *          to D.
     * @details Must be between @f$\pm@f$ 0.5&nbsp;V.
     * @details Defaults are 0&nbsp;V for each ADC channel.
     */
    double analog_offsets[NDIGO6G12_ADC_CHANNEL_COUNT];

    /*!
     * @brief   Set DAC for trigger threshold of the TDC inputs in V.
     * @details Channel assignment:
     *          - 0 to 3: high-resolution TDC, inputs E to H
     *          - 4 to 5: low-resolution TDC, inputs FPGA0, FPGA1
     * @details Set to a value between &minus;1.32&nbsp;V and +2.0&nbsp;V.
     * @details This should be close to 50% of the height of your pulses on
     *          the inputs. Examples for various signaling standards are
     *          defined @link defdcoffset here @endlink. The inputs are
     *          AC coupled. This means that for pulse inputs the absolute
     *          voltage is not important. Only the relative pulse amplitude
     *          causes the input circuits to switch. @c tdc_trigger_offset
     *          for an input must be set to the relative switching voltage
     *          for the input standard in use. If the pulses are negative, a
     *          negative switching threshold must be set and vice versa.
     * @details Defaults are @ref NDIGO6G12_DC_OFFSET_N_NIM for each TDC
     *          channel.
     */
    double tdc_trigger_offsets[NDIGO6G12_TDC_CHANNEL_COUNT];

    /*!
     * @brief   Configuration of the external trigger sources.
     * @details The entries in the array correspond to the definitions
     *          @link triggerdefs NDIGO6G12_TRIGGER_* @endlink.
     * @details @link ndigo6g12_trigger::threshold @endlink is ignored for
     *          index @link NDIGO6G12_TRIGGER_TDC0 @endlink and above.
     * @details @link ndigo6g12_trigger::edge @endlink and @link
     *          ndigo6g12_trigger::rising @endlink are ignored for indeces
     *          @link NDIGO6G12_TRIGGER_AUTO @endlink and
     *          @link NDIGO6G12_TRIGGER_ONE @endlink.
     */
    ndigo6g12_trigger trigger[NDIGO6G12_TRIGGER_COUNT];

    /*!
     * @brief   Trigger settings of ADC inputs.
     * @details The number of input channels depends on ADC mode.
     */
    ndigo6g12_trigger_block trigger_block[NDIGO6G12_ADC_CHANNEL_COUNT];

    /*!
     * @brief   Configuration of gating blocks
     * @details Gating blocks are used to filter trigger.
     */
    ndigo6g12_gating_block gating_block[NDIGO6G12_GATE_COUNT];

    /*!
     * @brief   THS788 related config.
     */
    ndigo6g12_tdc_configuration tdc_configuration;

    /*!
     * @brief   Averager related config.
     */
    ndigo6g12_averager_configuration average_configuration;

    /*!
     * @brief   Component to create a trigger either periodically or randomly.
     * @details To be exact, there are two parameters @f$M@f$ =
     *          @ref auto_trigger_period and @f$N@f$ =
     *          @ref auto_trigger_random_exponent that result in a distance
     *          between triggers of
     *          @f$ T = M + [1 \dots 2^N] - 1 @f$
     *          clock cycles, where
     *          @f$ 6 \le M < 2^{32} @f$ and
     *          @f$ 0 \le N < 32 @f$.
     * @details There is no enable or reset as the usage of this trigger can
     *          be configured in the channels. Each clock cycle is 5&nbsp;ns.
     * @details Default is 200000, corresponding to a 1&nbsp;kHz auto trigger.
     */
    int auto_trigger_period;

    /*!
     * @brief   Component to create a trigger either periodically or randomly.
     * @details See @ref auto_trigger_period.
     * @details Default is 0.
     */
    int auto_trigger_random_exponent;

    /*!
     * @brief   Output mode.
     * @details See @ref outputdefs "NDIGO6G12_OUTPUT_MODE_*".
     * @details Default value depends on
     *          @ref ndigo6g12_init_parameters::application_type.
     *          - @link NDIGO6G12_APP_TYPE_AVRG @endlink:
     *            @ref NDIGO6G12_OUTPUT_MODE_SIGNED32
     *          - otherwise: @ref NDIGO6G12_OUTPUT_MODE_SIGNED16.
     */
    int output_mode;

    /*!
     * @brief   Extended bandwidth.
     * @details If `true`, the input bandwidth is 6.5&nbsp;GHz instead of the
     *          default 4.5&nbsp;GHz.
     * @details Since the extended input bandwidth of the ADC influences the
     *          total bandwidth of the Ndigo6G-12 board only in a minimal
     *          manner, we recommend using the non-extended input bandwidth of
     *          4.5&nbsp;GHz. This ensures the best signal-to-noise ratio.
     * @details Default is `false`.
     */
    crono_bool_t extended_bandwidth;

    /*!
     * @brief   Default is `false`. Do not change.
     */
    crono_bool_t ramp_test_mode;

    /*!
     * @brief   Calculate sample average for multi-sampling modes
     *          @ref NDIGO6G12_ADC_MODE_AAAA "AAAA",
     *          @ref NDIGO6G12_ADC_MODE_DDDD "DDDD",
     *          @ref NDIGO6G12_ADC_MODE_AADD "AADD",
     *          @ref NDIGO6G12_ADC_MODE_AA "AA", and
     *          @ref NDIGO6G12_ADC_MODE_DD "DD"\.
     * @details Manipulate the output in multi-sampling modes.
     *          - `true`: Average all samples and combine them to a single
     *            output.
     *          - `false`: Output all samples in their own package.
     *          .
     * @verbatim embed:rst:leading-asterisk
     *          For more information, see :ref:`multiple sampling modes` in
     *          :numref:`Section %s<ADC Modes>`.
     * @endverbatim
     */
    crono_bool_t sample_averaging;
} ndigo6g12_configuration;

/*!
 * @brief   Get the driver version in integer format.
 * @return  The driver version in the same format as
 *          @link ndigo6g12_static_info::driver_revision @endlink.
 */
NDIGO6G12_API int ndigo6g12_get_driver_revision();

/*!
 * @brief   Get the driver version in string format.
 * @return  The Driver version including SVN build revision as a string
 *          with format x.y.z.svn.
 */
NDIGO6G12_API const char *ndigo6g12_get_driver_revision_str();

/*!
 * @brief   Get the number of Ndigo6G-12 boards that are installed
 *          in the system.
 * @param[out] error_code Pointer to an integer in which to store the
 *          @ref funcreturns "error code".
 * @param[out] error_message Location in which to store the error message
 *          as plain text.
 * @return  The number.
 */
NDIGO6G12_API int ndigo6g12_count_devices(int *error_code, const char **error_message);

/*!
 * @brief   Get the static information.
 * @details The static information does not change after the device
 *          initialization.
 * @param[in] device Pointer to the device from which to get the information.
 * @param[out] static_info Pointer to a structure in which to store the
 *          information.
 * @return  See @ref funcreturns "Function return values".
 */
NDIGO6G12_API int ndigo6g12_get_static_info(ndigo6g12_device *device, ndigo6g12_static_info *static_info);

/*!
 * @brief   Get parametric information.
 * @details The parametric information  may change due to the configuration.
 * @param[in] device Pointer to the device from which to get the information.
 * @param[out] param_info Pointer to a structure in which to store the
 *          information.
 * @return  See @ref funcreturns "Function return values".
 */
NDIGO6G12_API int ndigo6g12_get_param_info(ndigo6g12_device *device, ndigo6g12_param_info *param_info);

/*!
 * @brief   Get fast status information.
 * @details The information can be retrieved within a few microseconds.
 * @param[in] device Pointer to the device from which to get the information.
 * @param[out] fast_info Pointer to a structure in which to store the
 *          information.
 * @return  See @ref funcreturns "Function return values".
 */
NDIGO6G12_API int ndigo6g12_get_fast_info(ndigo6g12_device *device, ndigo6g12_fast_info *fast_info);

/*!
 * @brief   Copies the default configuration to the specified config pointer.
 * @param[in] device Pointer to the device from which to get the information.
 * @param[out] config Pointer to a structure in which to store the
 *          configuration values.
 * @return  See @ref funcreturns "Function return values".
 * @details Default values of @link ndigo6g12_configuration @endlink:
 *
 * - @ref ndigo6g12_configuration::adc_mode "adc_mode" =
 *   - @ref NDIGO6G12_ADC_MODE_A
 *     (if @ref ndigo6g12_init_parameters::application_type "application_type"
 *     = @link NDIGO6G12_APP_TYPE_1CH @endlink)
 *   - @ref NDIGO6G12_ADC_MODE_AD
 *     (if @ref ndigo6g12_init_parameters::application_type "application_type"
 *     = @link NDIGO6G12_APP_TYPE_2CH @endlink)
 *   - @ref NDIGO6G12_ADC_MODE_ABCD
 *     (if @ref ndigo6g12_init_parameters::application_type "application_type"
 *     = @link NDIGO6G12_APP_TYPE_4CH @endlink)
 *   - @ref NDIGO6G12_ADC_MODE_A
 *     (if @ref ndigo6g12_init_parameters::application_type "application_type"
 *     = @link NDIGO6G12_APP_TYPE_AVRG @endlink)
 *
 * - @ref ndigo6g12_configuration::adc_cal_set "adc_cal_set" = 3
 *
 * - @ref ndigo6g12_configuration::analog_offsets "analog_offsets[i]" = 0
 *
 * - @link ndigo6g12_configuration::tdc_trigger_offsets tdc_trigger_offsets[i]
 *   @endlink = @ref NDIGO6G12_DC_OFFSET_N_NIM
 *
 * - @ref ndigo6g12_trigger "trigger[i]":
 *   - @ref ndigo6g12_trigger.edge "edge" = `true`
 *   - @ref ndigo6g12_trigger.rising "rising" = `false`
 *   - @ref ndigo6g12_trigger.threshold "threshold" = 512
 *
 * - @ref ndigo6g12_trigger_block "trigger_block[i]":
 *   - @ref ndigo6g12_trigger_block::enabled "enabled" = `false`
 *   - @ref ndigo6g12_trigger_block::retrigger "retrigger" = `false`
 *   - @ref ndigo6g12_trigger_block::multi_shot_count "multi_shot_count" = 1
 *   - @ref ndigo6g12_trigger_block::precursor "precursor" = 0
 *   - @ref ndigo6g12_trigger_block::length "length" = 16
 *   - @ref ndigo6g12_trigger_block::sources "sources" =
 *     @ref sourcedefs "NDIGO6G12_TRIGGER_SOURCE_<channel>0"
 *   - @ref ndigo6g12_trigger_block::gates "gates" =
 *     @ref NDIGO6G12_TRIGGER_GATE_NONE
 *   - @link ndigo6g12_trigger_block::minimum_free_packets
 *     minimum_free_packets @endlink = 0
 *
 * - @ref ndigo6g12_gating_block "gating_block[i]":
 *   - @ref ndigo6g12_gating_block::negate "negate" = `false`
 *   - @ref ndigo6g12_gating_block::retrigger "retrigger" = `false`
 *   - @ref ndigo6g12_gating_block::start "start" = 0
 *   - @ref ndigo6g12_gating_block::stop "stop" = 1000
 *   - @ref ndigo6g12_gating_block::sources "sources" =
 *     @ref sourcedefs "NDIGO6G12_TRIGGER_SOURCE_<channel>0"
 *
 * - @ref ndigo6g12_tdc_configuration "tdc_configuration":
 *   - @ref ndigo6g12_tdc_configuration::channel "channel[i]":
 *        - @ref ndigo6g12_tdc_channel::enable "enable" = `false`
 *        - @ref ndigo6g12_tdc_gating_block "gating_block":
 *           - @ref ndigo6g12_tdc_gating_block::enable "enable" =
 *             `false`
 *           - @ref ndigo6g12_tdc_gating_block::negate "negate" =
 *             `false`
 *           - @ref ndigo6g12_tdc_gating_block::retrigger "retrigger" =
 *             `false`
 *           - @ref ndigo6g12_tdc_gating_block::sources "retrigger" =
 *             @ref NDIGO6G12_TRIGGER_SOURCE_AUTO
 *           - @ref ndigo6g12_tdc_gating_block::start "start" = 0
 *           - @ref ndigo6g12_tdc_gating_block::stop "stop" = 1000
 *           - @ref ndigo6g12_tdc_gating_block::sources "sources" =
 *             @ref sourcedefs "NDIGO6G12_TRIGGER_SOURCE_<channel>0"
 *        - @ref ndigo6g12_tdc_tiger_block "tiger_block":
 *           - @ref ndigo6g12_tdc_tiger_block::mode "mode" =
 *             @ref NDIGO6G12_TIGER_OFF
 *           - @ref ndigo6g12_tdc_tiger_block::negate "negate" =
 *             `true`
 *           - @ref ndigo6g12_tdc_tiger_block::retrigger "retrigger" = `false`
 *           - @ref ndigo6g12_tdc_tiger_block::sources "retrigger" =
 *             @ref NDIGO6G12_TRIGGER_SOURCE_AUTO
 *           - @ref ndigo6g12_tdc_tiger_block::start "start" = 0
 *           - @ref ndigo6g12_tdc_tiger_block::stop "stop" = 1
 *           - @ref ndigo6g12_tdc_tiger_block::sources "sources" =
 *             @ref sourcedefs "NDIGO6G12_TRIGGER_SOURCE_<channel>0"
 *   - @ref ndigo6g12_tdc_configuration::skip_alignment "skip_alignment" =
 *     `false`
 *   - @ref ndigo6g12_tdc_configuration::alignment_mode "alignment_mode" =
 *     `false`
 *   - @link ndigo6g12_tdc_configuration::alignment_pin_high_z
 *     alignment_pin_high_z@endlink = `false`
 *   - @link ndigo6g12_tdc_configuration::alignment_pin_invert
 *     alignment_pin_invert@endlink = `false`
 *   - @link ndigo6g12_tdc_configuration::alignment_phase_steps
 *     alignment_phase_steps@endlink = `12`
 *   - @link ndigo6g12_tdc_configuration::send_empty_packets
 *     send_empty_packets@endlink = `false`
 *
 * - @ref ndigo6g12_configuration::auto_trigger_period "auto_trigger_period"
 *   = 200000
 *
 * - @link ndigo6g12_configuration::auto_trigger_random_exponent
 *   auto_trigger_random_exponent @endlink = 0
 *
 * - @ref ndigo6g12_configuration::output_mode "output_mode" =
 *   - @ref NDIGO6G12_OUTPUT_MODE_SIGNED32
 *     (if @ref ndigo6g12_init_parameters::application_type "application_type"
 *     = @link NDIGO6G12_APP_TYPE_AVRG @endlink)
 *   - @ref NDIGO6G12_OUTPUT_MODE_SIGNED16 (otherwise)
 *
 * - @ref ndigo6g12_configuration::extended_bandwidth "extended_bandwidth" =
 *   `false`
 *
 * - @ref ndigo6g12_configuration::ramp_test_mode "ramp_test_mode" = `false`
 *
 */
NDIGO6G12_API int ndigo6g12_get_default_configuration(ndigo6g12_device *device, ndigo6g12_configuration *config);

/*!
 * @brief   Configures the Ndigo6G-12 device.
 * @details The config information is copied such that it can
 *          be changed after the call to @link
 *          ndigo6g12_configure @endlink.
 * @param[in] device Pointer to the device from which to get the information.
 * @param[out] config Pointer to the configuration structure.
 * @return  See @ref funcreturns "Function return values".
 */
NDIGO6G12_API int ndigo6g12_configure(ndigo6g12_device *device, ndigo6g12_configuration *config);

/*!
 * @ingroup initfuncts
 * @brief   Sets up the standard parameters.
 * @details Gets a set of default parameters for @link
 *          ndigo6g12_init() @endlink. This must always be used to
 *          initialize the @ref ndigo6g12_init_parameters structure.
 * @details For convinience, the macro
 *          @ref ndigo6g12_get_default_init_parameters is provided, which
 *          automatically sets the correct `client_api_version`.
 * @details Default values:
 *          - @ref ndigo6g12_init_parameters::card_index "card_index" = 0
 *          - @ref ndigo6g12_init_parameters::board_id "board_id" = 0
 *          - @ref ndigo6g12_init_parameters::buffer_size "buffer_size[0]" = 64 (MiB)
 *          - @ref ndigo6g12_init_parameters::buffer_size "buffer_size[1-7]" = 0 (unused)
 *          - @ref ndigo6g12_init_parameters::dma_read_delay "dma_read_delay" = 1000
 *          - @ref ndigo6g12_init_parameters::perf_derating "perf_derating" = 0
 *          - @ref ndigo6g12_init_parameters::led_flashing_mode "led_flashing_mode" = 1
 *          - @ref ndigo6g12_init_parameters::clock_source "clock_source" =
 *               @ref NDIGO6G12_CLOCK_SOURCE_INTERNAL
 *          - @ref ndigo6g12_init_parameters::application_type "application_type" =
 *               @ref NDIGO6G12_APP_TYPE_CURRENT
 *          - @link ndigo6g12_init_parameters::force_bitstream_update
 *               force_bitstream_update@endlink = `false`
 *          - @link ndigo6g12_init_parameters::partial_bitstream_size
 *               partial_bitstream_size@endlink = 0
 *          - @link ndigo6g12_init_parameters::partial_bitstream
 *               partial_bitstream@endlink = `nullptr`
 *          - @link ndigo6g12_init_parameters::firmware_locations
 *               firmware_locations@endlink = `nullptr`
 * @param[in] init Pointer to a structure in which to store the
 *          initialization values.
 * @param[in] client_api_version @link NDIGO6G12_API_VERSION @endlink
 * @return  See @ref funcreturns "Function return values".
 */
NDIGO6G12_API int ndigo6g12_get_default_init_parameters_version(ndigo6g12_init_parameters *init,
                                                                int client_api_version);

/*!
 * @brief   Macro that calls
 *          @ref ndigo6g12_get_default_init_parameters_version with
 *          the correct API version.
 */
#define ndigo6g12_get_default_init_parameters(init)                                                                    \
    ndigo6g12_get_default_init_parameters_version(init, NDIGO6G12_API_VERSION)

/*!
 * @brief   Open and initialize an Ndigo6G-12 board.
 * @details Which Ndigo6G-12 board will be initialized is
 *          determined by @link
 *          ndigo6g12_init_parameters::card_index @endlink.
 * @param[out] device Pointer to the device struct.
 * @param[in] params  Pointer to the structure that contains the
 *          initialization parameters.
 * @param[out] error_message Location in which to store the error message
 *          as plain text.
 * @return  See @ref funcreturns "Function return values".
 */
NDIGO6G12_API int ndigo6g12_init(ndigo6g12_device *device, ndigo6g12_init_parameters *params,
                                 const char **error_message);

/*!
 * @brief   Finalize the driver for this device.
 * @param[in] device Pointer to the device that should be finalized.
 * @return  See @ref funcreturns "Function return values".
 */
NDIGO6G12_API int ndigo6g12_close(ndigo6g12_device *device);

/*!
 * @brief   Reads packets from the board.
 * @details If @ref ndigo6g12_read_in::acknowledge_last_read is
 *          `true`, automatically acknowledges the last read packets.
 * @param[in] device Pointer to the device that should be read.
 * @param[in] in Pointer to the structure that configures the
 *          read call.
 * @param[out] out Pointer to a structure in which the read-out
 *          should be stored.
 * @return  See @ref funcreturns "Function return values".
 */
NDIGO6G12_API int ndigo6g12_read(ndigo6g12_device *device, ndigo6g12_read_in *in, ndigo6g12_read_out *out);

/*!
 * @brief   Gets latest error message of @b device.
 * @param[in] device Pointer to the device.
 * @return  char array containing the plain text error message.
 */
NDIGO6G12_API const char *ndigo6g12_get_last_error_message(ndigo6g12_device *device);

/*!
 * @brief   Reads the PCIe info like correctable and
 *          uncorrectable errors.
 * @param[in] device Pointer to the device.
 * @param[out] pcie_info Pointer to the structure in which to store the
 *          information.
 * @return  See @ref funcreturns "Function return values".
 */
NDIGO6G12_API int ndigo6g12_get_pcie_info(ndigo6g12_device *device, crono_pcie_info *pcie_info);

/*!
 * @brief   Clear PCIe errors.
 * @details Only useful for PCIe problem debugging flags.
 * @param[in] device Pointer to the device.
 * @param[in] flags  Specify which flags to clear.
 *          - @link CRONO_PCIE_CORRECTABLE_FLAG @endlink: clear all
 *            correctable errors
 *          - @link CRONO_PCIE_UNCORRECTABLE_FLAG @endlink: clear all
 *            uncorrectable errors
 * @return char array containing the plain text error message.
 */
NDIGO6G12_API int ndigo6g12_clear_pcie_errors(ndigo6g12_device *device, int flags);

/*!
 * @brief   Convert @b state to plain text.
 * @details The device state is stored in
 *          @link ndigo6g12_fast_info::state @endlink.
 * @param[in] state  See @link devicestates NDIGO6G12_DEVICE_STATE_* @endlink
 * @return  char array containing the state as plain text.
 */
NDIGO6G12_API const char *ndigo6g12_device_state_to_str(int state);

/*!
 * @brief   Start data acquisition.
 * @param[in] device Pointer to the device.
 * @return  See @ref funcreturns "Function return values".
 */
NDIGO6G12_API int ndigo6g12_start_capture(ndigo6g12_device *device);

/*!
 * @brief   Stop data acquisition.
 * @param[in] device Pointer to the device.
 * @return  See @ref funcreturns "Function return values".
 */
NDIGO6G12_API int ndigo6g12_stop_capture(ndigo6g12_device *device);

/*!
 * @brief   Enables manual triggering of the ADC channels.
 * @param[in] device Pointer to the device.
 * @param[in] channel_mask A bit mask that chooses which channels to trigger.
 * @return  See @ref funcreturns "Function return values".
 */
NDIGO6G12_API int ndigo6g12_manual_trigger(ndigo6g12_device *device, int channel_mask);

/*!
 * @brief   Enables single-shot recording of the ADC channels.
 * @details Instead of continously triggering on input signals, only trigger
 *          and record a @ref ndigo6g12_trigger_block::multi_shot_count number
 *          of events.
 * @details Requires that @ref ndigo6g12_trigger_block::enabled is `false`.
 * @param[in] device Pointer to the device.
 * @param[in] channel_mask A bit mask that chooses which channels to trigger.
 * @return  See @ref funcreturns "Function return values".
 */
NDIGO6G12_API int ndigo6g12_single_shot(ndigo6g12_device *device, int channel_mask);

#ifdef __cplusplus
}
#endif

#endif
