/******************************************************************************
 * This program is protected under international and U.S. copyright laws as
 * an unpublished work. This program is confidential and proprietary to the
 * copyright owners. Reproduction or disclosure, in whole or in part, or the
 * production of derivative works therefrom without the express permission of
 * the copyright owners is prohibited.
 *
 *                  Copyright (C) 2013 by Dolby Laboratories.
 *                            All rights reserved.
 ******************************************************************************/

/**
 * @file
 * @brief This header defines how speakers are specified for the Audio Renderer
 * projects.
 *
 * Speaker masks indicate which speakers are present. Such masks are built up
 * from the pairs of speakers (or single speakers where allowed) in the @ref
 * speaker_masks "speaker mask definitions".
 */

#ifndef AR_SPEAKER_H
#define AR_SPEAKER_H

/**
 * @name Speaker pair index definitions
 * These specify the index of each allowed set of speakers in the bitmask.
 * @{
 */
#define AR_SPEAKER_L_R_INDEX       (0)  /**< L/R       (2 speakers) */
#define AR_SPEAKER_C_INDEX         (1)  /**< C         (1 speaker)  */
#define AR_SPEAKER_LFE_INDEX       (2)  /**< LFE       (1 speaker)  */
#define AR_SPEAKER_LS_RS_INDEX     (3)  /**< Ls/Rs     (2 speakers) */
#define AR_SPEAKER_LRS_RRS_INDEX   (4)  /**< Lrs/Rrs   (2 speakers) */

#define AR_SPEAKER_CS_INDEX        (5)  /**< Cs        (1 speaker)  */
#define AR_SPEAKER_LC_RC_INDEX     (6)  /**< Lc/Rc     (2 speakers) */
#define AR_SPEAKER_LW_RW_INDEX     (7)  /**< Lw/Rw     (2 speakers) */

#define AR_SPEAKER_LFH_RFH_INDEX   (8)  /**< Lfh/Rfh   (2 speakers) */
#define AR_SPEAKER_LTF_RTF_INDEX   (9)  /**< Ltf/Rtf   (2 speakers) */
#define AR_SPEAKER_LTM_RTM_INDEX   (10) /**< Ltm/Rtm   (2 speakers) */
#define AR_SPEAKER_LTR_RTR_INDEX   (11) /**< Ltr/Rtr   (2 speakers) */
#define AR_SPEAKER_LRH_RRH_INDEX   (12) /**< Lrh/Rrh   (2 speakers) */

#define AR_SPEAKER_LSC_RSC_INDEX   (13) /**< Lsc/Rsc   (2 speakers) */
#define AR_SPEAKER_LS1_RS1_INDEX   (14) /**< Ls1/Rs2   (2 speakers) */
#define AR_SPEAKER_LS2_RS2_INDEX   (15) /**< Ls2/Rs2   (2 speakers) */
#define AR_SPEAKER_LRS1_RRS1_INDEX (16) /**< Lrs1/Rrs1 (2 speakers) */
#define AR_SPEAKER_LRS2_RRS2_INDEX (17) /**< Lrs2/Rrs2 (2 speakers) */
#define AR_SPEAKER_LCS_RCS_INDEX   (18) /**< Lcs/Rcs   (2 speakers) */
#define AR_SPEAKER_SH_INDEX        (19) /**< Sh        (1 speaker)  */
/** @} */

/** @brief Limit of speaker mask indices */
#define AR_SPEAKER_MASK_MAX_INDEX (AR_SPEAKER_SH_INDEX)

/** @brief Creates a speaker mask for the given speaker (pair) index */
#define AR_SPEAKER_MASK(X)             ((unsigned long)1 << AR_SPEAKER_##X##_INDEX)

/**
 * @anchor speaker_masks
 * @name Speaker mask definitions
 * These are the bitmasks for each pair of speakers (or single speaker).
 * Bitmasks for more complex speaker configurations can be built up from these
 * masks. Not all possible speaker masks will be valid: see the relevant
 * specification to determine if a particular speaker configuration is valid.
 * @{
 */
#define AR_SPEAKER_L_R_MASK       AR_SPEAKER_MASK(L_R)       /**< L/R       (2 speakers) */
#define AR_SPEAKER_C_MASK         AR_SPEAKER_MASK(C)         /**< C         (1 speaker)  */
#define AR_SPEAKER_LFE_MASK       AR_SPEAKER_MASK(LFE)       /**< LFE       (1 speaker)  */
#define AR_SPEAKER_LS_RS_MASK     AR_SPEAKER_MASK(LS_RS)     /**< Ls/Rs     (2 speakers) */
#define AR_SPEAKER_LRS_RRS_MASK   AR_SPEAKER_MASK(LRS_RRS)   /**< Lrs/Rrs   (2 speakers) */

#define AR_SPEAKER_CS_MASK        AR_SPEAKER_MASK(CS)        /**< Cs        (1 speaker)  */
#define AR_SPEAKER_LC_RC_MASK     AR_SPEAKER_MASK(LC_RC)     /**< Lc/Rc     (2 speakers) */
#define AR_SPEAKER_LW_RW_MASK     AR_SPEAKER_MASK(LW_RW)     /**< Lw/Rw     (2 speakers) */

#define AR_SPEAKER_LFH_RFH_MASK   AR_SPEAKER_MASK(LFH_RFH)   /**< Lfh/Rfh   (2 speakers) */
#define AR_SPEAKER_LTF_RTF_MASK   AR_SPEAKER_MASK(LTF_RTF)   /**< Ltf/Rtf   (2 speakers) */
#define AR_SPEAKER_LTM_RTM_MASK   AR_SPEAKER_MASK(LTM_RTM)   /**< Ltm/Rtm   (2 speakers) */
#define AR_SPEAKER_LTR_RTR_MASK   AR_SPEAKER_MASK(LTR_RTR)   /**< Ltr/Rtr   (2 speakers) */
#define AR_SPEAKER_LRH_RRH_MASK   AR_SPEAKER_MASK(LRH_RRH)   /**< Lrh/Rrh   (2 speakers) */

#define AR_SPEAKER_LSC_RSC_MASK   AR_SPEAKER_MASK(LSC_RSC)   /**< Lsc/Rsc   (2 speakers) */
#define AR_SPEAKER_LS1_RS1_MASK   AR_SPEAKER_MASK(LS1_RS1)   /**< Ls1/Rs2   (2 speakers) */
#define AR_SPEAKER_LS2_RS2_MASK   AR_SPEAKER_MASK(LS2_RS2)   /**< Ls2/Rs2   (2 speakers) */
#define AR_SPEAKER_LRS1_RRS1_MASK AR_SPEAKER_MASK(LRS1_RRS1) /**< Lrs1/Rrs1 (2 speakers) */
#define AR_SPEAKER_LRS2_RRS2_MASK AR_SPEAKER_MASK(LRS2_RRS2) /**< Lrs2/Rrs2 (2 speakers) */
#define AR_SPEAKER_LCS_RCS_MASK   AR_SPEAKER_MASK(LCS_RCS)   /**< Lcs/Rcs   (2 speakers) */
#define AR_SPEAKER_SH_MASK        AR_SPEAKER_MASK(SH)        /**< SH        (1 speaker)  */

#define AR_SPEAKER_70_MASK  ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LS_RS_MASK | AR_SPEAKER_LRS_RRS_MASK )

#define AR_SPEAKER_71_MASK  ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LFE_MASK | AR_SPEAKER_LS_RS_MASK \
                            | AR_SPEAKER_LRS_RRS_MASK )

#define AR_SPEAKER_712_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LFE_MASK | AR_SPEAKER_LS_RS_MASK \
                            | AR_SPEAKER_LRS_RRS_MASK | AR_SPEAKER_LTM_RTM_MASK )

#define AR_SPEAKER_702_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LS_RS_MASK | AR_SPEAKER_LRS_RRS_MASK \
                            | AR_SPEAKER_LTM_RTM_MASK )

#define AR_SPEAKER_714_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LFE_MASK | AR_SPEAKER_LS_RS_MASK \
                            | AR_SPEAKER_LRS_RRS_MASK | AR_SPEAKER_LTF_RTF_MASK \
                            | AR_SPEAKER_LTR_RTR_MASK )

#define AR_SPEAKER_704_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LS_RS_MASK | AR_SPEAKER_LRS_RRS_MASK \
                            | AR_SPEAKER_LTF_RTF_MASK | AR_SPEAKER_LTR_RTR_MASK )

#define AR_SPEAKER_60_MASK  ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LS_RS_MASK \
                            | AR_SPEAKER_LRS_RRS_MASK )

#define AR_SPEAKER_61_MASK  ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LFE_MASK \
                            | AR_SPEAKER_LS_RS_MASK | AR_SPEAKER_LRS_RRS_MASK )

#define AR_SPEAKER_612_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LFE_MASK \
                            | AR_SPEAKER_LS_RS_MASK | AR_SPEAKER_LRS_RRS_MASK \
                            | AR_SPEAKER_LTM_RTM_MASK )

#define AR_SPEAKER_602_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LS_RS_MASK \
                            | AR_SPEAKER_LRS_RRS_MASK | AR_SPEAKER_LTM_RTM_MASK )

#define AR_SPEAKER_614_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LFE_MASK \
                            | AR_SPEAKER_LS_RS_MASK | AR_SPEAKER_LRS_RRS_MASK \
                            | AR_SPEAKER_LTF_RTF_MASK | AR_SPEAKER_LTR_RTR_MASK )

#define AR_SPEAKER_604_MASK ( AR_SPEAKER_L_R_MASK \
                            | AR_SPEAKER_LS_RS_MASK | AR_SPEAKER_LRS_RRS_MASK \
                            | AR_SPEAKER_LTF_RTF_MASK | AR_SPEAKER_LTR_RTR_MASK )

#define AR_SPEAKER_50_MASK  ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LS_RS_MASK )

#define AR_SPEAKER_51_MASK  ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LFE_MASK | AR_SPEAKER_LS_RS_MASK )

#define AR_SPEAKER_512_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LFE_MASK | AR_SPEAKER_LS_RS_MASK \
                            | AR_SPEAKER_LTM_RTM_MASK )

#define AR_SPEAKER_502_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LS_RS_MASK | AR_SPEAKER_LTM_RTM_MASK )

#define AR_SPEAKER_514_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LFE_MASK | AR_SPEAKER_LS_RS_MASK \
                            | AR_SPEAKER_LTF_RTF_MASK | AR_SPEAKER_LTR_RTR_MASK )

#define AR_SPEAKER_504_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LS_RS_MASK | AR_SPEAKER_LTF_RTF_MASK \
                            | AR_SPEAKER_LTR_RTR_MASK )

#define AR_SPEAKER_40_MASK  ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LS_RS_MASK)

#define AR_SPEAKER_41_MASK  ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LFE_MASK \
                            | AR_SPEAKER_LS_RS_MASK )

#define AR_SPEAKER_412_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LFE_MASK \
                            | AR_SPEAKER_LS_RS_MASK | AR_SPEAKER_LTM_RTM_MASK )

#define AR_SPEAKER_402_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LS_RS_MASK \
                            | AR_SPEAKER_LTM_RTM_MASK )

#define AR_SPEAKER_414_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LFE_MASK \
                            | AR_SPEAKER_LS_RS_MASK | AR_SPEAKER_LTF_RTF_MASK \
                            | AR_SPEAKER_LTR_RTR_MASK )

#define AR_SPEAKER_404_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LS_RS_MASK \
                            | AR_SPEAKER_LTF_RTF_MASK | AR_SPEAKER_LTR_RTR_MASK )

#define AR_SPEAKER_30_MASK  ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK )

#define AR_SPEAKER_31_MASK  ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LFE_MASK )

#define AR_SPEAKER_312_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LFE_MASK | AR_SPEAKER_LTM_RTM_MASK )

#define AR_SPEAKER_302_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LTM_RTM_MASK )

#define AR_SPEAKER_20_MASK  ( AR_SPEAKER_L_R_MASK )

#define AR_SPEAKER_21_MASK  ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LFE_MASK )

#define AR_SPEAKER_30_MASK  ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK )

#define AR_SPEAKER_31_MASK  ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK | AR_SPEAKER_LFE_MASK )

#define AR_SPEAKER_212_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LFE_MASK \
                            | AR_SPEAKER_LTM_RTM_MASK )

#define AR_SPEAKER_202_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LTM_RTM_MASK )

#define AR_SPEAKER_211_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LFE_MASK \
                            | AR_SPEAKER_SH_MASK )

#define AR_SPEAKER_201_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_SH_MASK )

#define AR_SPEAKER_311_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LFE_MASK | AR_SPEAKER_SH_MASK )

#define AR_SPEAKER_301_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_SH_MASK )

#define AR_SPEAKER_411_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LFE_MASK \
                            | AR_SPEAKER_LS_RS_MASK | AR_SPEAKER_SH_MASK )

#define AR_SPEAKER_401_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_LS_RS_MASK \
                            | AR_SPEAKER_SH_MASK )

#define AR_SPEAKER_511_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LFE_MASK | AR_SPEAKER_LS_RS_MASK \
                            | AR_SPEAKER_SH_MASK )

#define AR_SPEAKER_501_MASK ( AR_SPEAKER_L_R_MASK | AR_SPEAKER_C_MASK \
                            | AR_SPEAKER_LS_RS_MASK | AR_SPEAKER_SH_MASK )

/** @} */

/**
 * @anchor speaker_definitions
 * @name Speaker Defintions
 * This is used internally by some nodes. Users should use only the @ref
 * speaker_masks "speaker mask definitions" to flag the existance of speakers.
 * @{
 */
#define AR_SPEAKER_L    0
#define AR_SPEAKER_R    1
#define AR_SPEAKER_C    2
#define AR_SPEAKER_LFE  3
#define AR_SPEAKER_LS   4
#define AR_SPEAKER_RS   5
#define AR_SPEAKER_LRS  6
#define AR_SPEAKER_RRS  7

#define AR_SPEAKER_CS   8
#define AR_SPEAKER_LC   9
#define AR_SPEAKER_RC   10
#define AR_SPEAKER_LW   11
#define AR_SPEAKER_RW   12

#define AR_SPEAKER_LFH  13
#define AR_SPEAKER_RFH  14
#define AR_SPEAKER_LTF  15
#define AR_SPEAKER_RTF  16
#define AR_SPEAKER_LTM  17
#define AR_SPEAKER_RTM  18
#define AR_SPEAKER_LTR  19
#define AR_SPEAKER_RTR  20
#define AR_SPEAKER_LRH  21
#define AR_SPEAKER_RRH  22

#define AR_SPEAKER_LSC  23
#define AR_SPEAKER_RSC  24
#define AR_SPEAKER_LS1  25
#define AR_SPEAKER_RS1  26
#define AR_SPEAKER_LS2  27
#define AR_SPEAKER_RS2  28
#define AR_SPEAKER_LRS1 29
#define AR_SPEAKER_RRS1 30
#define AR_SPEAKER_LRS2 31
#define AR_SPEAKER_RRS2 32
#define AR_SPEAKER_LCS  33
#define AR_SPEAKER_RCS  34
#define AR_SPEAKER_SH   35
/** @} */

/** @brief Limit of speaker indices */
#define AR_SPEAKER_MAX_COUNT  36

/**
 * @brief Speaker data table generation macro.
 *
 * This macro is designed to expand to a table that encapsulates all data
 * related to a speaker pair. A single row contains a speaker pair name (mask),
 * actual left and right speakers in this pair and the name of the speaker pair
 * as would show up in command line options. The following fields are included
 * in the table:
 *
 * - Field 1: **Speaker mask**
 *
 *   This is the speaker mask of the speaker pair as defined in the @ref
 *   speaker_masks "speaker mask definitions".
 *
 * - Field 2: **Left speaker**
 *
 *   This is the left speaker of the pair. If the mask is actually for a single
 *   speaker (eg. C) it is listed here as the left speaker.
 *
 * - Field 3: **Right speaker**
 *
 *   This is the right speaker of the pair. If the mask is actually for a single
 *   speaker (eg. C) this field is set to -1.
 *
 * - Field 4: **Speaker name**
 *
 *   This is the label used by the reflect layer to identify the speaker pair in
 *   the command-line and other places.
 *
 * - Field 5: **User defined**
 *
 *   Can be used to pass any extra parameters to a user's definition of this
 *   macro.
 *
 * - Field 6: **Speaker dependencies**
 *
 *   Some speakers cannot be added unless certain other speakers are present.
 *   This dependency is specified by this field.
 *
 * @param ENTRY a function-like macro that accepts 6 arguments
 * @param PARAM any extra user-defined information needed by the @p ENTRY macro
 */
#define SPEAKERS_MASK_LIST(ENTRY, PARAM)\
    ENTRY(AR_SPEAKER_L_R_MASK      , AR_SPEAKER_L   , AR_SPEAKER_R   , "LR"      , PARAM, 0)\
    ENTRY(AR_SPEAKER_C_MASK        , AR_SPEAKER_C   ,            -1  , "C"       , PARAM, AR_SPEAKER_L_R_MASK)\
    ENTRY(AR_SPEAKER_LFE_MASK      , AR_SPEAKER_LFE ,            -1  , "LFE"     , PARAM, AR_SPEAKER_L_R_MASK)\
    ENTRY(AR_SPEAKER_LS_RS_MASK    , AR_SPEAKER_LS  , AR_SPEAKER_RS  , "LsRs"    , PARAM, AR_SPEAKER_L_R_MASK)\
    ENTRY(AR_SPEAKER_LRS_RRS_MASK  , AR_SPEAKER_LRS , AR_SPEAKER_RRS , "LrsRrs"  , PARAM, AR_SPEAKER_L_R_MASK + AR_SPEAKER_LS_RS_MASK)\
    ENTRY(AR_SPEAKER_CS_MASK       , AR_SPEAKER_CS  ,            -1  , "Cs"      , PARAM, AR_SPEAKER_L_R_MASK + AR_SPEAKER_LS_RS_MASK)\
    ENTRY(AR_SPEAKER_LC_RC_MASK    , AR_SPEAKER_LC  , AR_SPEAKER_RC  , "LcRc"    , PARAM, AR_SPEAKER_L_R_MASK + AR_SPEAKER_LS_RS_MASK)\
    ENTRY(AR_SPEAKER_LW_RW_MASK    , AR_SPEAKER_LW  , AR_SPEAKER_RW  , "LwRw"    , PARAM, AR_SPEAKER_L_R_MASK + AR_SPEAKER_LS_RS_MASK)\
    ENTRY(AR_SPEAKER_LFH_RFH_MASK  , AR_SPEAKER_LFH , AR_SPEAKER_RFH , "LfhRfh"  , PARAM, AR_SPEAKER_L_R_MASK)\
    ENTRY(AR_SPEAKER_LTF_RTF_MASK  , AR_SPEAKER_LTF , AR_SPEAKER_RTF , "LtfRtf"  , PARAM, AR_SPEAKER_L_R_MASK)\
    ENTRY(AR_SPEAKER_LTM_RTM_MASK  , AR_SPEAKER_LTM , AR_SPEAKER_RTM , "LtmRtm"  , PARAM, AR_SPEAKER_L_R_MASK)\
    ENTRY(AR_SPEAKER_LTR_RTR_MASK  , AR_SPEAKER_LTR , AR_SPEAKER_RTR , "LtrRtr"  , PARAM, AR_SPEAKER_L_R_MASK)\
    ENTRY(AR_SPEAKER_LRH_RRH_MASK  , AR_SPEAKER_LRH , AR_SPEAKER_RRH , "LrhRrh"  , PARAM, AR_SPEAKER_L_R_MASK)\
    ENTRY(AR_SPEAKER_LS1_RS1_MASK  , AR_SPEAKER_LS1 , AR_SPEAKER_RS1 , "Ls1Rs1"  , PARAM, AR_SPEAKER_L_R_MASK + AR_SPEAKER_LS_RS_MASK + AR_SPEAKER_LRS_RRS_MASK)\
    ENTRY(AR_SPEAKER_LS2_RS2_MASK  , AR_SPEAKER_LS2 , AR_SPEAKER_RS2 , "Ls2Rs2"  , PARAM, AR_SPEAKER_L_R_MASK + AR_SPEAKER_LS_RS_MASK + AR_SPEAKER_LRS_RRS_MASK)\
    ENTRY(AR_SPEAKER_LRS1_RRS1_MASK, AR_SPEAKER_LRS1, AR_SPEAKER_RRS1, "Lrs1Rrs1", PARAM, AR_SPEAKER_L_R_MASK + AR_SPEAKER_LS_RS_MASK + AR_SPEAKER_LRS_RRS_MASK)\
    ENTRY(AR_SPEAKER_LRS2_RRS2_MASK, AR_SPEAKER_LRS2, AR_SPEAKER_RRS2, "Lrs2Rrs2", PARAM, AR_SPEAKER_L_R_MASK + AR_SPEAKER_LS_RS_MASK + AR_SPEAKER_LRS_RRS_MASK)\
    ENTRY(AR_SPEAKER_LCS_RCS_MASK  , AR_SPEAKER_LCS , AR_SPEAKER_RCS , "LcsRcs"  , PARAM, AR_SPEAKER_L_R_MASK + AR_SPEAKER_LS_RS_MASK + AR_SPEAKER_LRS_RRS_MASK)\
    ENTRY(AR_SPEAKER_LSC_RSC_MASK  , AR_SPEAKER_LSC , AR_SPEAKER_RSC , "LscRsc"  , PARAM, AR_SPEAKER_L_R_MASK + AR_SPEAKER_LS_RS_MASK)\
    ENTRY(AR_SPEAKER_SH_MASK  , AR_SPEAKER_SH , -1 , "Sh"  , PARAM, AR_SPEAKER_L_R_MASK)

/**
 * @brief Tests whether the given speaker mask represents a single speaker (as
 * opposed to a pair of speakers).
 */
#define AR_SPEAKER_IS_SINGLE(MASK)    \
    (   (MASK == AR_SPEAKER_C_MASK)   \
    ||  (MASK == AR_SPEAKER_LFE_MASK) \
    ||  (MASK == AR_SPEAKER_CS_MASK)  \
    ||  (MASK == AR_SPEAKER_SH_MASK))

/** @brief Combined mask for all height speakers. */
#define AR_SPEAKER_HEIGHTS_MASK                 \
  ( AR_SPEAKER_LFH_RFH_MASK                     \
    | AR_SPEAKER_LTF_RTF_MASK                   \
    | AR_SPEAKER_LTM_RTM_MASK                   \
    | AR_SPEAKER_LTR_RTR_MASK                   \
    | AR_SPEAKER_LRH_RRH_MASK                   \
    | AR_SPEAKER_SH_MASK                        \
    )

#define AR_SPEAKER_EXTENDED_MASK                \
  ( AR_SPEAKER_CS_MASK                          \
    | AR_SPEAKER_LC_RC_MASK                     \
    | AR_SPEAKER_LSC_RSC_MASK                   \
    | AR_SPEAKER_LW_RW_MASK                     \
    | AR_SPEAKER_LS1_RS1_MASK                   \
    | AR_SPEAKER_LS2_RS2_MASK                   \
    | AR_SPEAKER_LRS1_RRS1_MASK                 \
    | AR_SPEAKER_LRS2_RRS2_MASK                 \
    | AR_SPEAKER_LCS_RCS_MASK                   \
    | AR_SPEAKER_LFH_RFH_MASK                   \
    | AR_SPEAKER_LRH_RRH_MASK                   \
    )


#define DPF_MAX_CHANNELS 		12
#define UDC_MAX_OBJECTS     	16
#define  UDC_MAX_I0_FCHANS  	5
#define UDC_OUTPUTMAP_LENGTH 	16   /* Number of bits in the UDC output map*/
#define CHAN_UNASSIGNED 		0xFF


typedef enum
{
	DPF_CHANNEL_LEFT,                /**< Microsoft Front Left                */
	DPF_CHANNEL_RIGHT,               /**< Microsoft Front Right               */
	DPF_CHANNEL_CENTER,              /**< Microsoft Front Center              */
	DPF_CHANNEL_LFE,                 /**< Microsoft Low Frequency             */
	DPF_CHANNEL_BACK_LEFT,           /**< Microsoft Back Left (Lrs)           */
	DPF_CHANNEL_BACK_RIGHT,          /**< Microsoft Back Right (Rrs)          */
	DPF_CHANNEL_CENTER_LEFT,         /**< Microsoft Front Left of Center' (Lc)*/
	DPF_CHANNEL_CENTER_RIGHT,        /**< Microsoft Front Right of Center (Rc)*/
	DPF_CHANNEL_BACK_CENTER,         /**< Microsoft Back Center (mono or Cs)  */
	DPF_CHANNEL_SIDE_LEFT,           /**< Microsoft Side Left (Ls)            */
	DPF_CHANNEL_SIDE_RIGHT,          /**< Microsoft Side Right (Rs)           */
	DPF_CHANNEL_LEFT_WIDE,           /**< Lw - outside front left             */
	DPF_CHANNEL_RIGHT_WIDE,          /**< Rw - outside front right            */
	DPF_CHANNEL_LEFT_SCREEN,         /**< Lsc - between C and Lc              */
	DPF_CHANNEL_RIGHT_SCREEN,        /**< Rsc - between C and Rc              */
	DPF_CHANNEL_LEFT_SUR_1,          /**< Ls1 - between Ls and Lw             */
	DPF_CHANNEL_RIGHT_SUR_1,         /**< Rs1 - between Rs and Rw             */
	DPF_CHANNEL_LEFT_SUR_2,          /**< Ls2 - between Ls and Lrs1           */
	DPF_CHANNEL_RIGHT_SUR_2,         /**< Rs2 - between Rs and Rrs1           */
	DPF_CHANNEL_LEFT_REAR_SUR_1,     /**< Lrs1 - between Lrs and Ls2          */
	DPF_CHANNEL_RIGHT_REAR_SUR_1,    /**< Rrs1 - between Rrs and Rs2          */
	DPF_CHANNEL_LEFT_REAR_SUR_2,     /**< Lrs2 - between Lrs and Lcs          */
	DPF_CHANNEL_RIGHT_REAR_SUR_2,    /**< Rrs2 - between Rrs and Rcs          */
	DPF_CHANNEL_LEFT_CENTER_SUR,     /**< Lcs - between Cs and Lrs2           */
	DPF_CHANNEL_RIGHT_CENTER_SUR,    /**< Rcs - between Cs and Rrs2           */
	DPF_CHANNEL_LEFT_FRONT_HEIGHT,   /**< Lfh (Lvh) -  above front left       */
	DPF_CHANNEL_RIGHT_FRONT_HEIGHT,  /**< Rfh (Rvh) -  above front right      */
	DPF_CHANNEL_CENTER_FRONT_HEIGHT, /**< Cvh - above front center            */
	DPF_CHANNEL_LEFT_TOP_FRONT,      /**< Ltf - left ceiling towards front    */
	DPF_CHANNEL_RIGHT_TOP_FRONT,     /**< Rtf - right ceiling towards front   */
	DPF_CHANNEL_LEFT_TOP_MIDDLE,     /**< Ltm - left ceiling above listener   */
	DPF_CHANNEL_RIGHT_TOP_MIDDLE,    /**< Rtm - right ceiling above listener  */
	DPF_CHANNEL_TOP_SURROUND,        /**< Ts - mono top surround              */
	DPF_CHANNEL_LEFT_TOP_REAR,       /**< Ltr - left ceiling towards rear     */
	DPF_CHANNEL_RIGHT_TOP_REAR,      /**< Rtr - right ceiling towards rear    */
	DPF_CHANNEL_LEFT_REAR_HEIGHT,    /**< Lrh - left height on rear wall      */
	DPF_CHANNEL_RIGHT_REAR_HEIGHT,   /**< Rrh - right height on rear wall     */
    DPF_CHANNEL_SINGLE_HEIGHT,       /**< Sh - single height                  */
	DPF_CHANNEL_VOICE_ASSISTANT_LEFT, /**< Val - single height                  */
	DPF_CHANNEL_VOICE_ASSISTANT_RIGHT,/**< Var - single height */
	DPF_CHANNEL_SYSTEM_SOUND_LEFT,    /**< Ssl - single height */
	DPF_CHANNEL_SYSTEM_SOUND_RIGHT,   /**< Ssr - single height */
	DPF_CHANNEL_UNUSED,              /**< unused                              */
	DPF_CHANNEL_UNKNOWN              /**< Channel present, assignment unknown */
} dpf_channel_id;


enum udc_outputmap_bits
{
	UDC_OUTPUTMAP_L = 0,                /**< Output map bit for L                                  */
	UDC_OUTPUTMAP_C = 1,                /**< Output map bit for C                                  */
	UDC_OUTPUTMAP_R = 2,                /**< Output map bit for R                                  */
	UDC_OUTPUTMAP_LS = 3,               /**< Output map bit for Ls                                 */
	UDC_OUTPUTMAP_RS = 4,               /**< Output map bit for Rs                                 */
	UDC_OUTPUTMAP_LFE = 15              /**< Output map bit for LFE                                */
};

/******************************************************************************
 * 						Macro define Section
 *****************************************************************************/
typedef enum
{
    DATMOS_SPEAKER_PRESENCE_OFF = 0,
    DATMOS_SPEAKER_PRESENCE_ON
} datmos_ht_speaker_presence;

typedef enum
{
    /* Standard speakers*/
    DATMOS_SPEAKER_ID_C         = AR_SPEAKER_C_INDEX,
    DATMOS_SPEAKER_ID_L_R       = AR_SPEAKER_L_R_INDEX,
    DATMOS_SPEAKER_ID_LS_RS     = AR_SPEAKER_LS_RS_INDEX,
    DATMOS_SPEAKER_ID_LRS_RRS   = AR_SPEAKER_LRS_RRS_INDEX,
    DATMOS_SPEAKER_ID_LTF_RTF   = AR_SPEAKER_LTF_RTF_INDEX,
    DATMOS_SPEAKER_ID_LTM_RTM   = AR_SPEAKER_LTM_RTM_INDEX,
    DATMOS_SPEAKER_ID_LTR_RTR   = AR_SPEAKER_LTR_RTR_INDEX,
    DATMOS_SPEAKER_ID_LFE       = AR_SPEAKER_LFE_INDEX,
    DATMOS_SPEAKER_ID_LE_RE     = AR_SPEAKER_MASK_MAX_INDEX + 1,
    DATMOS_SPEAKER_ID_LSE_RSE   = AR_SPEAKER_MASK_MAX_INDEX + 2,
    DATMOS_SPEAKER_ID_LRSE_RRSE = AR_SPEAKER_MASK_MAX_INDEX + 3,
    DATMOS_SPEAKER_ID_LFH_RFH   = AR_SPEAKER_LFH_RFH_INDEX,
    DATMOS_SPEAKER_ID_LRH_RRH   = AR_SPEAKER_LRH_RRH_INDEX,
    DATMOS_SPEAKER_ID_SH        = AR_SPEAKER_SH_INDEX,

    /* Extended speakers */
    DATMOS_SPEAKER_ID_LSC_RSC   = AR_SPEAKER_LSC_RSC_INDEX,
    DATMOS_SPEAKER_ID_LC_RC     = AR_SPEAKER_LC_RC_INDEX,
    DATMOS_SPEAKER_ID_LW_RW     = AR_SPEAKER_LW_RW_INDEX,
    DATMOS_SPEAKER_ID_LS1_RS1   = AR_SPEAKER_LS1_RS1_INDEX,
    DATMOS_SPEAKER_ID_LS2_RS2   = AR_SPEAKER_LS2_RS2_INDEX,
    DATMOS_SPEAKER_ID_LRS1_RRS1 = AR_SPEAKER_LRS1_RRS1_INDEX,
    DATMOS_SPEAKER_ID_LRS2_RRS2 = AR_SPEAKER_LRS2_RRS2_INDEX,
    DATMOS_SPEAKER_ID_LCS_RCS   = AR_SPEAKER_LCS_RCS_INDEX,
    DATMOS_SPEAKER_ID_CS        = AR_SPEAKER_CS_INDEX,
    DATMOS_SPEAKER_ID__LAST_    = AR_SPEAKER_MASK_MAX_INDEX + 4
} datmos_ht_speaker_id;

typedef enum
{
    DATMOS_HT_GRAPH_TYPE_UNKNOWN = -1,
    DATMOS_HT_GRAPH_TYPE_DIRECTDEC,
    DATMOS_HT_GRAPH_TYPE_DIRECTDEC_WDMX,
    DATMOS_HT_GRAPH_TYPE_REGULAR,
    DATMOS_HT_GRAPH_TYPE_EXTENDED,
	DATMOS_HT_GRAPH_TYPE_TUNING
}datmos_ht_graph_type;
#endif
