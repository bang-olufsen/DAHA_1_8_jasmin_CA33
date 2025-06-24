/*
 * Copyright (c) 2020-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

#ifndef ADSP2159X_INIT_CONFIG_H
#define ADSP2159X_INIT_CONFIG_H

#include "mem_types.h"
#include "clock_configs.h"

/* Define any non-default configuration macros here
 * and then delete the #error.
 */
/*Common macros*/
#define CLKIN   (25000000)               /*!< SYS_CLKIN value*/
#define CONFIG_SHARC_CORE_CLOCK (CORE_CLOCK_1GHZ) /*!< Core Clock frequency */
#define CONFIG_DMC0 (WINBOND_2Gb_DDR3_800MHZ)      /*!< Define as 0, if there is no DDR on the board or the chip*/
#define CONFIG_DRAM_TEMP (NORMAL_TEMPERATURE) /*!< Choose the operating temperature range of DDR memory*/
#define CONFIG_SPIFLASH (1)              /*!< Define as 0, if there is no SPI Flash on the board or the chip*/
#define EXECUTE_SAFE_STATE (1)           /*!< Define as 1, if the program must go in to a safe state up on errors in the API calls*/
#define INIT_CANFD (0)                   /*!< Define to 1 for parts that have CANFD*/
#if !defined (PRELOAD_CODE)
#define INIT_EMSI (0)                    /*!< Define to 1 for EMSI boot initializations*/
#endif
/*Boot related macros*/
#define CONFIG_BOOT_UART_BAUD_RATE (0)   /*!< Define as 1, if the UART Baud Rate need to be recalculated and reinitialized*/

#define CONFIG_BOOT_SPI_CLOCK_RATE (0)   /*!< Define as 1, if the SPI Clock Rate need to be recalculated and reinitialized*/
#define CONFIG_BOOT_SPI_CLOCK_VAL (1)	// Sclk0=125MHz -> ~62MHz (Highest possible speed)

#define CONFIG_BOOT_OSPI_CLOCK_RATE (0)  /*!< Define as 1, if the OSPI Clock Rate need to be recalculated and reinitialized*/
#define DO_PROCESS_BOOTSTRUCT (0)        /*!< Define as 1, if there is need to process the boot struct passed by ROM*/

#endif /* ADSP2159X_INIT_CONFIG_H */
