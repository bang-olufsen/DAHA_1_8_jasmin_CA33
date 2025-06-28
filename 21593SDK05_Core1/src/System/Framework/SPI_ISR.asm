/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you 
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	SPI_ISR.asm
*  Description      : 	SPI Protocol Information & its corresponding save & unsave register function

******************************************************************************/
#include <def21593.h>
#include <asm_sprt.h>
#include "..\src\system\Include\HostDefines.h"
#include "..\src\system\Include\Extern_SPI.h"
#include "..\src\system\Include\Platform_Defines.h"

.segment/dm Seg_Kernal_Data;
.var Tag_Location32[4];
.global Tag_Location32;

.endseg;
.IMPORT "..\src\system\Include\Def_Struct.h";
.extern struct kernel Frmwk.;
.extern Tag_Location32.;
.extern PARAMETER_1_C2.;
.extern PARAMETER_2_C2.;
.extern PARAMETER_3_C2.;
.extern PARAMETER_4_C2.;
.extern RXSPI.;
.extern TXSPI.;
.extern SPI_Device.;

#define DAHA_IRQ_FLAG1_PA13			0x2000		// ("FLAG1" ADI_GPIO_PORT_A ADI_GPIO_PIN_13)

/******************************************************************************
*  Module Name        : SPIReceive
*  Functionality      : SPI receive ISR Routine
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/

.section/sw Seg_SPI_ISR_Code;
.global SPIReceive.;
.type SPIReceive., STT_FUNC;
SPIReceive.:

	dm(Frmwk.->Misc->Protect->prolbufsave_spi+(8*4)) = MODE1;

	bit clr mode1 (  BITM_REGF_MODE1_BR0
                     | BITM_REGF_MODE1_BR8
                     | BITM_REGF_MODE1_PEYEN
                     | BITM_REGF_MODE1_BDCST1
                     | BITM_REGF_MODE1_BDCST9);
	
	bit set mode1  BITM_REGF_MODE1_CBUFEN;
                      
	nop;nop;
		
	call save_lbrm_reg_spi;

	r0 = dm(Frmwk.->Spi->serialflash_flag);
	r0 = pass r0;
	if ne jump serialflashAddrRoutine;
	r0 = dm(Frmwk.->Spi->DataRead);
	r0 = pass r0;
	if eq jump NormalRoutine;	
	
	jump DirectReadRoutine;

NormalRoutine:		
  
 	r0 = dm(Frmwk.->Spi->SPIDummyReadFlg);
 	r0 = pass r0;
 	if eq jump SkipDummySPIRead;

 	r0 = dm(RXSPI.);
 	nop;
 
	r0 = 0;
	dm(Frmwk.->Spi->SPIDummyReadFlg) = r0;

	jump ExitSPIReceiveInterrupt;
    
SkipDummySPIRead:

	r3 = dm(Frmwk.->Spi->download_status);
	r3 = pass r3;
	if ne jump ReadStatusInfo;
	
	r3 = dm(Frmwk.->Spi->download_flag);
	r3 = pass r3;
	if eq jump Check_DirWrite;	
	
	jump ReadHeader;
	
Check_DirWrite:	
	
	r3 = dm(Frmwk.->Spi->DirectWrite_flag);
	r3 = pass r3;
	if eq jump Check_DirRead;	
	
	jump ReadHeader;
	
Check_DirRead:	
		
	r3 = dm(Frmwk.->Spi->DirectRead_flag);
	r3 = pass r3;
	if eq jump ReadStatusInfo;
	
	jump ReadHeader;

.global ReadStatusInfo;		
ReadStatusInfo:	

// Read data from SPI receiver buffer 	r3=dm(RXSPI);
    r3 = dm(RXSPI.);
  	r0 = fext r3 by 0:16;		// Read the Data Part	
  	r1 = fext r3 by 16:6;		// Read the Address Part

	b3 = dm(Frmwk.->Spi->SPIReceiveTempBuf);
	i3 = dm(Frmwk.->Spi->SPIReceiveTempBufPtr);		// store all bytes for debugging
	l3 = dm(Frmwk.->Spi->SPIReceivebufsize);  
	dm(i3,1) = r3;		     
	dm(Frmwk.->Spi->SPIReceiveTempBufPtr) = i3; 				

  	b3 = Frmwk.->Spi->COMMAND_BYTE;
  	l3 = COMMAND_TABLESIZE;
	i3 = b3;

  	btst r3 by 29;
  	if sz jump UpdateStatusInfo; 
  	
  	r2 = m5;
  	m3 = r1;

  	dm(m3,i3) = r0;	 	 	 // Write Data Part  
  
	r1 = pass r1;
 	if ne jump ExitSPIReceiveInterrupt;
  
	r1 = 0xff;
	r0 = r0 and r1;			// Contains Command Value
	
	r1 = 0x1C;
	comp(r0,r1);
	if ne jump Not_Download;
	
	r0 = 0;
	dm(Frmwk.->Spi->COMMAND_BYTE) = r0;
	dm(Frmwk.->Spi->download_flag) = m6;
	r0 = 3;
	dm(Frmwk.->Spi->header_count) = r0;
	r0 = TAGCOUNTADDR;
	dm(Frmwk.->Spi->header_address) = r0;
	r0 = 0;
	dm(Frmwk.->Spi->DataWrite) = r0;
	
	jump Not_serialflashCode;
	
Not_Download:					

	r1 = 0x1D;
	comp(r0,r1);
	if ne jump Not_DirectWrite;
	
	r0 = 0;
	dm(Frmwk.->Spi->COMMAND_BYTE) = r0;
	
	dm(Frmwk.->Spi->DirectWrite_flag) = m6;
	r0 = 3;
	dm(Frmwk.->Spi->header_count) = r0;
	r0 = TAGCOUNTADDR;
	dm(Frmwk.->Spi->header_address) = r0;
	r0 = 0;
	dm(Frmwk.->Spi->DataWrite) = r0;
	
	jump Not_serialflashCode;
	
Not_DirectWrite:	

Check_DirectRead:

	r1 = 0x1E;
	comp(r0,r1);
	if ne jump Not_DirectRead;
	
	r0 = 0;
	dm(Frmwk.->Spi->COMMAND_BYTE) = r0;
	
	dm(Frmwk.->Spi->DirectRead_flag) = m6;
	r0 = 3;
	dm(Frmwk.->Spi->header_count) = r0;
	r0 = TAGCOUNTADDR;
	dm(Frmwk.->Spi->header_address) = r0;
	r0 = 0;
	dm(Frmwk.->Spi->DataRead) = r0;
	
	jump Not_serialflashCode;

Not_DirectRead:	
	r1 = 0x17;
	comp(r0,r1);
	if ne jump Not_serialflashCode;
	
	r0 = 0;
	dm(Frmwk.->Spi->COMMAND_BYTE) = r0;
	
	dm(Frmwk.->Spi->serialflash_flag) = m6;
	r0 = 1;
	dm(Frmwk.->Spi->header_count) = r0;
	
Not_serialflashCode:	

	r0 = dm(Frmwk.->Spi->INTR_DESC_LOCN);
	r1 = 0x1;
	r0 = r0 or fdep r1 by 1:1;		
	dm(Frmwk.->Spi->INTR_DESC_LOCN )= r0;
	jump ExitSPIReceiveInterrupt;

UpdateStatusInfo:

   	m3 = r1;
	r0 = dm(m3,i3);					// Transmit Status Data Part
	
	r3 = 0x3F;
	comp(r1,r3);
	if ne jump No_DummyRead;
	
cmd_complete:
	r1 = 0x0004;
	r1 = r0 and r1;
    if ne jump CMD_PROCESS_COMPLETE;

	r1 = SIGNATURE_ADI_BUSY;
	r1 = r0 and r1;
	dm(Frmwk.->Spi->INTR_DESC_LOCN) = r1;

	jump NOT_INTR;

CMD_PROCESS_COMPLETE:

	r1 = dm(Frmwk.->Spi->INTR_DESC_LOCN);
	r3 = SIGNATURE_ADI_BITS;
	r1 = r1 and r3;
	dm(Frmwk.->Spi->INTR_DESC_LOCN)=r1;

NOT_INTR:
		
	dm(TXSPI.) = r0;

	r0 = 1;	
	dm(Frmwk.->Spi->SPIDummyReadFlg) = r0;

	r0 = 0;
	dm(Frmwk.->Spi->MicroWriteFlg) = r0;
	
	r0 = 0;
	dm(Frmwk.->Spi->download_status) = r0;
	
	call FLAG_TOGGLE_ROUTINE_LOW;
	
ReadStatusInfo.END:	
	
.global ExitSPIReceiveInterrupt;	
ExitSPIReceiveInterrupt: 

	call unsave_lbrm_reg_spi;
		
	MODE1 = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(8*4));	
	
	nop;nop;

ExitSPIReceiveInterrupt.END:
	
        i12 = dm(m7,i6);
		jump (m14,i12) (db); rframe; nop;
		
.SPIReceive..end:	

No_DummyRead:
	
	dm(TXSPI.) = r0;
	r0 = 0;	
	dm(Frmwk.->Spi->SPIDummyReadFlg) = r0;
	
	r0 = 0;
	dm(Frmwk.->Spi->MicroWriteFlg) = r0;
	
	r0 = 0;
	dm(Frmwk.->Spi->download_status) = r0;
	
	jump ExitSPIReceiveInterrupt;	
	
/******************************************************************************
*  Module Name        : delay_asm
*  Functionality      : wait loop for the specified count
*  Input Parameters	  : r4 = delay count
*  Output Parameters  : None
******************************************************************************/
.global delay_asm;
delay_asm:

	DelayLoop:
			nop;
			nop;
			nop;
			nop;
			r4 = r4-1;
			if ne jump DelayLoop;
	        rts ;			

delay_asm.END:
/******************************************************************************
 *  Module Name        : FlagsConfigure
 *  Functionality      : Enables the Flag0
 *  Input Parameters   : None
 *  Output Parameters  : None
 *****************************************************************************/
.global FlagsConfigure.;
.type FlagsConfigure., STT_FUNC;
FlagsConfigure.:
   
     r4 = dm(SPI_Device.);
	 r4 = pass r4;
	 if eq jump SPI0_Device1;
	 bit set FLAGS BITM_REGF_FLAGS_FLG2O; 
	 jump Flag_end1;
	  
	SPI0_Device1:
	 bit set FLAGS BITM_REGF_FLAGS_FLG0O; 

Flag_end1:
	call FLAG_TOGGLE_ROUTINE_LOW;	    
	nop;nop;nop;nop;
	i12 = dm(m7,i6);
	jump (m14,i12) (db); rframe; nop;		
	
.FlagsConfigure..end:	
/******************************************************************************
*  Module Name        : FLAG_TOGGLE_ROUTINE
*  Functionality      : Flag0 set to high. This is connected to host
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/
.global FLAG_TOGGLE_ROUTINE;
FLAG_TOGGLE_ROUTINE:
	nop;nop;
/*	
	 r4 = dm(SPI_Device.);
	 r4 = pass r4;
	 if eq jump SPI0_Device;
	 bit set FLAGS BITM_REGF_FLAGS_FLG2;
	 jump Flag_end;
	  
	SPI0_Device:
	 bit set FLAGS BITM_REGF_FLAGS_FLG0;

Flag_end:	  
*/
//#ifdef BEO_SPI_SLAVE_DAHA						// Note: Relevant for B&O code
	 r4 = DAHA_IRQ_FLAG1_PA13;
	 dm (REG_PORTA_DATA_SET) = r4; //CLR
//#endif
#ifdef MELODY9	 
	 r4 = 0x80;
	 dm (REG_PORTB_DATA_SET) = r4; //SET
#endif
	nop;nop;nop;nop;
	r4 = 0x4;
	call delay_asm;
	nop;nop;
	dm(Frmwk.->Spi->FlagToggle) = m5;
	rts;
FLAG_TOGGLE_ROUTINE.END:		

/******************************************************************************
*  Module Name        : FLAG_TOGGLE_ROUTINE_LOW
*  Functionality      : Flag0 set to low. This is connected to host
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/
.global FLAG_TOGGLE_ROUTINE_LOW;
FLAG_TOGGLE_ROUTINE_LOW:
	nop;nop;
/*	
	r4 = dm(SPI_Device.);
	r4 = pass r4;
	if eq jump SPI0_Device_Low;
	bit clr FLAGS BITM_REGF_FLAGS_FLG2;
	jump Flag_Low_end;
	  
	SPI0_Device_Low:
	bit clr FLAGS BITM_REGF_FLAGS_FLG0;

Flag_Low_end:	
*/  
//#ifdef BEO_SPI_SLAVE_DAHA						// Note: Relevant for B&O code
	 r4 = DAHA_IRQ_FLAG1_PA13;
	 dm (REG_PORTA_DATA_CLR) = r4; //CLR
//#endif
#ifdef MELODY9    
	r4 = 0x80;
	dm (REG_PORTB_DATA_CLR) = r4; // CLR 
#endif    
	nop;nop;nop;nop;
	r4 = 0x1;
	call delay_asm;
	nop;nop;
	
	dm(Frmwk.->Spi->FlagToggle) = m6;	
	rts;
	
FLAG_TOGGLE_ROUTINE_LOW.END:
/******************************************************************************
*  Module Name        : Flag_Toggle
*  Functionality      : Flag toggle routine wrapper
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/
.global _Flag_Toggle;
_Flag_Toggle:
	entry;	
	call FLAG_TOGGLE_ROUTINE;	
	exit;
_Flag_Toggle.END:	

/******************************************************************************
*  Module Name        : save_lbrm_reg_spi
*  Functionality      : Saving of registers which is used in SPI ISR
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/	
.global save_lbrm_reg_spi;
save_lbrm_reg_spi:

	dm(Frmwk.->Misc->Protect->prolbufsave_spi) = b3;		
	dm(Frmwk.->Misc->Protect->prolbufsave_spi+(1*4)) = i3;
    dm(Frmwk.->Misc->Protect->prolbufsave_spi+(2*4)) = l3; 
	dm(Frmwk.->Misc->Protect->prolbufsave_spi+(3*4)) = m3;		
	dm(Frmwk.->Misc->Protect->prolbufsave_spi+(4*4)) = r0;	
	dm(Frmwk.->Misc->Protect->prolbufsave_spi+(5*4)) = r3; 
	dm(Frmwk.->Misc->Protect->prolbufsave_spi+(6*4)) = r4;	
	dm(Frmwk.->Misc->Protect->prolbufsave_spi+(7*4)) = r1;	
	dm(Frmwk.->Misc->Protect->prolbufsave_spi+(11*4)) = r2;	
	dm(Frmwk.->Misc->Protect->prolbufsave_spi+(9*4)) = ASTAT;
	dm(Frmwk.->Misc->Protect->prolbufsave_spi+(10*4)) = LCNTR;
	dm(Frmwk.->Misc->Protect->prolbufsave_spi+(12*4)) = b0;
	dm(Frmwk.->Misc->Protect->prolbufsave_spi+(13*4)) = i0;
	dm(Frmwk.->Misc->Protect->prolbufsave_spi+(14*4)) = l0;
	
	rts;
save_lbrm_reg_spi.end:	
/******************************************************************************
*  Module Name        : unsave_lbrm_reg_spi
*  Functionality      : Unsaving of registers which is used in SPI ISR
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/	
.global unsave_lbrm_reg_spi;	
unsave_lbrm_reg_spi:

	ASTAT = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(9*4));
	r0 = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(10*4));
	LCNTR = r0;

	b3 = dm(Frmwk.->Misc->Protect->prolbufsave_spi);		
	i3 = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(1*4));
    l3 = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(2*4)); 
	m3 = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(3*4));	
	r0 = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(4*4));	
	r3 = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(5*4)); 
	r4 = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(6*4));	
	r1 = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(7*4));	
	r2 = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(11*4));
	b0 = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(12*4));
	i0 = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(13*4));
	l0 = dm(Frmwk.->Misc->Protect->prolbufsave_spi+(14*4));		
	rts;
unsave_lbrm_reg_spi.end:	

.ENDSEG;
