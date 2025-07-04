/***************************************************************************
*
Copyright(c) 2020 Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software you
agree to the terms of the associated Analog Devices License Agreement.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Customerasm.asm
*  Description      :
******************************************************************************/
#include "def21593.h"
#include "asm_sprt.h"
.IMPORT "../src/System/Include/Def_Struct.h";
#include "../src/System/Include/Commn.h"
#include "../src/System/Include/Extern_SPI.h"
#ifdef CUSTOMER_PP
.extern Predac_buffer_Cust_PP.;
.extern struct kernel Frmwk.;
.extern Predac_buffer_Int.;
.extern CustomerPP_Buffer.;

.section/sw  Seg_Customer_Code;
/******************************************************************************
*  Module Name        : FloatToFixConversion
*  Functionality      : This Routine Convert the Floating Format datas 
*					   into Fixed Format datas 
*  Input Parameters   : None
*  Output Parameters  : None
******************************************************************************/
.global FloatToFixConversion.;
.type FloatToFixConversion., STT_FUNC;
FloatToFixConversion.:						
    call saveforCEnv;
    
    	bit clr MODE1 0x10000;		//Clr Rnd32
	nop;nop;

	bit set MODE1 0x2000;		//Set ALUSAT
	nop;nop;
	
	/********Float to fix conversion for CustomerPP_Buffer *******/
	l1 = PP_BUFF_MAX_SIZE; 
	b1 = CustomerPP_Buffer.;
	i1 = CustomerPP_Buffer.;
	
	r0=dm(Frmwk.->ADI_DecoderError); 
	
	r0=pass r0;
	
	if ne jump Fill_Zero1;
	
	r1=31;
	
	r0 = PP_BUFF_MAX_SIZE;
	 
	lcntr = r0 , do Cpy2PreDacBufinFIX until lce;
	 		f0 = dm(i1,m5);  
	        r0 = fix f0 by r1;
		   
    Cpy2PreDacBufinFIX:dm(i1,m6) = r0; 
    
    jump end_copy1;
    Fill_Zero1:
    r1 = 0;
    r0 = PP_BUFF_MAX_SIZE;
	lcntr = r0 , do Cpy2PreDacBufinFIX2 until lce;
    Cpy2PreDacBufinFIX2:dm(i1,m6) = r1; 
    end_copy1:
    
    	bit clr MODE1 0x2000;	//Clr ALUSAT
	nop;nop;

	bit set MODE1 0x10000;		//Set Rnd32
	nop;nop;
    
    	call unsaveforCEnv;
	i12=dm(m7,i6);
	jump (m14,i12) (db); rframe; nop;                      
		
FloatToFixConversion..END:

/******************************************************************************
*  Module Name        : FixToFloatConversion
*  Functionality      : This Routine Process Convert Fixed Format datas 
                      into Floating Format datas
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/
.global FixToFloatConversion.;	
.type FixToFloatConversion., STT_FUNC;			
FixToFloatConversion.:
	
	/***********Fix to float conversion for CustomerPP_Buffer *******/
	call saveforCEnv;
	
	l1 = PP_BUFF_MAX_SIZE ; b1 =CustomerPP_Buffer.;
	i1 = CustomerPP_Buffer.;
	
	r1=-31;	
	r0= PP_BUFF_MAX_SIZE;
	
	lcntr = r0 , do Cpy2PreDacinFloat until lce;
 		r0 = dm(i1,m5);  
	    f0 = float r0 by r1;
    Cpy2PreDacinFloat:dm(i1,m6) = f0;       
	
	call unsaveforCEnv;
	i12=dm(m7,i6);
	jump (m14,i12) (db); rframe; nop;
FixToFloatConversion..END:

/******************************************************************************
*  Module Name        : PreDac_Int_To_Cust_PP_Buffer
*  Functionality      : This Routine Process is to copy Predac_buffer_Int 
                	   to CustomerPP_buffer	
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/
.global PreDac_Int_To_Cust_PP_Buffer.;	
.type PreDac_Int_To_Cust_PP_Buffer., STT_FUNC;			
PreDac_Int_To_Cust_PP_Buffer.:
     call saveforCEnv;
     
     i1 = CustomerPP_Buffer.;   
     l1 = 0;
     i0 = Predac_buffer_Int.;
     l0 = 0;
     
     r3 = dm(Frmwk.->DTSVX->DTS_VirtualX_Enable);
     r0 = dm(Frmwk.->DTSX->NeuralX_enable);
     r2 = dm(Frmwk.->StreamType_DTSX);
     r0 = r0 or r3;
     r0 = r0 or r2;
     r0 = pass r0;
     if ne jump NeuralX_Enable_case1;
       m2 = 2;
       jump NeuralX_Disable_case1;
 NeuralX_Enable_case1:
	    m2 = 18;
 NeuralX_Disable_case1:	
 
     r0 = NO_OF_SAMPLE_PROCESSING; 
     
     BIT SET MODE1 BITM_REGF_MODE1_PEYEN;
     nop;nop;nop;nop;nop;nop;
     
     lcntr = r0 , do Cpy2Cust_PP until lce;
        r2 = dm(i0,2);  //1&2 channels
        dm(i1,2) = r2;
        r2 = dm(i0,2);  //3&4 channels
        dm(i1,2) = r2;
        r2 = dm(i0,2);  //5&6 channels
        dm(i1,2) = r2;
        r2 = dm(i0,2);  //7&8 channels
        dm(i1,2) = r2;
        r2 = dm(i0,2);  //9&10 channels
        dm(i1,2) = r2;
        r2 = dm(i0,2);  //11&12 channels
        dm(i1,2) = r2;   
        r2 = dm(i0,2);  //13&14 channels
        dm(i1,2) = r2;
        r2 = dm(i0,m2);  //15&16 channels
      Cpy2Cust_PP: dm(i1,2) = r2; 
     
     BIT clr MODE1 BITM_REGF_MODE1_PEYEN;
     nop;nop;nop;nop;nop;nop;
     
       call unsaveforCEnv;
        
  	   i12=dm(m7,i6);
	   jump (m14,i12) (db); rframe; nop;
PreDac_Int_To_Cust_PP_Buffer..END:

/******************************************************************************
*  Module Name        : Cust_PP_To_PreDac_Int_Buffer
*  Functionality      : This Routine Process is to copy CustomerPP_buffer 
                	   to Predac_buffer_Int	
*  Input Parameters	  : None
*  Output Parameters  : None
******************************************************************************/
.global Cust_PP_To_PreDac_Int_Buffer.;	
.type Cust_PP_To_PreDac_Int_Buffer., STT_FUNC;			
Cust_PP_To_PreDac_Int_Buffer.:
     call saveforCEnv;
     
     i0 = CustomerPP_Buffer.;
     l0 = 0;   
     i1 = Predac_buffer_Int.;
     l1 = 0; 
     
     r0=dm(Frmwk.->ADI_DecoderError); 
     r0=pass r0;
     if ne jump Fill_Zero;
     
     /********** This function is to make memset for predac buffer ************/
    bit SET mode1 BITM_REGF_MODE1_PEYEN;
    nop;
   	nop;
	 r4 = 0;
	r2 = NO_OF_SAMPLE_PROCESSING*PREDAC_INT_NUMCHAN;
	r2 = lshift r2 by -1;	
	lcntr = r2, do mem_zero_Int_Predac until lce;
	mem_zero_Int_Predac: dm(i1,2) = r4;
	bit clr mode1 BITM_REGF_MODE1_PEYEN;
    nop;
    nop;	 
     
	/****************************** memset end ******************************/	
     i1 = Predac_buffer_Int.;
     r0 = NO_OF_SAMPLE_PROCESSING;
     //r0 = lshift r0 by -1;
     r1 = PREDAC_INT_NUMCHAN - CUSTOMER_PP_CHANNELS;
     m2 = r1;
     
     BIT SET MODE1 BITM_REGF_MODE1_PEYEN;
     nop;nop;nop;nop;nop;nop;
     
     lcntr = r0 , do Cpy2Predac_int until lce;
        r2 = dm(i0,2);  //1&2 channels
        dm(i1,2) = r2;
        r2 = dm(i0,2);  //3&4 channels
        dm(i1,2) = r2;
        r2 = dm(i0,2);  //5&6 channels
        dm(i1,2) = r2;
        r2 = dm(i0,2);  //7&8 channels
        dm(i1,2) = r2;
        r2 = dm(i0,2);  //9&10 channels
        dm(i1,2) = r2;
        r2 = dm(i0,2);  //11&12 channels
        dm(i1,2) = r2;
        r2 = dm(i0,2);  //13&14 channels
        dm(i1,2) = r2;
        r2 = dm(i0,2);  //15&16 channels
        dm(i1,2) = r2;       
    Cpy2Predac_int: modify(i1,m2) (nw); //skip in Predac_buffer_Int
     
     BIT clr MODE1 BITM_REGF_MODE1_PEYEN;
     nop;nop;nop;nop;nop;nop;
     
    jump end_copy;
    Fill_Zero:
    r1=0;
    r0 = NO_OF_SAMPLE_PROCESSING*PREDAC_INT_NUMCHAN;
	lcntr = r0 , do Cpy2PreDacBufinFIX1 until lce;
    Cpy2PreDacBufinFIX1:dm(i1,m6) = r1; 
    end_copy:
     
     call unsaveforCEnv;
        
  	   i12=dm(m7,i6);
	   jump (m14,i12) (db); rframe; nop;
Cust_PP_To_PreDac_Int_Buffer..END:

.endseg;

/******************************************************************************
*  Module Name        : FloatToFixConversion_INT
*  Functionality      : This Routine Convert the Floating Format datas 
*					   into Fixed Format datas in Predac_buffer_Int  
*  Input Parameters   : None
*  Output Parameters  : None
******************************************************************************/
.global FloatToFixConversion_INT.;
.type FloatToFixConversion_INT., STT_FUNC;
FloatToFixConversion_INT.:						
    call saveforCEnv;
    
    	bit set MODE1 0x2000;	//Set ALUSAT
	nop;nop;

	bit clr MODE1 0x10000;		//Clr Rnd32
	nop;nop;
        
	/********Float to fix conversion for CustomerPP_Buffer *******/
	l1 = NO_OF_SAMPLE_PROCESSING*PREDAC_INT_NUMCHAN; 
	b1 = Predac_buffer_Int.;
	i1 = Predac_buffer_Int.;
		
	r1=31;	
	r0 = NO_OF_SAMPLE_PROCESSING*PREDAC_INT_NUMCHAN;	 
	lcntr = r0 , do Cpy2PreDacBufinFIX_INT until lce;
 		f0 = dm(i1,m5);  
        r0 = fix f0 by r1;		   
    Cpy2PreDacBufinFIX_INT:dm(i1,m6) = r0;       
    
    	bit set MODE1 0x10000;		//Set Rnd32
	nop;nop;

	bit clr MODE1 0x2000;		//Clr ALUSAT
	nop;nop;     
    
    call unsaveforCEnv;
	i12=dm(m7,i6);
	jump (m14,i12) (db); rframe; nop;                      
		
FloatToFixConversion_INT..END:

#endif