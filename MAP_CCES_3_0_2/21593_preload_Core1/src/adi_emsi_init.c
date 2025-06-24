/*
 * Copyright (c) 2020-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

#include "adi_emsi_init.h"

#if INIT_EMSI

#include <sys/platform.h>

/* Command macros */
#define CMD_SWITCH ((6u << BITP_EMSI_CMD_INDEX) | \
                    ENUM_EMSI_CMD_NORMAL_CMD | \
                    ENUM_EMSI_CMD_NO_DATA | \
                    ENUM_EMSI_CMD_CMD_IDX_CHK_ENABLED | \
                    ENUM_EMSI_CMD_CMD_CRC_CHK_ENABLED | \
                    ENUM_EMSI_CMD_MAIN | \
                    ENUM_EMSI_CMD_RESP_LEN_48B)

#define CMD_STATUS ((13u << BITP_EMSI_CMD_INDEX) | \
                    ENUM_EMSI_CMD_NORMAL_CMD | \
                    ENUM_EMSI_CMD_NO_DATA|ENUM_EMSI_CMD_CMD_IDX_CHK_ENABLED | \
                    ENUM_EMSI_CMD_CMD_CRC_CHK_ENABLED | \
                    ENUM_EMSI_CMD_MAIN|ENUM_EMSI_CMD_RESP_LEN_48)

/* Macros to be used for the switch command */
#define BITP_VALUE 8
#define BITP_INDEX 16
#define BITP_ACCESS 24
#define ACCESS_WRITEBYTE 3

/* EMSI pinmux configuration macros */
#define EMSI0_CD_PORTB_MUX  ((uint32_t) ((uint32_t) 2<<30))
#define EMSI0_CLK_PORTE_MUX  ((uint32_t) ((uint32_t) 1<<18))
#define EMSI0_CMD_PORTG_MUX  ((uint16_t) ((uint16_t) 2<<2))
#define EMSI0_D0_PORTD_MUX  ((uint32_t) ((uint32_t) 1<<30))
#define EMSI0_D1_PORTE_MUX  ((uint16_t) ((uint16_t) 1<<2))
#define EMSI0_D2_PORTE_MUX  ((uint16_t) ((uint16_t) 2<<12))
#define EMSI0_D3_PORTE_MUX  ((uint32_t) ((uint32_t) 1<<16))
#define EMSI0_D4_PORTG_MUX  ((uint16_t) ((uint16_t) 2<<4))
#define EMSI0_D5_PORTG_MUX  ((uint32_t) ((uint32_t) 1<<16))
#define EMSI0_D6_PORTG_MUX  ((uint32_t) ((uint32_t) 3<<18))
#define EMSI0_D7_PORTG_MUX  ((uint32_t) ((uint32_t) 1<<20))
#define EMSI0_LED_CONTROL_PORTI_MUX  ((uint16_t) ((uint16_t) 1<<12))
#define EMSI0_RST_PORTC_MUX  ((uint16_t) ((uint16_t) 2<<8))
#define EMSI0_WP_PORTC_MUX  ((uint16_t) ((uint16_t) 2<<12))

#define EMSI0_CD_PORTB_FER  ((uint32_t) ((uint32_t) 1<<15))
#define EMSI0_CLK_PORTE_FER  ((uint32_t) ((uint32_t) 1<<9))
#define EMSI0_CMD_PORTG_FER  ((uint16_t) ((uint16_t) 1<<1))
#define EMSI0_D0_PORTD_FER  ((uint32_t) ((uint32_t) 1<<15))
#define EMSI0_D1_PORTE_FER  ((uint16_t) ((uint16_t) 1<<1))
#define EMSI0_D2_PORTE_FER  ((uint16_t) ((uint16_t) 1<<6))
#define EMSI0_D3_PORTE_FER  ((uint32_t) ((uint32_t) 1<<8))
#define EMSI0_D4_PORTG_FER  ((uint16_t) ((uint16_t) 1<<2))
#define EMSI0_D5_PORTG_FER  ((uint32_t) ((uint32_t) 1<<8))
#define EMSI0_D6_PORTG_FER  ((uint32_t) ((uint32_t) 1<<9))
#define EMSI0_D7_PORTG_FER  ((uint32_t) ((uint32_t) 1<<10))
#define EMSI0_LED_CONTROL_PORTI_FER  ((uint16_t) ((uint16_t) 1<<6))
#define EMSI0_RST_PORTC_FER  ((uint16_t) ((uint16_t) 1<<4))
#define EMSI0_WP_PORTC_FER  ((uint16_t) ((uint16_t) 1<<6))


/*******************************************************************************
    Function name : check_switch_response
    Description   : This function is used to confirm a short response is
                    received correctly.
    Arguments     : None
    Return value  : 0 if successful and 1 if fails
 ******************************************************************************/
static int32_t check_switch_response(void)
{
    /* store the interrupt status */
    uint32_t err_stat = *pREG_EMSI0_ERR_STAT;

    /* check if a command timeout occured */
    if ((err_stat & BITM_EMSI_ERR_STAT_CMD_TOUT_ERR) != 0u)
    {
        /* clear the interrupt and return an error */
        *pREG_EMSI0_ERR_STAT = BITM_EMSI_ERR_STAT_CMD_TOUT_ERR;
        return 1;
    }

    /* check if a CRC failure occured */
    if ((err_stat & BITM_EMSI_ERR_STAT_CMD_CRC_ERR) != 0u)
    {
        /* clear the interrupt and return an error */
        *pREG_EMSI0_ERR_STAT = BITM_EMSI_ERR_STAT_CMD_CRC_ERR;
        return 1;
    }

    /* check for end bit error */
    if ((err_stat & BITM_EMSI_ERR_STAT_CMD_END_BIT_ERR) != 0u)
    {
        /* clear the interrupt and return an error */
        *pREG_EMSI0_ERR_STAT = BITM_EMSI_ERR_STAT_CMD_END_BIT_ERR;
        return 1;
    }

    /* check for a long response */
    if ((*pREG_EMSI0_CMD & ENUM_EMSI_CMD_RESP_LEN_136) != 0u)
    {
        return 1;
    }

    /* response received as expected */
    return 0;
}

/*******************************************************************************
    Function name : send_command
    Description   : Simplified function to send a particular command and
                    argument to the card.
    Arguments     : cmd- is the command index values from range 0-63.
                    arg- is the argument to be sent in the command fields.
    Return value  : None
 ******************************************************************************/
static void send_command (uint32_t cmd, uint32_t arg)
{
    while ((*pREG_EMSI0_PSTATE & BITM_EMSI_PSTATE_CMD_INHIBIT) != 0u)
    {
        /* wait till CMD line become free to issue command */
    }

    *pREG_EMSI0_ARG = arg;
    *pREG_EMSI0_CMD = cmd;

    if ((*pREG_EMSI0_TRNSFRMODE & BITM_EMSI_TRNSFRMODE_RESP_INT_DIS) == 0u)
    {
        while ((*pREG_EMSI0_ISTAT & BITM_EMSI_ISTAT_CMD_COMPLETE) == 0u)
        {
            /* wait till command gets completed */
        }
        /* clearing the interrupt */
        *pREG_EMSI0_ISTAT = BITM_EMSI_ISTAT_CMD_COMPLETE;
    }
}


/*******************************************************************************
    Function name : check_switch_success
    Description   : Check if the switch command was successful by reading 
                    the card status.
    Arguments     : None
    Return value  : 0 if successful and 1 if fails
 ******************************************************************************/
static int32_t check_switch_success (void)
{
    /* Stores the Relative Card Address (RCA) read from the SD card or published
     * to the eMMC card.
    */
    static volatile uint16_t card_rca = 1u;
    send_command(CMD_STATUS, card_rca<<16);
    if ((check_switch_response() != 0) || ((*pREG_EMSI0_RESP0 & 0x80u) != 0u))
    {
        return 1;
    }
    return 0;
}


/*******************************************************************************
    Function name : set_bus_width
    Description   : Specialized function to configure MMC card's bus width
                    to 8-bit SDR mode.
    Arguments     : None
    Return value  : 0 if successful and 1 if fails
 ******************************************************************************/
static int32_t set_bus_width (void)
{
    uint32_t bus_width_arg = 2u;

    /* Send the CMD6 (SWITCH) command to change the bus width */
    send_command(CMD_SWITCH, ((bus_width_arg << BITP_VALUE) |
                             (183 << BITP_INDEX) |
                             (ACCESS_WRITEBYTE << BITP_ACCESS)));

    while ((*pREG_EMSI0_PSTATE & BITM_EMSI_PSTATE_DAT_LINE_ACTIVE) != 0u)
    {
        /* Wait for D0 line to get clear */
    }

    /* Update the control 1 register for 8-bit mode */
    *pREG_EMSI0_CTL1 &= ~(BITP_EMSI_CTL1_EXT_DAT_XFER |
                          BITP_EMSI_CTL1_DAT_XFER_WIDTH);
    *pREG_EMSI0_CTL1 |= ENUM_EMSI_CTL1_EIGHT_BIT;

    /* check if the switch was successful by reading the card status */
    return check_switch_success();
}


/*******************************************************************************
    Function name : enable_high_speed_mode
    Description   : Enables MMC high speed mode (52 MHz MSI_CLK speed).
    Arguments     : None
    Return value  : 0 if successful and 1 if fails
 ******************************************************************************/
static int32_t enable_high_speed_mode(void)
{
    /* send the CMD6 (SWITCH) command to change the speed mode */
    send_command(CMD_SWITCH, ((1u << BITP_VALUE) |
                              (185u << BITP_INDEX) |
                              (ACCESS_WRITEBYTE<<BITP_ACCESS)));

    while ((*pREG_EMSI0_PSTATE & BITM_EMSI_PSTATE_DAT_LINE_ACTIVE) != 0u)
    {
        /* Wait for D0 line to get clear */
    }

    /* putting controller into high speed SDR mode */
    *pREG_EMSI0_CTL2 &= ~BITM_EMSI_CTL2_SD_EMMC_MODE_SEL;
    *pREG_EMSI0_CTL2 |= ENUM_EMSI_CTL2_SDR25;

    /* select high speed mode from controller side (>25-50 MHz) */
    *pREG_EMSI0_CTL1 |= BITM_EMSI_CTL1_HIGH_SPEED_EN;

    return check_switch_success();
}


/*******************************************************************************
    Function name : pinmux_init
    Description   : Initialize pinux.
    Arguments     : None
    Return value  : None
 ******************************************************************************/
static void pinmux_init(void)
{
    *pREG_PORTB_MUX = EMSI0_CD_PORTB_MUX;
    *pREG_PORTC_MUX = EMSI0_RST_PORTC_MUX | EMSI0_WP_PORTC_MUX;
    *pREG_PORTD_MUX = EMSI0_D0_PORTD_MUX;
    *pREG_PORTE_MUX = EMSI0_CLK_PORTE_MUX | EMSI0_D1_PORTE_MUX |
                      EMSI0_D2_PORTE_MUX | EMSI0_D3_PORTE_MUX;
    *pREG_PORTG_MUX = EMSI0_CMD_PORTG_MUX | EMSI0_D4_PORTG_MUX |
                      EMSI0_D5_PORTG_MUX | EMSI0_D6_PORTG_MUX |
                      EMSI0_D7_PORTG_MUX;
    *pREG_PORTI_MUX = EMSI0_LED_CONTROL_PORTI_MUX;

    *pREG_PORTB_FER = EMSI0_CD_PORTB_FER;
    *pREG_PORTC_FER = EMSI0_RST_PORTC_FER | EMSI0_WP_PORTC_FER;
    *pREG_PORTD_FER = EMSI0_D0_PORTD_FER;
    *pREG_PORTE_FER = EMSI0_CLK_PORTE_FER | EMSI0_D1_PORTE_FER |
                      EMSI0_D2_PORTE_FER | EMSI0_D3_PORTE_FER;
    *pREG_PORTG_FER = EMSI0_CMD_PORTG_FER | EMSI0_D4_PORTG_FER |
                      EMSI0_D5_PORTG_FER | EMSI0_D6_PORTG_FER |
                      EMSI0_D7_PORTG_FER;
    *pREG_PORTI_FER = EMSI0_LED_CONTROL_PORTI_FER;
}


/*******************************************************************************
    Function name : adi_emsi_init
    Description   : Enables MMC high speed 8-bit SDR mode to switch from safe
                    mode for eMMC boot initcode.
    Arguments     : None
    Return value  : 0 if successful and non-zero if fails
 ******************************************************************************/
int32_t adi_emsi_init(void)
{
    int32_t result = 0;

    /* init the pinmux */
    pinmux_init();

    /* put card and controller into high speed SDR mode */
    result = enable_high_speed_mode();

    /* put card and controller into 8-bit SDR mode */
    result += set_bus_width();

    /* configure tuning support */
    *pREG_PADS0_PCFG0 |= BITM_PADS_PCFG0_EMSI_TUNING_EN;
    *pREG_PADS0_PCFG1 |= (4u << BITP_PADS_PCFG1_EMSI_TUNING_MUX_SEL);

    return result;
}

#endif /* #if INIT_EMSI */

