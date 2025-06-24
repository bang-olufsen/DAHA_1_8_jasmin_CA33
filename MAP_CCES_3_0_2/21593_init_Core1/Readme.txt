    1.  Description

        This example demonstrates how to build the initialization code for ADSP-SC594 and ADSP-SC598 families of processors.

        Refer to the source code embedded Doxygen documentation comments in the SC59x_InitPreload_code.c for further details.

        There are 11 projects covered by this common readme :-
          2159x_init        - Initialization code project for ADSP-2159x to be used as the basis for custom hardware support.
          2159x_preload     - CCES preload code project to be used as the basis for custom hardware support.

          SC59x_init        - Initialization code project for ADSP-SC59x to be used as the basis for custom hardware support for the Cortex-A5.
          SC59x_preload     - CCES preload code project to be used as the basis for custom hardware support for the Cortex-A5.

          SC59x_init_a55    - Initialization code project for ADSP-SC59x to be used as the basis for custom hardware support for the Cortex-A55.
          SC59x_preload_a55 - CCES preload code project to be used as the basis for custom hardware support for the Cortex-A55.

          21593_init        - Initialization code project for the EV-21593-SOM Board.
          21593_preload     - CCES preload code project for the EV-21593-SOM Board.

          SC594W_init_Core0    - Initialization code project for the EV-SC594-SOM Board.
          SC594W_preload_Core0 - CCES preload code project for the EV-SC594-SOM Board.

          SC589W_init_Core0    - Initialization code project for Cortex-A55 core 0 on the EV-SC598-SOM Board.
          SC589W_preload_Core0 - CCES preload code project for the Cortex-A55 core 0 on the EV-SC598-SOM Board.
          SC589W_preload_Core1 - CCES preload code project for the SHARC+ core 1 on the EV-SC598-SOM Board.

        The clock frequencies configured for EV-SC594-SOM and EV-21593-SOM boards support are :-

          SHARC0 & its Accelerators  (CLKO0) : CCLK0_0      : 1000 MHz
          SHARC1 & its Accelerators  (CLKO1) : CCLK0_0      : 1000 MHz
          ARM                        (CLKO2) : CCLK1_0      : 1000 MHz
          DDR                        (CLKO3) : DCLK_1       :  800 MHz
          CANFD                      (CLKO4) : OCLK_1       :  100 MHz
          SPDIF                      (CLKO5) : SCLK1_EXEN_0 :  333.3 MHz
          SPI                        (CLKO6) : SCLK0_0      :  125 MHz
          GigE                       (CLKO7) : SCLK0_0      :  125 MHz
          LP                         (CLKO8) : SCLK0_0      :  125 MHz
          LP_DDR                     (CLKO9) : OCLK_0       :  250 MHz
          OSPI_REFCLK                (CLKO10): SYSCLK_0     :  500 MHz
          TRACE                      (CLKO12): SCLK0_0      :  125 MHz

        The clock frequencies configured for EV-SC598-SOM are :-

          SHARC0 & its Accelerators  (CLKO0) : CCLK0_0          : 1000 MHz
          SHARC1 & its Accelerators  (CLKO1) : CCLK0_0          : 1000 MHz
          ARM                        (CLKO2) : CCLK2_1          : 1200 MHz
          DDR                        (CLKO3) : DCLK_2(3rd PLL)  :  800 MHz
          CANFD                      (CLKO4) : OCLK_1           :  100 MHz
          SPDIF                      (CLKO5) : SCLK1_EXEN_0     :  333.3 MHz
          SPI                        (CLKO6) : SCLK0_0          :  125 MHz
          GigE                       (CLKO7) : SCLK0_0          :  125 MHz
          LP                         (CLKO8) : SCLK0_0          :  125 MHz
          LP_DDR                     (CLKO9) : OCLK_0           :  250 MHz
          OSPI_REFCLK                (CLKO10): SYSCLK_0         :  500 MHz
          TRACE                      (CLKO12): SCLK0_0          :  125 MHz
          EMMC                       (CLKO13): SCLK0_EXEN_1     :  50 MHz
          EMMC TIMER CMQ             (CLKO14): (SCLK1_EXEN_1)/2 :  10 MHz

        The initializations done for EV-SC594-SOM and EV-21593-SOM board support are defined using MACROs in the config.h include as shown below :-

          /*Common macros*/
          #define CLKIN   (25000000)               /*!< SYS_CLKIN value*/
          #define CONFIG_SHARC_CORE_CLOCK (CORE_CLOCK_1GHZ) /*!< SHARC and ARM Core Clock frequency */
          #define CONFIG_DMC0 (ISSI_8Gb_DDR3_800MHZ)/*!< Define as 0, if there is no DDR on the board or the chip. Note care to be taken to make sure DDR clock frequency is configured correctly in CGU/CDU */
          #define CONFIG_DRAM_TEMP (NORMAL_TEMPERATURE) /*!< Choose the operating temperature range of DDR memory*/
          #define CONFIG_SPIFLASH (1)              /*!< Define as 0, if there is no SPI Flash on the board or the chip*/
          #define EXECUTE_SAFE_STATE (1)           /*!< Define as 1, if the program must go in to a safe state up on errors in the API calls*/
          #define INIT_CANFD (1)                   /*!< Define to 1 for parts that have CANFD*/

          /*Boot related macros*/
          #define CONFIG_BOOT_UART_BAUD_RATE (0)   /*!< Define as 1, if the UART Baud Rate need to be recalculated and reinitialized*/
          #define CONFIG_BOOT_SPI_CLOCK_RATE (0)   /*!< Define as 1, if the SPI Clock Rate need to be recalculated and reinitialized*/
          #define CONFIG_BOOT_OSPI_CLOCK_RATE (0)  /*!< Define as 1, if the OSPI Clock Rate need to be recalculated and reinitialized*/
          #define DO_PROCESS_BOOTSTRUCT (0)        /*!< Define as 1, if there is need to process the boot struct passed by ROM*/

        The config.h macro defines for EV-SC598-SOM are the same as above except for the following additional configuration macros :-

          #define CONFIG_DMC0 (ISSI_4Gb_DDR3_800MHZ) /*!< Define as 0, if there is no DDR on the board or the chip. Note care to be taken to make sure DDR clock frequency is configured correctly in CGU/CDU */
          #define INIT_EMSI (1)                    /*!< Define to 1 for EMSI boot initializations*/

        The six base projects have no macro definitions provided in config.h and instead there is a preprocessor
        #error statement as a reminder that configuration for custom hardware is required when using these projects.
        The base projects are: 2159x_init, 2159x_preload, SC59x_init, SC59x_preload, sc59x_init_a55, sc59x_preload_a55.

    2.  Processors

        ADSP-21593, ADSP-SC594W, ADSP-SC598W

    3.  References

        SHARC+ Core Programming Reference
        ADSP-SC59x/ADSP-2159x SHARC+ Processor Hardware Reference
        EV-21593-SOM Manual
        EV-SC594-SOM Manual
        EV-SC598-SOM Manual

