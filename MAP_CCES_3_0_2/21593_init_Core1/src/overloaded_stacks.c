/*******************************************************************************

     Copyright (c) 2014-2022, Analog Devices, Inc.  All rights reserved.

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

    File name:    overloaded_stacks.c
    Purpose:      Declare minimally sized Abort, Undefined, Supervisor and FIQ
                  stacks so that everything for the preload will fit in L2.
    Notes:

*******************************************************************************/

#include <stdint.h>
#include <sys/adi_stack.h>

#if defined(__ADSPCORTEXA55__)

#define __ADI_B  (1u)
#define __ADI_kB (1024u)
#define __ADI_MB (1024u * 1024u)

#define __ADI_SYSTEM_HEAP_SIZE (4u)
#define __ADI_SYSTEM_HEAP_SIZE_UNITS __ADI_kB
#define __ADI_SYSTEM_HEAP_ALIGN (4u)

#define __ADI_EL0_STACK_SIZE (4u)
#define __ADI_EL0_STACK_SIZE_UNITS __ADI_kB
#define __ADI_EL0_STACK_ALIGN (64u)

#define __ADI_EL3_STACK_SIZE (4u)
#define __ADI_EL3_STACK_SIZE_UNITS __ADI_kB
#define __ADI_EL3_STACK_ALIGN (64u)

/* The object used for the system heap. */
uint8_t __adi_heap_object[__ADI_SYSTEM_HEAP_SIZE * __ADI_SYSTEM_HEAP_SIZE_UNITS]
             __attribute__ ((aligned (__ADI_SYSTEM_HEAP_ALIGN))) 
             __attribute__ ((section (".heap,\"aw\",%nobits //")));

/* The object used for the EL0 stack. */
uint8_t __adi_stack_el0_object[__ADI_EL0_STACK_SIZE * __ADI_EL0_STACK_SIZE_UNITS]
             __attribute__ ((aligned (__ADI_EL0_STACK_ALIGN))) 
             __attribute__ ((section (".stack_el0,\"aw\",%nobits //")));

/* The object used for the EL3 stack. */
uint8_t __adi_stack_el3_object[__ADI_EL3_STACK_SIZE * __ADI_EL3_STACK_SIZE_UNITS]
             __attribute__ ((aligned (__ADI_EL3_STACK_ALIGN))) 
             __attribute__ ((section (".stack_el3,\"aw\",%nobits //")));

#elif defined(__ADSPCORTEXA5__)

#define __ADI_STACK_ABORT_SIZE 8
uint8_t   __adi_stack_abort_object[__ADI_STACK_ABORT_SIZE]
             __attribute__ ((aligned (__ADI_STACK_ABORT_ALIGN)))
             __attribute__ ((section (".stack_abort")));

#define __ADI_STACK_UNDEF_SIZE 8
uint8_t   __adi_stack_undef_object[__ADI_STACK_UNDEF_SIZE]
             __attribute__ ((aligned (__ADI_STACK_UNDEF_ALIGN)))
             __attribute__ ((section (".stack_undef")));

#define __ADI_STACK_SUP_SIZE 8
uint8_t   __adi_stack_sup_object[__ADI_STACK_SUP_SIZE]
             __attribute__ ((aligned (__ADI_STACK_SUP_ALIGN)))
             __attribute__ ((section (".stack_sup")));

#define __ADI_STACK_FIQ_SIZE 8
uint8_t   __adi_stack_fiq_object[__ADI_STACK_FIQ_SIZE]
             __attribute__ ((aligned (__ADI_STACK_FIQ_ALIGN)))
             __attribute__ ((section (".stack_fiq")));
#endif
