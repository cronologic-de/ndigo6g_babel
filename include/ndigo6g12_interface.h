//
// Header file containing structs and #defines specific for the Ndigo6G12
// The current driver version for Ndigo6G12 devices is 1.3.0.0
//

/*! \file
 * \brief The functions provided by the API are declared in
 * ndigo6G12_interface.h.
 *
 * The API is a DLL with C linkage.
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

#define NDIGO6G12_API_VERSION 1

//!< ADC and TDC trigger including AUTO and ONE
#define NDIGO6G12_TRIGGER_COUNT 16
//!< The number of analog input channels.
#define NDIGO6G12_ADC_CHANNEL_COUNT 4
//!< The number of gating blocks.
#define NDIGO6G12_GATE_COUNT 4

//!< The number of TDC input channels
#define NDIGO6G12_TDC_CHANNEL_COUNT 4
//!< The number of TDC gates
#define NDIGO6G12_TDC_GATE_COUNT 4
//!< The number of timing generator blocks for the TDC inputs.
#define NDIGO6G12_TDC_TIGER_COUNT 4
//!< The number of FPGA TDC input channels
#define NDIGO6G12_FPGA_TDC_CHANNEL_COUNT 2
//!< The number of timing generator blocks for the FPGA TDC inputs.
#define NDIGO6G12_FPGA_TDC_TIGER_COUNT 2

/*! \addtogroup adcdefs (ADC mode defines)
 /{ */
/*! \ingroup adcdefs
 * \brief 4 channel mode at sample rate 1600 Msps
 */
#define NDIGO6G12_ADC_MODE_ABCD 0
/*! \ingroup adcdefs
 * \brief 4 channel mode at sample rate 1600 Msps
 */
#define NDIGO6G12_ADC_MODE_AADD 1
/*! \ingroup adcdefs
 * \brief 4 channel mode at sample rate 1600 Msps
 */
#define NDIGO6G12_ADC_MODE_AAAA 2
/*! \ingroup adcdefs
 * \brief 4 channel mode at sample rate 1600 Msps
 */
#define NDIGO6G12_ADC_MODE_DDDD 3
/*! \ingroup adcdefs
 * \brief 2 channel mode at sample rate 3200 Msps
 */
#define NDIGO6G12_ADC_MODE_AD 4
/*! \ingroup adcdefs
 * \brief 2 channel mode at sample rate 3200 Msps
 */
#define NDIGO6G12_ADC_MODE_AA 5
/*! \ingroup adcdefs
 * \brief 2 channel mode at sample rate 3200 Msps
 */
#define NDIGO6G12_ADC_MODE_DD 6
/*! \ingroup adcdefs
 * \brief 1 channel mode at sample rate 6400 Msps
 */
#define NDIGO6G12_ADC_MODE_A 7
/*! \ingroup adcdefs
 * \brief 1 channel mode at sample rate 6400 Msps
 * \}
 */
#define NDIGO6G12_ADC_MODE_D 8
/*! \ingroup outputdefs
 *	\brief Native range
 *
 *	Return the native range 0 - 4095
 */
#define NDIGO6G12_OUTPUT_MODE_RAW 0
/*! \ingroup outputdefs
 *	\brief Output in signed16 integer format.
 *
 * Return output in the range -32768 to 32767
 */
#define NDIGO6G12_OUTPUT_MODE_SIGNED16 1
/*! \ingroup outputdefs
 *	\brief Output in signed32 integer format.
 * Only applicable for averaging mode.
 *
 * Return output in the range -(2^31) to 2^31 - 1
 */
#define NDIGO6G12_OUTPUT_MODE_SIGNED32 2

/*! \ingroup gatedefs
 * Bitmask for configuration of gates
 */
#define NDIGO6G12_TRIGGER_GATE_NONE 0x0000
#define NDIGO6G12_TRIGGER_GATE_0 0x0001
#define NDIGO6G12_TRIGGER_GATE_1 0x0002
#define NDIGO6G12_TRIGGER_GATE_2 0x0004
#define NDIGO6G12_TRIGGER_GATE_3 0x0008

// Bit definitions for trigger sources used in timing generator
// and gating configuration all sources disabled
#define NDIGO6G12_TRIGGER_SOURCE_NONE 0x00000000
// trigger source is ADC input A0, A1, ..., D1
#define NDIGO6G12_TRIGGER_SOURCE_A0 0x00000001
#define NDIGO6G12_TRIGGER_SOURCE_A1 0x00000002
#define NDIGO6G12_TRIGGER_SOURCE_B0 0x00000004
#define NDIGO6G12_TRIGGER_SOURCE_B1 0x00000008
#define NDIGO6G12_TRIGGER_SOURCE_C0 0x00000010
#define NDIGO6G12_TRIGGER_SOURCE_C1 0x00000020
#define NDIGO6G12_TRIGGER_SOURCE_D0 0x00000040
#define NDIGO6G12_TRIGGER_SOURCE_D1 0x00000080
// trigger source is TDC input TDC0, TDC1, TDC2, TDC3
#define NDIGO6G12_TRIGGER_SOURCE_TDC0 0x00000100
#define NDIGO6G12_TRIGGER_SOURCE_TDC1 0x00000200
#define NDIGO6G12_TRIGGER_SOURCE_TDC2 0x00000400
#define NDIGO6G12_TRIGGER_SOURCE_TDC3 0x00000800
// trigger source is input FPGA0, FPGA1
#define NDIGO6G12_TRIGGER_SOURCE_FPGA0 0x00001000
#define NDIGO6G12_TRIGGER_SOURCE_FPGA1 0x00002000
// trigger source is autotrigger module
#define NDIGO6G12_TRIGGER_SOURCE_AUTO 0x00004000
// trigger signal active each clock cycle
#define NDIGO6G12_TRIGGER_SOURCE_ONE 0x00008000

/*! \ingroup triggerdefs
 *  Index for configuration of the triggers
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

/*! \ingroup tigerdefs
 *  Index for configuration of the TiGers
 */
#define NDIGO6G12_TIGER_TDC0 0
#define NDIGO6G12_TIGER_TDC1 1
#define NDIGO6G12_TIGER_TDC2 2
#define NDIGO6G12_TIGER_TDC3 3
#define NDIGO6G12_TIGER_FPGA0 4
#define NDIGO6G12_TIGER_FPGA1 5

/*! \ingroup defdcoffset
 *
 */
#define NDIGO6G12_DC_OFFSET_N_NIM -0.35

/**
 * Device states
 * A device must be configured before data capturing is started.
 */
// device is created but not yet initialized
#define NDIGO6G12_DEVICE_STATE_CREATED CRONO_DEVICE_STATE_CREATED
// device is initialized but not yet configured for data capture
#define NDIGO6G12_DEVICE_STATE_INITIALIZED CRONO_DEVICE_STATE_INITIALIZED
// device is ready to capture data
#define NDIGO6G12_DEVICE_STATE_CONFIGURED CRONO_DEVICE_STATE_CONFIGURED
// device has started data capture
#define NDIGO6G12_DEVICE_STATE_CAPTURING CRONO_DEVICE_STATE_CAPTURING
// data capture is paused
#define NDIGO6G12_DEVICE_STATE_PAUSED CRONO_DEVICE_STATE_PAUSED
// device is closed
#define NDIGO6G12_DEVICE_STATE_CLOSED CRONO_DEVICE_STATE_CLOSED

/*! \ingroup devicestruct
 *   \brief contains information on the current device.
 */
typedef struct {
    bool is_valid;
    void *ndigo6g12;
} ndigo6g12_device;

/*! \ingroup initparamsstruct
 *   \brief struct for the initialization of the Ndigo6G12
 *
 *   this structure MUST be completely INITIALIZED
 */
typedef struct {
    /*! \brief the version number
     *   that is increased when the definition of the structure is changed. The
     * increment can be larger than one to match driver version numbers or
     * similar. Set to 0 for all versions up to first release.
     *
     *   must be set to @link apiversion NDIGO6G12_API_VERSION @endlink
     */
    int version;
    /*! \brief The index in the list of Ndigo6G12 boards that should be
     * initialized.
     *
     *   There might be multiple boards in the system that are handled by this
     * driver as reported by @link initialization ndigo6g12_count_devices()
     * @endlink. This index selects one of them. Boards are enumerated depending
     * on the PCIe slot. The lower the bus number and the lower the slot number
     * the lower the card index.
     */
    int card_index;
    /*! \brief the global index in all cronologic devices
     *
     *   This 8 bit number is filled into each packet created by the board and
     * is useful if data streams of multiple boards will be merged. If only
     * Ndigo6G12 cards are used this number can be set to the
     *   @link card_index card_index @endlink. If boards of different types that
     * use a compatible data format are used in a system each board should get a
     * unique id.
     */
    int board_id;
    /*! \brief The minimum size of the DMA buffer.
     *
     *   If set to 0 the default size of 64 MiBytes is used.
     *   For the Ndigo6G12 only the first entry is used.
     */
    int64_t buffer_size[8];
    /*! \brief The update delay of the writing pointer after a packet has been
     * send over PCIe.
     *
     *   Default: 8192. Do not change.
     */
    int dma_read_delay;

    /*!
     * Default 0: 1.6/3.2/6.4 Gsps. Do not change.
     */
    int perf_derating;

    /*!
     * 0: off
     * 1: light all colors once
     * 2:
     * 3:
     */
    int led_flashing_mode;

    /*!
     * Mask with a bit set for each enabled ADC channel.
     * Default: all channels enabled. Do not change.
     */
    int adc_channel_mask;

    /*!
     * Default is false. Do not change.
     */
    crono_bool_t no_reference_clock;

    /*!
     * Use external 10 MHz clock as reference.
     * Input is internal SMA or external LEMO connector
     * depending on use_aux2_clock.
     *
     * Default is false.
     */
    crono_bool_t use_external_clock;

    /*!
     * If enabled use slot bracket LEMO as external
     * reference clock input.
     * Otherwise, the internal SMA connector is used.
     * Has no effect if use_external_clock is false.
     *
     * Default is false.
     */
    crono_bool_t use_aux2_clock;

    /*!
     * Default is false. Do not change.
     */
    crono_bool_t ignore_lane_errors;

    /*!
     * Default is false. Do not change.
     */
    crono_bool_t ignore_clock_errors;

    /*!
     * Default is false. Do not change.
     */
    crono_bool_t adc_full_swing;

    /*!
     * Select four, two or one channel, or averaging mode.
     * 0: use currently installed type
     * 1: one ADC channel @6.4 Gsps
     * 2: two ADC channels @3.2 Gsps
     * 4: four ADC channels @1.6 Gsps
     * 5: averaging mode
     */
    int application_type;

    /*!
     * Update partial bitstream even if application type matches.
     */
    crono_bool_t force_bitstream_update;

    /*!
     * Size of partial bitstream
     */
    int partial_bitstream_size;

    /*!
     * Pointer to buffer with partial bitstream data. Can be nullptr if
     * application_type matches application_type of currently installed
     * firmware.
     */
    uint32_t *partial_bitstream;

    /*!
     * Pointer to a list of paths (separated by ;) Can be nullptr if
     * application_type matches application_type of currently installed
     * firmware.
     */
    const char *firmware_locations;

} ndigo6g12_init_parameters;

/*! \ingroup paraminfo
 *   \brief contains configuration changes
 *
 *   Structure filled by @link statfuncts ndigo6g12_get_param_info() @endlink.
 * This structure contains information that change indirectly due to
 * configuration changes.
 */
typedef struct {
    /*! \brief The number of bytes occupied by the structure
     */
    int size;

    /*! \brief A version number
     *
     * that is increased when the definition of the structure is changed. The
     * increment can be larger than one to match driver version numbers or
     * similar. Set to 0 for all versions up to first release.
     */
    int version;

    /*! \brief Bandwidth.
     *
     * 4.5 or 6.5 GHz depending on configuration
     */
    double bandwidth;

    /*! \brief ADC sample resolution
     *   always 12 bit
     */
    int resolution;

    /*! \brief Actual ADC sample rate of currently sampled data.
     *
     * depending on ADC mode: sample_rate = 6.4GHz/#channels.
     */
    double sample_rate;

    /*! \brief The period one sample in the data represents in picoseconds
     */
    double sample_period;

    /*! \brief The period one TDC bin in the data represents in picoseconds
     */
    double tdc_period;

    /*! \brief The period one tick of the packet timestamp represents in
     * picoseconds
     */
    double packet_ts_period;

    /*! /brief TDC packets carry the timestamp of the end of packet.
     *  To calculate the start substract the offset.
     */
    uint64_t tdc_packet_timestamp_offset;

    /*! \brief Time span in TDC bins of one TDC timestamp rollover period.
     */
    uint32_t tdc_rollover_period;

    /*! \brief The delay of the ADC samples due to pipelining in picoseconds
     */
    double adc_sample_delay;

    /*! \brief the ID the board uses to identify itself in the output data
     * stream.
     *
     * takes values 0 to 255.
     */
    int board_id;

    /*!\brief Number of ADC channels in the current mode
     */
    int channels;

    /*! \brief Mask with a set bit for each enabled input channel.
     */
    int channel_mask;

    /*!\brief Number of TDC channels in the current mode
     */
    int tdc_channels;

    /*! \brief The total amount of the DMA buffer in bytes
     */
    int64_t total_buffer;
} ndigo6g12_param_info;

// bitstream date format: YYYY-MM-DD hh:mm:ss
#define NDIGO6G_BITSTREAM_DATE_LEN 20
// calibration date format: YYYY-MM-DD hh:mm
#define NDIGO6G_CALIBRATION_DATE_LEN 20
// length of ndigo6G12 flash signature
#define NDIGO6G_FLASH_SIG_LEN 60

// application types
// averaging mode
#define NDIGO6G_APP_TYPE_AVRG 5
// four ADC channels @1.6 Gsps
#define NDIGO6G_APP_TYPE_4CH 4
// two ADC channels @3.2 Gsps
#define NDIGO6G_APP_TYPE_2CH 2
// one ADC channel @6.4 Gsps
#define NDIGO6G_APP_TYPE_1CH 1

/**
 * Structure contains static information.
 *
 * This structure contains information about the board that does not change
 * during run time. It is provided by the function ndigo6g12_get_static_info().
 */
typedef struct {
    /*! \brief The number of bytes occupied by the structure
     */
    int size;

    /*! \brief A version number
     *
     * that is increased when the definition of the structure is changed. The
     * increment can be larger than one to match driver version numbers or
     * similar. Set to 0 for all versions up to first release.
     */
    int version;
    /**
     * Bitstream creation date
     *
     * DIN EN ISO 8601 string YYYY-MM-DD HH:DD:SS describing the time when the
     * bitstream was created.
     */
    char bitstream_date[NDIGO6G_BITSTREAM_DATE_LEN];
    /**
     * Describes the schematic configuration of the board.
     *
     * The same board schematic can be populated in multiple variants.
     * This is a eight bit-code that can be read from a register.
     */
    int board_configuration;
    /**
     * Board revision number.
     *
     * The board revision number can be read from a register. It is a four
     * bit number that changes when the schematic of the board is changed.
     * - 0: Experimental first board Version. Labeled "Rev. 1"
     * - 2: First commercial Version. Labeled "Rev. 2"
     */
    int board_revision;
    /**
     * Serial number
     *
     * With year and running number in 8.24 format. The number is identical
     * to the one printed on the silvery sticker on the board.
     */
    int board_serial;
    /**
     * Calibration date
     *
     * DIN EN ISO 8601 string YYYY-MM-DD HH:DD describing the time when the
     * card was calibrated.
     */
    char calibration_date[NDIGO6G_CALIBRATION_DATE_LEN];
    /**
     * 16bit factory ID of the ADC chip.
     *
     * This is the chipID as read from the 16 bit ADC chip id register.
     */
    int chip_id;
    /**
     * Shows if the inputs are dc-coupled.
     * Default is ac-coupled
     */
    crono_bool_t dc_coupled;
    /**
     * Encoded version number for the driver.
     *
     * The lower three bytes contain a triple level hierarchy of version
     * numbers. E.g. 0x010103 codes version 1.1.3.
     *
     * A change in the first digit generally requires a recompilation of
     * user applications. Change in the second digit denote significant
     * improvements or changes that don't break compatibility and the third
     * digit changes with minor bugfixes and the like.
     */
    int driver_revision;
    /**
     * The build number of the driver according to cronologic's internal
     * versioning system.
     */
    int driver_build_revision;
    /**
     * Calibration data read from flash is valid.
     *
     * If not 'false', the driver found valid calibration data in the flash
     * on the board and is using it.
     */
    crono_bool_t flash_valid;
    /**
     * Revision number of the FPGA configuration
     */
    int fw_revision;
    /**
     * Type of firmware, always 5 -> Ndigo6G-12.
     */
    int fw_type;
    /**
     * Trenz serial number
     */
    int pcb_serial;
    /**
     * Subversion revision id of the FPGA configuration.
     *
     * A number to track builds of the firmware in more detail than the
     * firmware revision. It changes with every change in the firmware, even
     * if there is no visible effect for the user. The subversion revision
     * number can be read from a register.
     */
    int svn_revision;
    /*!
     * Shows the initialized mode
     * 1: one ADC channel @6.4 Gsps
     * 2: two ADC channels @3.2 Gsps
     * 4: four ADC channels @1.6 Gsps
     * 5: averaging mode
     * See NDIGO6G_APP_TYPE_* constants
     */
    int application_type;
    /*!
     * Shows the signature of the primary flash
     */
    char config_flash_signature_primary[NDIGO6G_FLASH_SIG_LEN];
    /*!
     * Shows the signature of the secondary flash
     */
    char config_flash_signature_secondary[NDIGO6G_FLASH_SIG_LEN];
} ndigo6g12_static_info;

typedef struct {
    /*! \brief The number of bytes occupied by the structure
     */
    int size;

    /*! \brief A version number
     *
     * that is increased when the definition of the structure is changed. The
     * increment can be larger than one to match driver version numbers or
     * similar. Set to 0 for all versions up to first release.
     */
    int version;

    /**
     * The current state of the device.
     * Should be one of the values NDIGO6G12_DEVICE_STATE_*
     */
    int state;

    /**
     * Speed of the FPGA fan in rounds per minute.
     *
     * Reports 0, if no fan is present.
     */
    int fan_speed;

    /**
     * Temperature of the FPGA in C.
     */
    double fpga_temperature;

    /**
     * Internal Voltage of the FPGA .
     */
    double fpga_vccint;
    /**
     * Auxillary Voltage of the FPGA .
     */
    double fpga_vccaux;
    /**
     * BRAM Voltage of the FPGA .
     */
    double fpga_vccbram;

    /**
     * Shows measured Voltage for the mgt_0v9 supply
     */
    double mgt_0v9;
    /**
     * Shows measured Voltage for the mgt_1v2 supply
     */
    double mgt_1v2;
    /**
     * Shows measured Voltage for the 2v5 supply
     */
    double adc_2v5;
    /**
     * Shows measured Voltage for the clk_3v3 supply
     */
    double clk_3v3;
    /**
     * Shows measured Voltage for the adc_3v3 supply
     */
    double adc_3v3;
    /**
     * Shows measured Voltage for the pcie_3v3 supply
     */
    double pcie_3v3;
    /**
     * Shows measured Voltage for the opamp_5v2 supply
     */
    double opamp_5v2;
    /**
     * Shows temperature of temp4633_1 in C
     */
    double temp4633_1;
    /**
     * Shows temperature of temp4633_2 in C
     */
    double temp4633_2;
    /**
     * Shows temperature of temp4644 in C
     */
    double temp4644;

    /**
     * Temperature of the TDC in C.
     */
    double tdc1_temp;

    /**
     * Shows voltage for ev12_cmiref supply. Measured or calibration target
     * depending on board revision and assembly variant.
     */
    double ev12_cmiref;

    /**
     * Temperature of the ADC in C.
     */
    double ev12_temp;

    /**
     * Alert bits from temperature sensor and the system monitor.
     *
     * Bit 0 is set if the TDC temperature exceeds 140 C. In this case the
     * TDC did shut down and the device needs to be reinitialized.
     */
    int alerts;

    /**
     * Number of PCIe lanes the card uses.
     * Should always be 8 for the Ndigo6G12.
     */
    int pcie_link_width;

    /**
     * Data rate of the PCIe card.
     * Should always be x for the Ndigo6G12.
     */
    int pcie_link_speed;

    /**
     * Maximum size for a single PCIe transaction in bytes. Depends on
     * system configuration.
     */
    int pcie_max_payload;

    /**
     * ADC data clock is PLL locked
     */
    crono_bool_t adc_data_pll_locked;

    /**
     * ADC data clock PLL lost lock  (Sticky Bit)
     */
    crono_bool_t adc_data_pll_lost_lock;

    /**
     * Shows the synced ADC lanes
     * each bit corresponds to one lane
     */
    int adc_lanes_synced;

    /**
     * Shows the ADC lanes that lost sync
     * each bit corresponds to one lane
     */
    int adc_lanes_lost_sync;

    /**
     * Shows which ADC lanes have an empty FIFO
     * each bit corresponds to one lane
     */
    int adc_lanes_fifo_empty;

    /**
     * Shows which ADC lanes have a full FIFO
     * each bit corresponds to one lane
     */
    int adc_lanes_fifo_full;

    /**
     * Shows which ADC lanes are running
     * each bit corresponds to one lane
     */
    int adc_lanes_running;

    /**
     * Shows which ADC lanes were unable to sync before a timeout
     * each bit corresponds to one lane
     */
    int adc_lanes_sync_timeout;

    /**
     * The number of ADC lane synchronization retries
     * Default is set to 0
     */
    int adc_sync_retry_count;

    /**
     * The number of ADC strobe synchronization retries
     * Default is set to 0
     */
    int adc_sync_strobe_retry_count;

    /**
     * 16 Bit number showing when the last ADC lane synchronization was achieved
     *
     */
    int adc_sync_delay_count;

    /**
     * Shows if the supplied mgt power is sufficient
     *
     */
    crono_bool_t adc_mgt_power_good;

    /**
     * Shows if lmk_pll1 is locked
     */
    crono_bool_t lmk_pll1_locked;

    /**
     * Shows if lmk_pll2 is locked
     */
    crono_bool_t lmk_pll2_locked;

    /**
     * Shows if lmk lost lock
     */
    crono_bool_t lmk_lost_lock;

    /**
     * Wait count of the lmk
     */
    int lmk_lock_wait_count;

    /**
     *
     */
    int lmk_ctrl_vcxo;

    /**
     * lmx locked
     */
    crono_bool_t lmx_locked;

    /**
     * lmx lost lock
     */
    crono_bool_t lmx_lost_lock;

    int lmx_lock_wait_count;

} ndigo6g12_fast_info;

/*! \ingroup readin
 *   \brief The parameters of the read commands
 */
typedef struct {
    crono_bool_t
        acknowledge_last_read; //!< ndigo6g12_read automatically acknowledges
                               //!< packets from the last read
} ndigo6g12_read_in;

/*! \ingroup strucreadout
 *   \brief struct for the read out of the Ndigo6G12 packets
 */
typedef struct {
    /*! \brief pointer to the first packet
     *
     *   that was captured by the call of @link readout ndigo6g12_read @endlink
     */
    volatile crono_packet *first_packet;
    /*! \brief The packet after the last one
     *
     *   this is not a valid packet
     */
    volatile crono_packet *last_packet;
    /*! \brief error code
     *
     *   The assignments of the error codes can be found @link deferror here
     * @endlink.
     */
    int error_code;
    /*! \brief error message
     */
    const char *error_message;
} ndigo6g12_read_out;

typedef struct {
    /*! \brief Threshold of both triggers in trigger block ADC-counts.
     *
     * Sets the threshold for the trigger block within the range of the ADC data
     * of -32768 and +32768.
     *
     * For trigger indices @link triggerdefs NDIGO6G12_TRIGGER_TDC @endlink to
     * @link triggerdefs NDIGO6G12_TRIGGER_ONE @endlink the threshold is
     * ignored.
     *
     *  Valid values depend on output mode:
     *  - @link outputdefs NDIGO6G12_OUTPUT_MODE_RAW @endlink : 0 to 4096
     *  - @link outputdefs NDIGO6G12_OUTPUT_MODE_SIGNED16 @endlink : -32768 to
     * 32767
     */
    short threshold;

    /*! \brief sets edge trigger functionality
     *
     * else this is a level trigger:
     *       - 0: level trigger
     *       - 1: edge trigger
     *
     * For trigger indices @link triggerdefs NDIGO6G12_TRIGGER_AUTO @endlink and
     * @link triggerdefs NDIGO6G12_TRIGGER_ONE @endlink this is ignored.
     *
     * The edge trigger triggers as soon as its set threshold is crossed by the
     * signal. Thus the roots in reference to the threshold are recorded. The
     * level trigger triggers as long as the signal is above or below the set
     * threshold. Followingly the trigger gives the sign of the signal in
     * reference to the threshold.
     */
    crono_bool_t edge;
    /*! \brief sets rising edge trigger functionality
     *
     * if set, triggers on rising edges or when threshold is exceeded:
     * 0 - falling edge
     * 1 - rising edge
     *
     * for the level trigger:
     * 0 - triggers parts of the signal above the threshold
     * 1 - triggers parts of the signal below the threshold
     *
     * For trigger indices @link triggerdefs NDIGO6G12_TRIGGER_AUTO @endlink and
     * @link triggerdefs NDIGO6G12_TRIGGER_ONE @endlink this is ignored.
     */
    crono_bool_t rising;

    crono_bool_t
        enable_rand; //!< use random bits for undefined LSBs of timestamp
} ndigo6g12_trigger;

/*! \ingroup ndigotrgblock
 *   \brief configuration of the trigger block
 */
typedef struct {
    crono_bool_t enabled; //!< Activates triggers on this channel.

    /*! \brief enable retrigger
     *
     * If a new trigger condition occurs while the postcursor is acquired the
     * packet is extended by starting a new postcursor. Otherwise the new
     * trigger is ignored and the packet ends after the precursor of the first
     * trigger.
     */
    crono_bool_t retrigger;

    /*! \brief Number of packets created in single shot mode before packet
     * generation stops. Maximum is
     *   @link multishotdef NDIGO6G12_MAX_MULTISHOT @endlink
     */
    int multi_shot_count;

    /*! \brief Precursor in multiples of 5ns.
     * The amount of data preceding a trigger that is captured. Maximum is set
     * by @link precursordef NDIGO6G12_MAX_PRECURSOR @endlink.
     */
    int precursor;

    /*! \brief Length in multiples of 5ns.
     *
     * The total amount of data that is recorded in addition to the trigger
     * window.  Precursor determines how many of these are ahead of the trigger
     * and how many are appended after the trigger. In edge trigger mode the
     * trigger window always is 5ns wide, in level trigger mode it is as long as
     * the trigger condition is fulfilled.
     */
    int length;

    /*! \brief A @link sourcedefs bit mask @endlink with a bit set for all
     * trigger sources that can trigger this channel.
     *
     * Default @link sourcedefs NDIGO6G12_TRIGGER_SOURCE_x @endlink (x = 0 for
     * index 0 etc)
     */
    int sources;

    /*! \brief A @link gatedefs bit mask @endlink with a bit set for all trigger
     * gates
     *
     * Mask which selects the gates that have to be 1 for the trigger block to
     * use Default
     * @link gatedefs NDIGO6G12_TRIGGER_GATE_NONE @endlink
     */
    int gates;

    /*! \brief number of packets that fit into the FIFO
     *
     * This parameter sets how many packets are supposed to fit into the
     * on-board FIFO before a new  packet is recorded after the FIFO was full,
     * i.e. a certain amount of free space in the FIFO is demanded before a new
     * packet is written after the FIFO was full. As a measure for the packet
     * length the gatelength set by the user is used. The on-board algorithm
     * checks the free FIFO space only in case the FIFO is full. Therefore, if
     * this number is 1.0 or more at least every second packet in the DMA buffer
     * is guaranteed to have the full length set by the gatelength parameters.
     * In many cases smaller values will also result in full length packets. But
     * below a certain value multiple packets that are cut off at the end will
     * show up.
     */
    double minimum_free_packets;
} ndigo6g12_trigger_block;

/*! \ingroup ndigogat Structure ndigo6g12_gating_block
 *   \brief contains settings of the gating block
 */
typedef struct {
    crono_bool_t negate; //!< Invert output polarity. Defaults to false.

    /*!\brief enable retrigger
     *
     * Defaults to false. If retriggering is enabled the timer is reset to the
     * value of the start parameter, whenever the input signal is set while
     * waiting to reach the stop time.
     */
    crono_bool_t retrigger;

    /*! \brief The time from the first input signal seen in the idle state until
     * the gating output is set.
     *
     * In multiples of 5ns. Start needs to be >=0 and <2^16, start must be set
     * to a value <=stop.
     */
    int start;

    /*! \brief The number of samples from leaving the idle state until the
     * gating output is reset.
     *
     * If retriggering is enabled the timer is reset to the value of the start
     * parameter whenever the input signal is set while waiting to reach the
     * stop time. In multiples of 5ns. Stop needs to be >=0 and <2^16.
     */
    int stop;

    /*! \brief @link sourcedefs bit mask @endlink with a bit set for all trigger
     * sources that can trigger this channel.
     *
     * Default is @link sourcedefs NDIGO6G12_TRIGGER_SOURCE_x0 @endlink (0 for
     * index 0 etc).
     */
    int sources;
} ndigo6g12_gating_block;

/*! \ingroup avrgcfg
 *   \brief Contains averaging settings
 */
typedef struct {
    /*! \brief Set the number of trigger events that are averaged
     *
     *    Must be 0 if no averaging application is installed on the Ndigo6G12.
     *
     */
    int iterations;

    /*! \brief Stops averaging before overflow can happen
     *
     *  Stops the averaging once AVERAGING_VALUE >=
     * (MAX_AVERAGING_VALUE-MAX_ADC_VALUE) to prevent overflow
     *
     */
    crono_bool_t stop_on_overflow;

    /*! \brief Stops the averaging manually
     *
     *  Software stop for averaging. If an averaging iteration has already
     * started it is finished before the averaging stops.
     *
     */
    crono_bool_t stop_manual;

    /*! \brief Use saturation artihmetic
     *
     *  Determines if saturation arithmetic is used by averager
     *
     */
    crono_bool_t use_saturation;

    /*! \brief Stops the averaging on timeout
     *
     *  Stop averaging on configurable timeout
     *
     */
    crono_bool_t stop_on_timeout;

    /*! \brief Set the number microseconds until timeout
     *
     *    Must be 0 if no averaging application is installed on the Ndigo6G12.
     *
     */
    int timeout_threshold;
} ndigo6g12_averager_configuration;

/*! \ingroup channel
 *   \brief Contains TDC channel settings
 */
typedef struct {
    crono_bool_t enable; //!< Enable TDC channel.
    crono_bool_t rising; //!< Set whether to record rising or falling edges.
} ndigo6g12_tdc_channel;

/*! \ingroup gating
 *   \brief contains settings of gating block
 */
typedef struct {
    //!< activates gating block
    crono_bool_t enable;
    /*! \brief inverts output polarity
     *
     *   default is set to false.
     */
    crono_bool_t negate;
    /*! \brief enables/disables retrigger setting
     *
     *   Default is set to false. If retriggering is enabled the timer is reset
     * to the value of the start parameter, whenever the input signal is set
     * while waiting to reach the stop time.
     */
    crono_bool_t retrigger;

    // default is true
    //!< not implemented
    crono_bool_t extend;

    /*! \brief Precursor
     *
     *  Number of 5ns clock cycles before the tiger output goes active
     *       relative to the trigger signal.
     */
    int start;
    /*! \brief postcursor
     *
     *   Number of 5ns clock cycles before the tiger output goes inactive
     *   relative to the trigger signal.
     */
    int stop;
    /*! \brief mask for choosing the trigger source
     *
     *   A bit mask with a bit set for all trigger sources that can trigger this
     * channel. Default is NDIGO6G12_TRIGGER_SOURCE_A. One can choose a from a
     * source @link deftriggersource here @endlink.
     */
    int sources;
} ndigo6g12_tdc_gating_block;

/*! \ingroup gating
 *   \brief contains settings of gating block
 */
typedef struct {
    /*! \brief activates tiger block
     *
     *  TiGer output buffer is tristated if not enabled
     *
     *  default value: false
     */
    crono_bool_t enable;
    /*! \brief set pulse polarity
     *
     *   default value: false
     */
    crono_bool_t negate;
    /*! \brief enables/disables retrigger setting
     *
     *   If retriggering is enabled the timer is reset to the value of the start
     *   parameter, whenever the input signal is set while waiting to reach the
     * stop time.
     *
     *   default value: false
     */
    crono_bool_t retrigger;
    /*! \brief if set output buffer is constantly enabled resulting in larger
     * swing
     *
     *   default value: false.
     */
    crono_bool_t pulse_mode;
    /*! /brief enables the pin output
     *
     *   enabled by default, TiGer without pin output wouldn't do anything with
     * current firmware
     */
    crono_bool_t enable_output;
    /*! \brief Precursor
     *
     *   Number of 5ns clock cycles before the tiger output goes active
     *   relative to the trigger signal.
     */
    int start;
    /*! \brief postcursor
     *
     *   Number of 5ns clock cycles before the tiger output goes inactive
     *   relative to the trigger signal.
     */
    int stop;
    /*! \brief mask for choosing the trigger source
     *
     *   A bit mask with a bit set for all trigger sources that can trigger this
     * channel. Default is NDIGO6G12_TRIGGER_SOURCE_A. One can choose a from a
     * source @link deftriggersource here @endlink.
     */
    int sources;
} ndigo6g12_tdc_tiger_block;

/*! \ingroup confstruct Structure ndigo6g12_configuration
 *   \brief  contains configuration information
 *
 *   This structure contains the configuration information. It is used in
 * conjunction with
 *   @link conffuncts ndigo6g12_get_default_configuration(),
 * ndigo6g12_get_current_configuration() and ndigo6g12_configure() @endlink
 *
 *   Internally it uses the structures @link trigger ndigo6g12_trigger @endlink
 * and @link tiger ndigo6g12_tiger_block @endlink
 */
typedef struct {
    //!< configuration of the gating blocks
    ndigo6g12_tdc_gating_block gating_block[NDIGO6G12_TDC_GATE_COUNT];
    //!< configuration of the timing generator blocks
    ndigo6g12_tdc_tiger_block
        tiger_block[NDIGO6G12_TDC_TIGER_COUNT + NDIGO6G12_FPGA_TDC_TIGER_COUNT];
    //!< configure polaritiy, type and threshold for the TDC channels
    ndigo6g12_tdc_channel channel[NDIGO6G12_TDC_CHANNEL_COUNT];

    /*! \brief Configure THS788 calibration.
     *
     *  If set to 1 skip THS788 calibration.
     *  If set to 0 do THS788 calibration (default).
     */
    crono_bool_t skip_alignment;

    /*!
     * Align TDC channels
     */
    crono_bool_t alignment_mode;

    /*!
     */
    crono_bool_t alignment_pin_high_z;

    /*!
     */
    crono_bool_t alignment_pin_invert;

    /*!
     */
    int alignment_phase_mask;

    /*!
     */
    crono_bool_t send_empty_packets;
} ndigo6g12_tdc_configuration;

typedef struct {
    /*! \brief size in bytes
     *
     * The number of bytes occupied by the structure.
     */
    int size;

    /*! \brief The version number
     *
     * that is increased when the definition of the structure is changed. The
     * increment can be larger than one to match driver version numbers or
     * similar. Set to 0 for all versions up to first release.
     */
    int version;

    /*! \brief ADC mode
     *
     * as defined in @link adcdefs NDIGO6G12_ADC_MODE_* @endlink
     */
    int adc_mode;

    /*! \brief Select ADC calibration set
     * default: 3 Do not change.
     */
    int adc_cal_set;

    /*! \brief analog input configuration
     * 0: ADC A
     * 1: ADC B
     * 2: ADC C
     * 3: ADC D
     */
    double analog_offsets[NDIGO6G12_ADC_CHANNEL_COUNT];

    /*! \brief Set DAC for trigger threshold of TDC inputs.
    *
    *       0 - 3: THS788 A - D
    *       4 : FGPA TDC A
    *       5 : FGPA TDC B
    *
    *       Set to a value between -1.65V and +0.85V. This should be close to
    50% of the height of your pulses on
    *       the inputs. Examples for various signaling standards are defined in
    @link defdcoffset #defines for
    *       dc_offset @endlink. The inputs are AC coupled. This means that for
    pulse inputs the absolute voltage is
    *       not important. it is rather the relative pulse amplitude that causes
    the input circuits to switch.
    *       dc_offset for an input must be set to the relative switching voltage
    for the input standard in use. If
    *       the pulses are negative, a negative switching threshold must be set
    and vice versa.
    */
    double tdc_trigger_offsets[NDIGO6G12_TDC_CHANNEL_COUNT +
                               NDIGO6G12_FPGA_TDC_CHANNEL_COUNT];

    /*! \brief Configuration of the external trigger sources.
     *
     * Threshold is ignored for entries 8 and above. The trigger indeces refer
     * to the entry in the trigger array @link triggerdefs NDIGO6G12_TRIGGER_*
     * @endlink
     */
    ndigo6g12_trigger trigger[NDIGO6G12_TRIGGER_COUNT];

    /*! \brief Trigger settings of ADC inputs.
     *
     * The number of input channels depends on TDC mode.
     */
    ndigo6g12_trigger_block trigger_block[NDIGO6G12_ADC_CHANNEL_COUNT];

    /*! \brief Configuration of gating blocks
     *
     * Gating blocks are used to filter trigger.
     */
    ndigo6g12_gating_block gating_block[NDIGO6G12_GATE_COUNT];

    /*! \brief THS788 related config
     *
     *
     */
    ndigo6g12_tdc_configuration tdc_configuration;

    /*! \brief averager related config
     *
     *
     */
    ndigo6g12_averager_configuration average_configuration;

    /** \brief component to create a trigger either periodically or randomly.
     *
     * To be exact, there are two parameters M = @link auto_trigger_period
     * auto_trigger_period @endlink and N = @link auto_trigger_random_exponent
     * auto_trigger_random_exponent @endlink that result in a distance between
     * triggers of
     *
     * T = 1 + M + [1...2^N]
     *
     * clock cycles.
     *
     * 0 <= M < 2^32
     *
     * 0 <= N < 32
     *
     * there is no enable or reset as the usage of this trigger can be
     * configured in the channels. Each clock cycle is 5 ns.
     */
    int auto_trigger_period;

    /** \brief component to create a trigger either periodically or randomly.
     *
     * To be exact, there are two parameters M = @link auto_trigger_period
     * auto_trigger_period @endlink and N = @link auto_trigger_random_exponent
     * auto_trigger_random_exponent @endlink that result in a distance between
     * triggers of
     *
     * T = 1 + M + [1...2^N]
     *
     * clock cycles.
     *
     * 0 <= M < 2^32
     *
     * 0 <= N < 32
     *
     * there is no enable or reset as the usage of this trigger can be
     * configured in the channels.
     */
    int auto_trigger_random_exponent;

    // RAW or SIGNED16
    int output_mode;

    /*! \brief Extended bandwidth
     *
     * Set ADC to the extended bandwidth
     */
    crono_bool_t extended_bandwidth;

    /*!
     * default: false. Do not change.
     */
    crono_bool_t ramp_test_mode;
} ndigo6g12_configuration;

/*! \ingroup statfuncts
 *   \brief Returns the driver version, same format as
 * ndigo6g12_static_info::driver_revision
 */
NDIGO6G12_API int ndigo6g12_get_driver_revision();

/*! \ingroup statfuncts
 *   \brief Returns the driver version including SVN build revision as a string
 * with format x.y.z.svn
 */
NDIGO6G12_API const char *ndigo6g12_get_driver_revision_str();

/*! Get the number of Ndigo6G12 cards
 */
NDIGO6G12_API int ndigo6g12_count_devices(int *error_code,
                                          const char **error_message);

/*! \ingroup conffuncts
 *   \brief Copies the default configuration to the specified config pointer
 *
<dl class="params">
  <dt>Default Values</dt>
  <dd>
    <table class="params">
      <tr><td class="paramname">adc_mode</td><td>NDIGO6G12_ADC_MODE_A for AppType::AVERAGING and AppType::SINGLE_CHANNEL</td></tr>
      <tr><td class="paramname"></td><td>NDIGO6G12_ADC_MODE_AD for AppType::DUAL_CHANNEL</td></tr>
      <tr><td class="paramname"></td><td>NDIGO6G12_ADC_MODE_ABCD for AppType::QUAD_CHANNEL or others</td></tr>
      <tr><td class="paramname">adc_cal_set</td><td>3 // Calibration data from Flash</td></tr>
      <tr><td class="paramname">analog_offsets[i]</td><td>0 // All channels</td></tr>
      <tr><td class="paramname">tdc_trigger_offsets[0-3]</td><td>0 // ADC channels</td></tr>
      <tr><td class="paramname">tdc_trigger_offsets[4]</td><td>AUX2_CLK_THRESHOLD // If clk_use_aux2</td></tr>
      <tr><td class="paramname">trigger[i].edge</td><td>true // All triggers</td></tr>
      <tr><td class="paramname">trigger[i].rising</td><td>false // All triggers</td></tr>
      <tr><td class="paramname">trigger[i].threshold</td><td>512 // All triggers</td></tr>
      <tr><td class="paramname">trigger[i].enable_rand</td><td>true // All triggers</td></tr>
      <tr><td class="paramname">trigger_block[i].enabled</td><td>false // All ADC Channels</td></tr>
      <tr><td class="paramname">trigger_block[i].retrigger</td><td>false // All ADC Channels</td></tr>
      <tr><td class="paramname">trigger_block[i].multi_shot_count</td><td>1 // All ADC Channels</td></tr>
      <tr><td class="paramname">trigger_block[i].precursor</td><td>0 // All ADC Channels</td></tr>
      <tr><td class="paramname">trigger_block[i].length</td><td>16 // All ADC Channels</td></tr>
      <tr><td class="paramname">trigger_block[i].sources</td><td>0 // All ADC Channels</td></tr>
      <tr><td class="paramname">trigger_block[i].gates</td><td>0 // All ADC Channels</td></tr>
      <tr><td class="paramname">trigger_block[i].minimum_free_packets</td><td>0 // All ADC Channels</td></tr>
      <tr><td class="paramname">gating_block[i].negate</td><td>false // All Gates</td></tr>
      <tr><td class="paramname">gating_block[i].retrigger</td><td>false // All Gates</td></tr>
      <tr><td class="paramname">gating_block[i].start</td><td>0 // All Gates</td></tr>
      <tr><td class="paramname">gating_block[i].stop</td><td>1000 // All Gates</td></tr>
      <tr><td class="paramname">gating_block[i].sources</td><td>0x00000000 // All Gates</td></tr>
      <tr><td class="paramname">auto_trigger_period</td><td>200000</td></tr>
      <tr><td class="paramname">auto_trigger_random_exponent</td><td>0</td></tr>
      <tr><td class="paramname">output_mode</td><td>NDIGO6G12_OUTPUT_MODE_SIGNED32 for AppType::AVERAGING, NDIGO6G12_OUTPUT_MODE_SIGNED16 for others</td></tr>
      <tr><td class="paramname">extended_bandwidth</td><td>false</td></tr>
      <tr><td class="paramname">ramp_test_mode</td><td>false</td></tr>
      <tr><td class="paramname">average_configuration.iterations</td><td>0</td></tr>
      <tr><td class="paramname">average_configuration.timeout_threshold</td><td>0</td></tr>
      <tr><td class="paramname">average_configuration.stop_manual</td><td>false</td></tr>
      <tr><td class="paramname">average_configuration.stop_on_overflow</td><td>false</td></tr>
      <tr><td class="paramname">average_configuration.stop_on_timeout</td><td>false</td></tr>
      <tr><td class="paramname">average_configuration.use_saturation</td><td>true</td></tr>
    </table>
  </dd>
</dl>
*/
NDIGO6G12_API int
ndigo6g12_get_default_configuration(ndigo6g12_device *device,
                                    ndigo6g12_configuration *config);

/*! \brief Sets up the standard parameters
 *
 *   Gets a set of default parameters for @link ndigo6g12_init ndigo6g12_init()
 * @endlink . This must always be used to initialize the @link initparamsstruct
 * ndigo6g12_init_parameter() @endlink structure. Return values are listed @link
 * defdefinpar here @endlink. \param init is type *ndigo6g12_init_parameters
 * 
 <dl class="params">
  <dt>Default Values</dt>
  <dd>
    <table class="params">
      <tr><td class="paramname">card_index</td><td>0</td></tr>
      <tr><td class="paramname">board_id</td><td>0</td></tr>
      <tr><td class="paramname">buffer_size[0]</td><td>64MB</td></tr>
      <tr><td class="paramname">buffer_size[1-7]</td><td>0 (unused)</td></tr>
      <tr><td class="paramname">dma_read_delay</td><td>8192</td></tr>
      <tr><td class="paramname">perf_derating</td><td>0</td></tr>
      <tr><td class="paramname">led_flashing_mode</td><td>1</td></tr>
      <tr><td class="paramname">adc_channel_mask</td><td>0x0f // all 4 ADC channels enabled by default</td></tr>
      <tr><td class="paramname">no_reference_clock</td><td>false</td></tr>
      <tr><td class="paramname">use_external_clock</td><td>false</td></tr>
      <tr><td class="paramname">use_aux2_clock</td><td>false</td></tr>
      <tr><td class="paramname">ignore_lane_errors</td><td>false</td></tr>
      <tr><td class="paramname">ignore_clock_errors</td><td>false</td></tr>
      <tr><td class="paramname">adc_full_swing</td><td>false</td></tr>
      <tr><td class="paramname">application_type</td><td>0 // use currently installed type</td></tr>
      <tr><td class="paramname">force_bitstream_update</td><td>false</td></tr>
      <tr><td class="paramname">partial_bitstream_size</td><td>0</td></tr>
      <tr><td class="paramname">partial_bitstream</td><td>nullptr</td></tr>
    </table>
  </dd>
</dl>
*/
NDIGO6G12_API int
ndigo6g12_get_default_init_parameters(ndigo6g12_init_parameters *init);

/*! \ingroup conffuncts
 *   \brief Configures Ndigo6G12 device.
 *
 *   The config information is copied such that it can be changed after the call
 * to
 *   @link ndigoconf ndigo6g12_configure()@endlink.
 */
NDIGO6G12_API int ndigo6g12_configure(ndigo6g12_device *device,
                                      ndigo6g12_configuration *config);

/*! \ingroup initfuncts
 *   \brief Open and initialize the ndigo6G12 board with the given index.
 *
 *   With error_code and error_message the user must provide pointers where
 * error information should be written by the driver. The buffer for the error
 * message must contain at least 80 chars. \param *device is a pointer to a struct
 * that receives the internal device reference \param *params is type @link
 * initparamsstruct ndigo6g12_init_parameters @endlink \param *error_code is
 * type int \param **error_message is type char. The buffer for the error
 * message has to contain at least 80 chars.
 */
NDIGO6G12_API int ndigo6g12_init(ndigo6g12_device *device,
                                 ndigo6g12_init_parameters *params,
                                 const char **error_message);

/*! \ingroup readout
 *   \brief Reads packets from the board
 *
 *   optionally automatically acknowledges the last read packets. Return values
 * are listed @link defread here @endlink. \param *device is type
 * ndigo6g12_device \param *in is type ndigo6g12_read_in \param *out is type
 * ndigo6g12_read_out
 */
NDIGO6G12_API int ndigo6g12_read(ndigo6g12_device *device,
                                 ndigo6g12_read_in *in,
                                 ndigo6g12_read_out *out);

/*! \ingroup initfuncts
 *   \brief finalize the driver for this device
 *
 *   Return values are listed @link defclose here @endlink.
 *   \param *device is type @link ndigo6g12_device ndigo6g12_device @endlink
 */
NDIGO6G12_API int ndigo6g12_close(ndigo6g12_device *device);

/*! \ingroup errorfuncts
 *   \brief gets latest error message of the current device
 *
 *   Return values are listed @link defclose here @endlink.
 *   \param *device is type @link ndigo6g12_device Ndigo6G12 device @endlink
 */
NDIGO6G12_API const char *
ndigo6g12_get_last_error_message(ndigo6g12_device *device);

/*! \ingroup runtime
 *   \brief start data acquisition
 *
 *   Return values are listed @link defstartcap here @endlink.
 *   \param *device is type @link ndigo6g12_device ndigo6g12_device @endlink
 */
NDIGO6G12_API int ndigo6g12_start_capture(ndigo6g12_device *device);

/*! \ingroup runtime
 *   \brief stop data acquisition
 *
 *   Return values are listed @link defstopcap here @endlink.
 *   \param *device is type @link ndigo6g12_device ndigo6g12_device @endlink
 */
NDIGO6G12_API int ndigo6g12_stop_capture(ndigo6g12_device *device);

/*! \ingroup runtime
 *   \brief Enables manual triggering
 */
NDIGO6G12_API int ndigo6g12_manual_trigger(ndigo6g12_device *device,
                                           int channel_mask);

/*! \ingroup runtime
 *   \brief Enables single shot recording
 */
NDIGO6G12_API int ndigo6g12_single_shot(ndigo6g12_device *device,
                                        int channel_mask);

/*! \ingroup statfuncts
 *   \brief Get static info
 */
NDIGO6G12_API int ndigo6g12_get_static_info(ndigo6g12_device *device,
                                            ndigo6g12_static_info *static_info);

/*! \ingroup statfuncts
 *   \brief Get static info
 */
NDIGO6G12_API int ndigo6g12_get_param_info(ndigo6g12_device *device,
                                           ndigo6g12_param_info *param_info);

/*! \ingroup statfuncts
 *   \brief Get fast info
 */
NDIGO6G12_API int ndigo6g12_get_fast_info(ndigo6g12_device *device,
                                          ndigo6g12_fast_info *fast_info);

/*! \ingroup runtime
 *   \brief write partial bitstream to Ndigo6G12
 */
NDIGO6G12_API int ndigo6g12_write_partial_bitstream(ndigo6g12_device *device,
                                                    uint32_t *buffer,
                                                    uint32_t buffer_size);

/*! \ingroup runtime
 *   \brief fully reset the MCAP interface
 */
NDIGO6G12_API int ndigo6g12_mcap_fullreset(ndigo6g12_device *device);

/*! Returns the state, corresponding to state code 'state', in string format.
 *
 *   @param[in] state
 */
NDIGO6G12_API const char *ndigo6g12_device_state_to_str(int state);

#ifdef __cplusplus
}
#endif

#endif
