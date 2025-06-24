/*
 * Copyright (c) 2020-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

/*!
* @file      adi_clockrates_SC59x_config.h
*
* @brief     Header file for clock rate configurations.
*
* @details
*
*/

#ifndef INC_ADI_CLOCK_SC59X_CONFIG_H
#define INC_ADI_CLOCK_SC59X_CONFIG_H

#include <stdint.h>
#include <cdefSC59x_rom.h>

#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_5_1:"Allow identifiers to be more than 31 characters")
#endif

#ifdef __cplusplus
extern "C" {
#endif

uint32_t adi_uart_baud_read(int32_t boot_cmd_device);
uint32_t adi_uart_baud_init(int32_t boot_cmd_device, uint32_t UART_Baud_Rate_Val);
uint32_t adi_spi_clock_rate(int32_t boot_cmd_device, uint32_t SPI_Clock_Rate_Val);
uint32_t adi_ospi_clock_rate(int32_t boot_cmd_device, uint32_t OSPI_Clock_Rate_Val, uint8_t Readcapdelay);
uint32_t adi_uart_byte_delay(int32_t boot_cmd_device);


#ifdef __cplusplus
}
#endif

#ifdef _MISRA_RULES
#pragma diag(pop)
#endif /* _MISRA_RULES */

#endif /* INC_ADI_CLOCKRATES_SC59X_CONFIG_H */
