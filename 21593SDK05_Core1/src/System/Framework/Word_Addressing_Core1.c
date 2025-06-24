/***************************************************************************
*
*  Copyright (c) 2022 Analog Devices, Inc. All Rights Reserved.
*  This software is proprietary and confidential to Analog Devices, Inc. and its licensors.
*
*  Project          :  	21593SDK
*  Organization     :  	Jasmin Infotech Private Limited,Chennai
*  File Name        :	Word_Addressing_Core1.c
*  Description      :   To add normal-word/word-addressed variables and arrays
******************************************************************************/
#include "../Include/Commn.h"

#pragma section("seg_word_addr")
int InAutobuf[(((INAUTOBUFSIZEBY2 * 4)+INAUTOBUFSIZEBY2)/4)*4];
#pragma section("seg_word_addr")
int Spi_size[SPI_BUFFER_SIZE*4];

