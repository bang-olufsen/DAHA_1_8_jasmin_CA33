/*******************************************************************************

     Copyright (c) 2014-2017, Analog Devices, Inc.  All rights reserved.

     Redistribution and use in source and binary forms, with or without
     modification, are permitted (subject to the limitations in the
     disclaimer below) provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.

     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the
       distribution.

     * Neither the name of Analog Devices, Inc.  nor the names of its
       contributors may be used to endorse or promote products derived
       from this software without specific prior written permission.

     NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
     GRANTED BY THIS LICENSE.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
     HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
     WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
     MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
     LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
     BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
     WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
     OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
     IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



*******************************************************************************/


/*******************************************************************************

    File name:    disable_mmu.S
    Purpose:      Disable cache, MMU and branch prediction, to improve load
                  time of main application via emulator.
    Notes:

*******************************************************************************/

	.arch armv7-a
	.text
	.syntax unified
#ifdef __SOFTFP__
	.fpu softvfp
#else
	.fpu vfp
	.eabi_attribute 27, 3  /* Hardware FP */
	.eabi_attribute 28, 1  /* Hardware FP Linkage */
#endif
	.thumb
	.global disable_mmu
	.thumb_func
	.type	disable_mmu, %function
	.align 	2
disable_mmu:
	mrc p15, 0, r0, c1, c0, 0  /* Read CP15 Sys Control Reg */
	bic r0, r0, #(0x1 << 12)   /* Disable I-Cache */
	bic r0, r0, #(0x1 <<  2)   /* Disable D-Cache */
	bic r0, r0, #0x1           /* Disable MMU */
	bic r0, r0, #(0x1 << 11)   /* Disable branch prediction */
	mcr p15, 0, r0, c1, c0, 0  /* Write back to CP15 */
	/* Reset the VBAR to 0x0 */
	movs r0, #0
	mcr p15, 0, r0, c12, c0, 0
	bx lr
	.size disable_mmu, .-disable_mmu
