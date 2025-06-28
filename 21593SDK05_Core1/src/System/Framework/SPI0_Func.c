/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	SPI0_func.c
*  Description      :   SPI0 Initialization
******************************************************************************/
#pragma default_section(CODE,"Seg_SPI_Func_Code")

#include "..\src\system\Include\Common_macros__extern_definations.h"
#include "stdio.h"
#include "../Include/Function_Prototype.h"
#pragma default_section(ALLDATA,"Seg_SPI_Func_Data")

extern int SPI_Device;
extern int RXSPI;
extern int TXSPI;

/******************************************************************************
*  Module Name        : Init_SPI0
*  Functionality      : Configured SPI0 Module Registers
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/
void Init_SPI0(void)
{
	if (SPI_Device == 1)
	{
		*pREG_SPI1_CLK	= 	((SPI1_BAUD << BITP_SPI_CLK_BAUD) & BITM_SPI_CLK_BAUD);

		*pREG_SPI1_DLY	= (	((SPI1_STOP << BITP_SPI_DLY_STOP) & BITM_SPI_DLY_STOP)	|
							((SPI1_LEADx<< BITP_SPI_DLY_LEADX)& BITM_SPI_DLY_LEADX)	|
							((SPI1_LAGx << BITP_SPI_DLY_LAGX) & BITM_SPI_DLY_LAGX)	);

		*pREG_SPI1_CTL 	= (	((SPI1_MSTR << BITP_SPI_CTL_MSTR) & BITM_SPI_CTL_MSTR)	|
							((SPI1_PSSE << BITP_SPI_CTL_PSSE) & BITM_SPI_CTL_PSSE)	|
							((SPI1_ODM	<< BITP_SPI_CTL_ODM)  & BITM_SPI_CTL_ODM )	|
							((SPI1_CPHA << BITP_SPI_CTL_CPHA) & BITM_SPI_CTL_CPHA)	|
							((SPI1_CPOL << BITP_SPI_CTL_CPOL) & BITM_SPI_CTL_CPOL)	|
							((SPI1_ASSEL<< BITP_SPI_CTL_ASSEL)& BITM_SPI_CTL_ASSEL)	|
							((SPI1_SELST<< BITP_SPI_CTL_SELST)& BITM_SPI_CTL_SELST)	|
							((SPI1_EMISO<< BITP_SPI_CTL_EMISO)& BITM_SPI_CTL_EMISO)	|
							((SPI1_SIZE << BITP_SPI_CTL_SIZE) & BITM_SPI_CTL_SIZE)	|
							((SPI1_LSBF << BITP_SPI_CTL_LSBF) & BITM_SPI_CTL_LSBF)	|
							((SPI1_FCEN << BITP_SPI_CTL_FCEN) & BITM_SPI_CTL_FCEN)	|
							((SPI1_FCCH << BITP_SPI_CTL_FCCH) & BITM_SPI_CTL_FCCH)	|
							((SPI1_FCPL << BITP_SPI_CTL_FCPL) & BITM_SPI_CTL_FCPL)	|
							((SPI1_FCWM << BITP_SPI_CTL_FCWM) & BITM_SPI_CTL_FCWM)	|
							((SPI1_FMODE<< BITP_SPI_CTL_FMODE)& BITM_SPI_CTL_FMODE)	|
							((SPI1_MIOM << BITP_SPI_CTL_MIOM) & BITM_SPI_CTL_MIOM)	|
							((SPI1_SOSI << BITP_SPI_CTL_SOSI) & BITM_SPI_CTL_SOSI)	);


		*pREG_SPI1_TXCTL = (((SPI1_TTI	<< BITP_SPI_TXCTL_TTI)	& BITM_SPI_TXCTL_TTI)	|
							((SPI1_TWCEN<< BITP_SPI_TXCTL_TWCEN)& BITM_SPI_TXCTL_TWCEN)	|
							((SPI1_TDU	<< BITP_SPI_TXCTL_TDU)	& BITM_SPI_TXCTL_TDU)	|
							((SPI1_TDR	<< BITP_SPI_TXCTL_TDR)	& BITM_SPI_TXCTL_TDR)	|
							((SPI1_TRWM	<< BITP_SPI_TXCTL_TRWM)	& BITM_SPI_TXCTL_TRWM)	|
							((SPI1_TUWM	<< BITP_SPI_TXCTL_TUWM)	& BITM_SPI_TXCTL_TUWM)	);


		*pREG_SPI1_RXCTL = (((SPI1_RTI	<< BITP_SPI_RXCTL_RTI)	& BITM_SPI_RXCTL_RTI)	|
							((SPI1_RWCEN<< BITP_SPI_RXCTL_RWCEN)& BITM_SPI_RXCTL_RWCEN) |
							((SPI1_RDO	<< BITP_SPI_RXCTL_RDO)	& BITM_SPI_RXCTL_RDO)	|
							((SPI1_RDR	<< BITP_SPI_RXCTL_RDR)	& BITM_SPI_RXCTL_RDR)	|
							((SPI1_RRWM	<< BITP_SPI_RXCTL_RRWM)	& BITM_SPI_RXCTL_RRWM)	|
							((SPI1_RUWM << BITP_SPI_RXCTL_RUWM)	& BITM_SPI_RXCTL_RUWM)	);

		*pREG_SPI1_TWC	= 	0;//BUFF_SIZE1;
		*pREG_SPI1_TWCR	= 	0;//;BUFF_SIZE1;
		*pREG_SPI1_RWC	= 	0;//BUFF_SIZE2;
		*pREG_SPI1_RWCR	= 	0;//BUFF_SIZE2;

		*pREG_SPI1_SLVSEL = (((SPI1_SSE1 << BITP_SPI_SLVSEL_SSE1) & BITM_SPI_SLVSEL_SSE1));

		*pREG_SPI1_SLVSEL |= ENUM_SPI_SLVSEL_SSEL1_HI ;

		*pREG_SPI1_IMSK_SET = BITM_SPI_IMSK_MF ;
			if (SPI1_REN)
				*pREG_SPI1_IMSK_SET |= (BITM_SPI_IMSK_RUWM | BITM_SPI_IMSK_ROR | BITM_SPI_IMSK_RS | BITM_SPI_IMSK_RF );
			if (SPI1_TEN)
				*pREG_SPI1_IMSK_SET |= (BITM_SPI_IMSK_TUWM | BITM_SPI_IMSK_TUR | BITM_SPI_IMSK_TC | BITM_SPI_IMSK_TS | BITM_SPI_IMSK_TF );
	}

	else
	{
		*pREG_SPI0_CLK	= 	((SPI0_BAUD << BITP_SPI_CLK_BAUD) & BITM_SPI_CLK_BAUD);

		*pREG_SPI0_DLY	= (	((SPI0_STOP << BITP_SPI_DLY_STOP) & BITM_SPI_DLY_STOP)	|
							((SPI0_LEADx<< BITP_SPI_DLY_LEADX)& BITM_SPI_DLY_LEADX)	|
							((SPI0_LAGx << BITP_SPI_DLY_LAGX) & BITM_SPI_DLY_LAGX)	);

		*pREG_SPI0_CTL 	= (	((SPI0_MSTR << BITP_SPI_CTL_MSTR) & BITM_SPI_CTL_MSTR)	|
							((SPI0_PSSE << BITP_SPI_CTL_PSSE) & BITM_SPI_CTL_PSSE)	|
							((SPI0_ODM	<< BITP_SPI_CTL_ODM)  & BITM_SPI_CTL_ODM )	|
							((SPI0_CPHA << BITP_SPI_CTL_CPHA) & BITM_SPI_CTL_CPHA)	|
							((SPI0_CPOL << BITP_SPI_CTL_CPOL) & BITM_SPI_CTL_CPOL)	|
							((SPI0_ASSEL<< BITP_SPI_CTL_ASSEL)& BITM_SPI_CTL_ASSEL)	|
							((SPI0_SELST<< BITP_SPI_CTL_SELST)& BITM_SPI_CTL_SELST)	|
							((SPI0_EMISO<< BITP_SPI_CTL_EMISO)& BITM_SPI_CTL_EMISO)	|
							((SPI0_SIZE << BITP_SPI_CTL_SIZE) & BITM_SPI_CTL_SIZE)	|
							((SPI0_LSBF << BITP_SPI_CTL_LSBF) & BITM_SPI_CTL_LSBF)	|
							((SPI0_FCEN << BITP_SPI_CTL_FCEN) & BITM_SPI_CTL_FCEN)	|
							((SPI0_FCCH << BITP_SPI_CTL_FCCH) & BITM_SPI_CTL_FCCH)	|
							((SPI0_FCPL << BITP_SPI_CTL_FCPL) & BITM_SPI_CTL_FCPL)	|
							((SPI0_FCWM << BITP_SPI_CTL_FCWM) & BITM_SPI_CTL_FCWM)	|
							((SPI0_FMODE<< BITP_SPI_CTL_FMODE)& BITM_SPI_CTL_FMODE)	|
							((SPI0_MIOM << BITP_SPI_CTL_MIOM) & BITM_SPI_CTL_MIOM)	|
							((SPI0_SOSI << BITP_SPI_CTL_SOSI) & BITM_SPI_CTL_SOSI)	);


		*pREG_SPI0_TXCTL = (((SPI0_TTI	<< BITP_SPI_TXCTL_TTI)	& BITM_SPI_TXCTL_TTI)	|
							((SPI0_TWCEN<< BITP_SPI_TXCTL_TWCEN)& BITM_SPI_TXCTL_TWCEN)	|
							((SPI0_TDU	<< BITP_SPI_TXCTL_TDU)	& BITM_SPI_TXCTL_TDU)	|
							((SPI0_TDR	<< BITP_SPI_TXCTL_TDR)	& BITM_SPI_TXCTL_TDR)	|
							((SPI0_TRWM	<< BITP_SPI_TXCTL_TRWM)	& BITM_SPI_TXCTL_TRWM)	|
							((SPI0_TUWM	<< BITP_SPI_TXCTL_TUWM)	& BITM_SPI_TXCTL_TUWM)	);


		*pREG_SPI0_RXCTL = (((SPI0_RTI	<< BITP_SPI_RXCTL_RTI)	& BITM_SPI_RXCTL_RTI)	|
							((SPI0_RWCEN<< BITP_SPI_RXCTL_RWCEN)& BITM_SPI_RXCTL_RWCEN) |
							((SPI0_RDO	<< BITP_SPI_RXCTL_RDO)	& BITM_SPI_RXCTL_RDO)	|
							((SPI0_RDR	<< BITP_SPI_RXCTL_RDR)	& BITM_SPI_RXCTL_RDR)	|
							((SPI0_RRWM	<< BITP_SPI_RXCTL_RRWM)	& BITM_SPI_RXCTL_RRWM)	|
							((SPI0_RUWM << BITP_SPI_RXCTL_RUWM)	& BITM_SPI_RXCTL_RUWM)	);

		*pREG_SPI0_TWC	= 	0;//BUFF_SIZE1;
		*pREG_SPI0_TWCR	= 	0;//;BUFF_SIZE1;
		*pREG_SPI0_RWC	= 	0;//BUFF_SIZE2;
		*pREG_SPI0_RWCR	= 	0;//BUFF_SIZE2;

		*pREG_SPI0_SLVSEL = (((SPI0_SSE1 << BITP_SPI_SLVSEL_SSE1) & BITM_SPI_SLVSEL_SSE1));

		*pREG_SPI0_SLVSEL |= ENUM_SPI_SLVSEL_SSEL1_HI ;

		*pREG_SPI0_IMSK_SET = BITM_SPI_IMSK_MF ;
			if (SPI0_REN)
				*pREG_SPI0_IMSK_SET |= (BITM_SPI_IMSK_RUWM | BITM_SPI_IMSK_ROR | BITM_SPI_IMSK_RS | BITM_SPI_IMSK_RF );
			if (SPI0_TEN)
				*pREG_SPI0_IMSK_SET |= (BITM_SPI_IMSK_TUWM | BITM_SPI_IMSK_TUR | BITM_SPI_IMSK_TC | BITM_SPI_IMSK_TS | BITM_SPI_IMSK_TF );
	}

}

/******************************************************************************
*  Module Name        : Enable_SPI0
*  Functionality      : Enable SPI0 Module
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/
void Enable_SPI0(void)
{
	if (SPI_Device == 1)
	{
		*pREG_SPI1_RXCTL |= ((SPI1_REN << BITP_SPI_RXCTL_REN) & BITM_SPI_RXCTL_REN);
		*pREG_SPI1_TXCTL |= ((SPI1_TEN << BITP_SPI_TXCTL_TEN) & BITM_SPI_TXCTL_TEN);
		*pREG_SPI1_CTL 	 |= ((SPI1_EN  << BITP_SPI_CTL_EN) 	  & BITM_SPI_CTL_EN);
	}
	else
	{
		*pREG_SPI0_RXCTL |= ((SPI0_REN << BITP_SPI_RXCTL_REN) & BITM_SPI_RXCTL_REN);
		*pREG_SPI0_TXCTL |= ((SPI0_TEN << BITP_SPI_TXCTL_TEN) & BITM_SPI_TXCTL_TEN);
		*pREG_SPI0_CTL 	 |= ((SPI0_EN  << BITP_SPI_CTL_EN) 	  & BITM_SPI_CTL_EN);
	}
}
/******************************************************************************
*  Module Name        : Disable_SPI0
*  Functionality      : Disable SPI0 Module
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/
void Disable_SPI0(void)
{
	*pREG_SPI0_RXCTL &= ~ENUM_SPI_RXCTL_RX_EN;
	*pREG_SPI0_TXCTL &= ~ENUM_SPI_TXCTL_TX_EN;
	*pREG_SPI0_CTL 	 &= ~ENUM_SPI_CTL_EN;
	*pREG_DMA22_CFG	 &= ~ENUM_DMA_CFG_EN ;
	*pREG_DMA23_CFG	 &= ~ENUM_DMA_CFG_EN ;
}
