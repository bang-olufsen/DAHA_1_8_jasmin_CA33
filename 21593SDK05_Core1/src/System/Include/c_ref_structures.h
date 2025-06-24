/******************************************************************************
 * This program is protected under international and U.S. copyright laws as
 * an unpublished work. This program is confidential and proprietary to the
 * copyright owners. Reproduction or disclosure, in whole or in part, or the
 * production of derivative works therefrom without the express permission of
 * the copyright owners is prohibited.
 *
 *                Copyright (C) 2013-2019 by Dolby Laboratories
 *                            All rights reserved.
 ******************************************************************************/
 



#include "ar_speaker.h"
//#include "dtt_xml_parser.h"
#define DLB_GETPARAM_MAXLEN    256     /**< commandline length in text file*/
#define DAP_AUDIO_OPTIMIZER_NB_BANDS_MAX (20u)
#define DAP_MAX_NUM_OUTPUT_CHANNELS      (32)
#define DAP_GRAPHIC_EQUALIZER_BANDS_MAX  (20u)
#define DAP_IEQ_MAX_BANDS_NUM            (20u)
/**
 * @brief Maximum number of Audio Optimizer bands.
 */
#define DATMOS_HT_AUDIO_OPTIMIZER_NB_BANDS_MAX (20u)

/**
 * @brief Maximum number of Graphic Equalizer bands.
 */
#define DATMOS_HT_GRAPHIC_EQUALIZER_BANDS_MAX  (20u)

/**
 * @brief Maximum number of Intelligent Equalizer bands.
 */
#define DATMOS_HT_IEQ_MAX_BANDS_NUM            (20u)
typedef struct dlb_bufer_s
{
    /** Channel count */
    unsigned    nchannel;

    /** Distance, in units of the chosen data type, between consecutive samples
     *  of the same channel. For DLB_BUFFER_OCTET_PACKED, this is in units of
     *  unsigned char. For interleaved audio data, set this equal to nchannel.
     *  For separate channel buffers, set this to 1.
     */
    int   nstride;

    /** One of the DLB_BUFFER_* codes */
    int         data_type;

    /** Array of pointers to data, one for each channel. */
    void      **ppdata;
} dlb_bufer;


typedef struct {
    int rate;         /**< sample rate */
    int channels;     /**< number of channels */
    int bpf;          /**< bytes per frame (one sample size multiplied by number
                           of channels */
    int bps;          /**< bytes per sample */
    int interleaved;  /**< is output interleaved or not */
} datmos_ht_audio_info;

/**
 * @brief The total configuration of the room.
 *
 * Currently contains only the speaker layout, but may be extended in the future.
 */
typedef struct datmos_room_config_s
{
    datmos_ht_speaker_presence speaker_presence[DATMOS_SPEAKER_ID__LAST_];  /**< Speaker presence indexed by @ref datmos_speaker_id. */
} datmos_room_config;
#ifndef HOME_AUDIO_DAP
/**
 * @enum datmos_ht_audio_stream_type
 * @brief Enumeration of supported media types
 *
 * @var DATMOS_VIRTUALIZER_MODE_DISABLE
 * @brief Disable virtualizer.
 *
 * @var DATMOS_VIRTUALIZER_MODE_SPEAKER
 * @brief Enable speaker virtualizer.
 *
 * @var DATMOS_VIRTUALIZER_MODE_HEADPHONE
 * @brief Enable headphone virtualizer.
 *
 * If this option is enabled the selected speaker layout can only consist of
 * left and right speakers
 */
typedef enum {
  DATMOS_VIRTUALIZER_MODE_DISABLE,
  DATMOS_VIRTUALIZER_MODE_SPEAKER,
  DATMOS_VIRTUALIZER_MODE_HEADPHONE,
  DATMOS_VIRTUALIZER_MODE_DEFAULT = DATMOS_VIRTUALIZER_MODE_DISABLE,
} datmos_ht_virtualizer_mode;
/**
 * @enum datmos_ht_audio_processing_profile
 * @brief Enumeration audio processing profiles.
 *
 * @var DATMOS_PROFILE_OFF
 * @brief Processing disabled.
 *
 * @var DATMOS_PROFILE_MOVIE
 * @brief Processing optimized for movie content.
 *
 * @var DATMOS_PROFILE_MUSIC
 * @brief Processing optimized for music content.
 *
 * @var DATMOS_PROFILE_NIGHT
 * @brief Processing optimized for low dynamic range playback.
 *
 * @var DATMOS_PROFILE_DYNAMIC
 * @brief Processing optimized for dynamic content.
 *
 * @var DATMOS_PROFILE_GAME
 * @brief Processing optimized for game content.
 *
 * @var DATMOS_PROFILE_VOICE
 * @brief Processing optimized for voice content.
 *
 * @var DATMOS_PROFILE_PERSONALIZE
 * @brief Personal processing PROFILE.
 *
 * @var DATMOS_PROFILE_CUSTOM_A
 * @brief Custom profile A.
 *
 * @var DATMOS_PROFILE_CUSTOM_B
 * @brief Custom profile B.
 *
 * @var DATMOS_PROFILE_CUSTOM_C
 * @brief Custom profile C.
 *
 * @var DATMOS_PROFILE_CUSTOM_D
 * @brief Custom profile D.
 *
 * @var DATMOS_PROFILE_DEFAULT
 * @brief Default processing profile.
 */
typedef enum
{
    DATMOS_PROFILE_OFF,
    DATMOS_PROFILE_MOVIE,
    DATMOS_PROFILE_MUSIC,
    DATMOS_PROFILE_NIGHT,
    DATMOS_PROFILE_DYNAMIC,
    DATMOS_PROFILE_GAME,
    DATMOS_PROFILE_VOICE,
    DATMOS_PROFILE_PERSONALIZE,
    DATMOS_PROFILE_CUSTOM_A,
    DATMOS_PROFILE_CUSTOM_B,
    DATMOS_PROFILE_CUSTOM_C,
    DATMOS_PROFILE_CUSTOM_D,
    DATMOS_PROFILE_DEFAULT = DATMOS_PROFILE_OFF
} datmos_ht_profile_id;

/**
 * @enum datmos_ht_drc_mode
 * @brief Enumeration dynamic range control modes
 *
 * @var DATMOS_DRC_MODE_DISABLE
 * @brief Disable Dynamic range control in Dolby Digital Plus, Dolby TrueHD, and Dolby MAT
 *        decoders
 *
 * @var DATMOS_DRC_MODE_ENABLE
 * @brief Enable Dynamic range control in Dolby Digital Plus, Dolby TrueHD, and Dolby MAT decoders
 *
 * @var DATMOS_DRC_MODE_AUTO
 * @brief If available in decoder, activate automatic Dynamic range control setting, else enable
 *        Dynamic range control.
 * @var DATMOS_DRC_MODE_DEFAULT
 * @brief Default Dynamic range control setting.
 */
typedef enum
{
    DATMOS_DRC_MODE_DISABLE,
    DATMOS_DRC_MODE_ENABLE,
    DATMOS_DRC_MODE_AUTO,
    DATMOS_DRC_MODE_DEFAULT = DATMOS_DRC_MODE_ENABLE
} datmos_ht_drc_mode;

/**
 * @brief Postprocessing profile.
 *
 * Set of dynamic parameters used for audio postprocessing.
 */
#endif
/**
 * @brief Options for controlling the applications.
 */
typedef struct datmos_options_s
{
    char                 in_filename[DLB_GETPARAM_MAXLEN];     /**< Filename of input audio stream.                              */
    char                 out_filename[DLB_GETPARAM_MAXLEN];    /**< Filename of output audio stream.                             */
    char                 xml_config_file[DLB_GETPARAM_MAXLEN]; /**< Filename of XML tuning file                                  */
    char                 endpoint[DLB_GETPARAM_MAXLEN];   /**< Endpoint name to use for loading configuration               */
    int                  virt_cfg_enable;                 /**< If set, loads configuration with enabled virtualization                */
    int                  b_rf64;                     /**< If set, ouptut file will be opened as RF64 BWF, to allow for >4GB data */
    int                  output_bit_depth;           /**< Requested output integer bit depth. If 0, output follows input format. */
    int                  b_tuning_mode_enable;       /**< If set, enables tuning mode.                                           */

    datmos_room_config   room_config;                /**< Room configuration.                                                    */
    int                  b_direct_decode;            /**< If set, decode the largest channel-based presentation supported by the room.  */
    int                  b_direct_decode_config;     /**< If set, room config consists of 5.1 or fewer speakers                  */
    int                  b_enable_upmixer;           /**< If set, channel-based content is upmixed.                              */
    int                  b_enable_loudness_mgmt;     /**< If set, enable loudness management in the Dolby TrueHD decoder.        */
    int                  b_verbose;                  /**< If set, enable verbose reporting by the application.                   */
    int                  b_height_filter;            /**< If set, enable height filter in DAP                                    */
    int                  b_center_spread;            /**< If set, enable center spreading in DAP                                 */
    int                  b_vlamp;                    /**< If set, Volume Leveler output target level will be set to -31.0 dBFS   */

    datmos_ht_virtualizer_mode virt_mode;            /**< Virtualization mode                                                    */
    datmos_ht_profile_id audio_profile;				 /**< Dolby Audio Processing profile                                         */
    datmos_ht_drc_mode   drc_mode;                   /**< Dynamic Range Control setting for decoders.                            */
    double               drc_cut;                    /**< Requested DRC cut amount, on [0.0, 1.0].                               */
    double               drc_boost;                  /**< Requested DRC boost amount, on [0.0, 1.0].                             */

    unsigned int         front_angle;                /**< Configures front speakers angle for virtualization                     */
    unsigned int         height_angle;               /**< Configures height speakers angle for virtualization                    */
    unsigned int         surr_angle;                 /**< Configures surround speakers angle for virtualization                  */
    unsigned int         rear_surr_angle;            /**< Configures rear surround speakers angle for virtualization             */

#ifndef NDEBUG
    unsigned int         dbg_out_mask;               /**< Bitmask enabling debug wave output files                               */
#endif
} datmos_options;

