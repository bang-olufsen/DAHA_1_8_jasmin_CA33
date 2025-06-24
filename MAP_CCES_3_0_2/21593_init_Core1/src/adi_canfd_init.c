/*
 * Copyright (c) 2020-2022 Analog Devices, Inc. All Rights Reserved.
 * This software is proprietary to Analog Devices, Inc. and its licensors.
 */

#include "adi_canfd_init.h"

#if INIT_CANFD

#include <stdint.h>
#include <stddef.h>
#include <sys/platform.h>
#if defined(__ADSPSC594_FAMILY__) || defined(__ADSPSC598_FAMILY__)
#include <ADSP-SC59x_device.h>
#else
#error Unconfigured
#endif

#if !defined(__ADI_HAS_CANFD__)
#error INIT_CANFD defined for a part without CANFD
#endif

/* macros */
#define MB_OFFSET \
  (0x80u)   /* offset of message buffer ram */
#define MB_RAM_SIZE \
  (64u*16u) /* 64 message buffers with 8 byte header and 8 byte payload */

#define SMB_OFFSET \
  (0xab0u)  /* offset of serial Tx and Rx normal mode message buffer ram */
#define SMB_RAM_SIZE (48u)

#define SMB_FD_OFFSET \
  (0xf58u)  /* offset of serial Tx and Rx FD mode message buffer ram */
#define SMB_FD_RAM_SIZE (168u)

#define RX_FIR_OFFSET \
  (0xa80u)  /* offset of RX FIR space ram */
#define RX_FIR_RAM_SIZE (32u)

/* prototypes */
static void canfd_init (uint32_t canfd_base);

/* Initialize the RAM for a CANFD instance. */
static void canfd_init (uint32_t canfd_base) {
  size_t i, start, end;
  volatile uint32_t *pCANFDMem = (volatile uint32_t *) (uintptr_t) canfd_base;
  volatile ADI_CANFD_TypeDef *pCANFDRegs = (volatile ADI_CANFD_TypeDef *) (uintptr_t) canfd_base;

  /* Set the Freeze and Halt bit to enter freeze mode. */
  pCANFDRegs->CFG |= BITM_CANFD_CFG_FRZ;
  pCANFDRegs->CFG |= BITM_CANFD_CFG_HALT;

  /* Wait for the freeze acknowledgment. */
  while((pCANFDRegs->CFG & BITM_CANFD_CFG_FRZACK) == 0u) { }

  /* Enable unrestricted write access to CANFD memory in Freeze mode. */
  pCANFDRegs->CTL2 |= BITM_CANFD_CTL2_WRMFRZEN;

  /* Initialize the RAM area occupied by message buffers. */
  start = MB_OFFSET/sizeof(*pCANFDMem);
  end   = start + (MB_RAM_SIZE/sizeof(*pCANFDMem));
  for (i=start; i<end; i++) {
    pCANFDMem[i] = 0u;
  }

  /* Initialize the RAM area occupied by some of the CAN registers. */
  pCANFDRegs->RX_MB_GMSK = 0u;
  pCANFDRegs->RX_14_MSK = 0u;
  pCANFDRegs->RX_15_MSK = 0u;
  pCANFDRegs->RX_FIFO_GMSK = 0u;

  /* Initialize the IMSK registers which occupy RAM. */
  for (i=0u;
       i<(sizeof(pCANFDRegs->RX_IMSK)/sizeof(pCANFDRegs->RX_IMSK[0]));
       i++) {
    pCANFDRegs->RX_IMSK[i] = 0u;
  }

  /* Initialize additional memory used for internal Serial Tx and Rx MB
   * buffer structures for FD mode.
   */
  start = SMB_FD_OFFSET/sizeof(*pCANFDMem);
  end   = start + (SMB_FD_RAM_SIZE/sizeof(*pCANFDMem));
  for (i=start; i<end; i++) {
    pCANFDMem[i] = 0u;
  }

  /* Initialize additional memory used for internal Serial Tx and Rx MB
   * buffer structures for Normal CAN mode.
   */
  start = SMB_OFFSET/sizeof(*pCANFDMem);
  end   = start + (SMB_RAM_SIZE/sizeof(*pCANFDMem));
  for (i=start; i<end; i++) {
    pCANFDMem[i] = 0u;
  }

  /* Initialize additional memory used for internal RAM space used for
   * storing RXFIR contents and some reserved space.
   */
  start = RX_FIR_OFFSET/sizeof(*pCANFDMem);
  end   = start + (RX_FIR_RAM_SIZE/sizeof(*pCANFDMem));
  for (i=start; i<end; i++) {
    pCANFDMem[i] = 0u;
  }

  /* Disable the unrestricted write access to CANFD memory in Freeze mode. */
  pCANFDRegs->CTL2 &= ~BITM_CANFD_CTL2_WRMFRZEN;

  /* Clear the Freeze and Halt bit to exit the freeze mode. */
  pCANFDRegs->CFG &= ~(BITM_CANFD_CFG_FRZ|BITM_CANFD_CFG_HALT);

  /* Wait for the freeze acknowledgment to be cleared. */
  while((pCANFDRegs->CFG & BITM_CANFD_CFG_FRZACK) != 0u) { }

} /* canfd_init */

/* Initialize the RAM for each CANFD. */
void adi_canfd_init (void)
{
#if defined(__ADI_HAS_CANFD0__)
  canfd_init ((uint32_t)ADI_CANFD0_BASE);
#endif
#if defined(__ADI_HAS_CANFD1__)
  canfd_init ((uint32_t)ADI_CANFD1_BASE);
#endif
} /* adi_canfd_init */

#endif /* INIT_CANFD */
