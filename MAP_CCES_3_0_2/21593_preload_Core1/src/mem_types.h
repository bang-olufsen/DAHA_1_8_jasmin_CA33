/*
 * Copyright (c) 2018-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

#ifndef MEM_TYPES_H
#define MEM_TYPES_H

/* enumerate supported memory types used as the non-zero value for CONFIG_DMC0 */
#define DMC_NONE                      (0)
#define ISSI_4Gb_DDR3_800MHZ          (1)
#define ISSI_8Gb_DDR3_800MHZ          (2)
#define ISSI_4Gb_DDR3_667MHZ          (3)
#define ISSI_8Gb_DDR3_667MHZ          (4)
#define ISSI_4Gb_DDR3_900MHZ          (5)
#define ISSI_8Gb_DDR3_900MHZ          (6)
#define WINBOND_2Gb_DDR3_800MHZ       (7)

/* enumerate supported operating temperature ranges of DDR memory
 * - refer to DDR memory data sheet for more details and temperature options
 */
#define NORMAL_TEMPERATURE            (0) /*!< DRAM is operated below 85C */
#define EXTENDED_TEMPERATURE          (1) /*!< DRAM is operated above 85C */

#endif /* MEM_TYPES_H */
