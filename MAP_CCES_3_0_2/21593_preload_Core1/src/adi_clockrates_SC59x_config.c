/*
 * Copyright (c) 2020-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

#include <stdlib.h>
#include <sys/platform.h>
#include <services/pwr/adi_pwr.h>
#include <services/tmr/adi_tmr.h>

#include "adi_clockrates_SC59x_config.h"

#ifdef _MISRA_RULES
#pragma diag(suppress:misra_rule_14_7:"Allow functions to have multiple exits for better readability and optimized code")
#pragma diag(suppress:misra_rule_5_6:"The fsysclk name etc used is the same as a fields of a type in adi_pwr.h.")
#endif

uint32_t adi_uart_byte_delay(int32_t boot_cmd_device)
{
    if (boot_cmd_device == ENUM_ROM_BCMD_DEVICE_UART)
    {
        ADI_TMR_HANDLE phTMR = NULL;
        ADI_TMR_CFG_PARAMS ConfigParams;
        uint8_t TimerMemory[ADI_TMR_MEMORY];
        ADI_TMR_RESULT Result;

        /*Read UART Clock Div value*/
        uint32_t clockdiv = *pREG_UART0_CLK;

        *pREG_UART0_CTL &= ~BITM_UART_CTL_ARTS; /* Disable Automatic RTS, so we add a delay for only 2 Bytes */
        *pREG_UART0_CTL &= ~BITM_UART_CTL_MRTS; /* De-assert RTS manually */

        /* Open the Timer Device */
        Result = adi_tmr_Open( 0u,              /* TimerNum */
                               TimerMemory,     /* pMemory */
                               ADI_TMR_MEMORY,  /* nMemSize */
                               NULL,
                               NULL,            /* pCBParam */
                               &phTMR);
        if (Result != ADI_TMR_SUCCESS)
        {
            return 1u;
        }

        /*Configure the device in Single PWM Out Mode*/
        ConfigParams.Mode = ADI_TMR_MODE_SINGLE_PWMOUT;
        ConfigParams.PulsePolarity = true;
        ConfigParams.ClkInSource = ADI_TMR_CLKIN_SYSCLK;
        ConfigParams.InputAuxIn = false;

        /*Add a 2 x 10 bit UART Clock delay (10 Bits = 1 Byte + 1 Start Bit + 1 Stop Bit) */
        ConfigParams.Width = 2u * 10u * 16u * clockdiv;
        ConfigParams.Delay = 0u;

        Result = adi_tmr_Config(phTMR, &ConfigParams);
        if (Result != ADI_TMR_SUCCESS)
        {
            return 1u;
        }

        /*Enable the timer*/
        Result = adi_tmr_Enable(phTMR, true);
        if (Result != ADI_TMR_SUCCESS)
        {
            return 1u;
        }

        /*Wait for the TIMER_RUN bit to be cleared*/
        while ((*pREG_TIMER0_RUN & BITM_TIMER_RUN_TMR00) != 0u) { }

        /*Close the timer*/
        Result = adi_tmr_Close(phTMR);
        if (Result != ADI_TMR_SUCCESS)
        {
            return 1u;
        }
    }

    return 0u;
}

/**
 * @brief   This API returns the Baud Rate of UART
 * @details This API returns the Baud Rate of UART by reading the current SCLK0 value
 *

 * @return  baud if boot mode is UART boot mode
 *          1    if there is an error determining the system clock frequency
 *          0    if boot mode is not UART boot mode
 *
 * @note
 **/
uint32_t adi_uart_baud_read(int32_t boot_cmd_device)
{
    uint32_t fsysclk;
    uint32_t fsclk0;
    uint32_t fsclk1;
    uint32_t clockdiv;
    uint32_t baud;

    if (boot_cmd_device == ENUM_ROM_BCMD_DEVICE_UART)
    {
        /*read clock div*/
        clockdiv = *pREG_UART0_CLK;

        /*get system clock frequency*/
        if(adi_pwr_GetSystemFreq(0u,&fsysclk,&fsclk0,&fsclk1) != ADI_PWR_SUCCESS)
        {
            return 1u;
        }

        /*calculate the baud rate*/
        baud = fsclk0 / (16u * clockdiv);
        return baud;
    }

    return 0u;
}

/**
 * @brief    This API programs the UART Clock register with new baud rate.
 * @details  This API programs the UART Clock register with new baud rate, by reading the new SCLK0 value
 *
 * @return      0    if boot mode is UART boot mode
 *              1    if boot mode is UART boot mode
 * @note
 **/
uint32_t adi_uart_baud_init(int32_t boot_cmd_device, uint32_t UART_Baud_Rate_Val)
{
    uint32_t   fsysclk;
    uint32_t   fsclk0;
    uint32_t   fsclk1;
    uint32_t   clockdiv;

    if (boot_cmd_device == ENUM_ROM_BCMD_DEVICE_UART)
    {
        /*get system clock frequency*/
        if(adi_pwr_GetSystemFreq(0u,&fsysclk,&fsclk0,&fsclk1) != ADI_PWR_SUCCESS)
        {
            return 1u;
        }

        /*calculate the clock div*/
        clockdiv = fsclk0 / (16u * UART_Baud_Rate_Val);

        /*write clock div*/
        *pREG_UART0_CLK = clockdiv;

        /*Re enable the ARTS so that the transmitter starts sending the remaing part of the boot stream*/
        *pREG_UART0_CTL |= BITM_UART_CTL_ARTS;

        return 0u;
    }

    return 1u;
}

/**
 * @brief       Programs SPI Clock Rate
 * @details     This API can be used to program the clock rate of SPI during SPI boot modes.
 *              It verifies first whether the boot mode is SPI or SPI XIP.
 *
 * @param[in]   SPI_Clock_Rate_Val Clock Rate value
 *
 * @return      0    if boot mode is SPI or SPI XIP
 *              1    if boot mode is not SPI or SPI XIP
 *
 * @note
 **/
uint32_t adi_spi_clock_rate(int32_t boot_cmd_device, uint32_t SPI_Clock_Rate_Val)
{
    if ((boot_cmd_device == ENUM_ROM_BCMD_DEVICE_SPI) ||
        (boot_cmd_device == ENUM_ROM_BCMD_DEVICE_SPIXIP))
    {
        *pREG_SPI2_CLK = (uint32_t) SPI_Clock_Rate_Val;

        return 0u;
    }

    return 1u;
}

/**
 * @brief       Programs OSPI Clock Rate
 * @details     This API can be used to program the clock rate of OSPI during OSPI master boot mode.
 *              It verifies first whether the boot mode is indeed OSPI master boot.
 *
 * @param[in]   OSPI_Clock_Rate_Val Clock Rate value
 * @param[in]   Readcapdelay Read Cap Delay
 *
 * @return      0    if boot mode is OSPI Master boot mode
 *              1    if boot mode is not OSPI Master boot mode
 *
 * @note
 **/
uint32_t adi_ospi_clock_rate(int32_t boot_cmd_device, uint32_t OSPI_Clock_Rate_Val, uint8_t Readcapdelay)
{

    if (boot_cmd_device == ENUM_ROM_BCMD_DEVICE_OSPI)
    {
        *pREG_OSPI0_CTL &= ~BITM_OSPI_CTL_BAUD;
        *pREG_OSPI0_CTL |= (OSPI_Clock_Rate_Val << BITP_OSPI_CTL_BAUD) & BITM_OSPI_CTL_BAUD;
        *pREG_OSPI0_RDC = (((uint32_t)Readcapdelay << BITP_OSPI_RDC_DLYRD) & BITM_OSPI_RDC_DLYRD) | BITM_OSPI_RDC_SMPLEDG;

        return 0u;
    }

    return 1u;
}

