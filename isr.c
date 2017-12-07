/******************************************************************************
(C) Copyright Pumpkin, Inc. All Rights Reserved.

This file may be distributed under the terms of the License
Agreement provided with this software.

THIS FILE IS PROVIDED AS IS WITH NO WARRANTY OF ANY KIND,
INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE.

$Source: C:\\RCS\\D\\Pumpkin\\CubeSatKit\\Example\\MSP430\\MSP430x1xx\\CubeSatKit_Dev_Board\\Test\\Test1\\RA430-v2\\isr.c,v $
$Author: aek $
$Revision: 3.0 $
$Date: 2009-11-02 02:45:08-08 $

******************************************************************************/
#include "main.h"
#include "csk_uart.h"
#include "salvo.h"
#include <__cross_studio_io.h>

#define LOOP_HERE()            do { ; } while (1)


/******************************************************************************
****                                                                       ****
**                                                                           **
isr_timerA0()                  code edited by Aaron Blaufox for E_Summer2017

**                                                                           **
****                                                                       ****
******************************************************************************/
void isr_timerA0(void) __interrupt[TIMERA0_VECTOR] {
  //CCR0 += SYSTEM_TIMER_RELOAD; ----> for continuous mode (original code)
  tick++;                  //not originally in code
  //debug_printf("isr_A0\n");
  OSTimer();
} /* isr_timerA0() */                     


/******************************************************************************
****                                                                       ****
**                                                                           **
isr_tx0()

**                                                                           **
****                                                                       ****
******************************************************************************/
void isr_tx0(void) __interrupt[USCIAB0TX_VECTOR] {

  csk_uart0_outchar();
  
} /* isr_tx0() */


/******************************************************************************
****                                                                       ****
**                                                                           **
isr_tx1()

**                                                                           **
****                                                                       ****
******************************************************************************/
void isr_tx1(void) __interrupt[USCIAB1TX_VECTOR] {

  csk_uart1_outchar();
  
} /* isr_tx1() */


/******************************************************************************
****                                                                       ****
**                                                                           **
isr_rx0()

**                                                                           **
****                                                                       ****
******************************************************************************/
void isr_rx0(void) __interrupt[USCIAB0RX_VECTOR] {

  //  Put it into the ring buffer ...
  csk_uart0_inchar(UCA0RXBUF);
  //debug_printf("rx0\n");

  //  Tell OS we've received a new char ...
  //OSSignalSem(BINSEM_RX0_RECEIVED);  
} /* isr_rx0() */


/******************************************************************************
****                                                                       ****
**                                                                           **
isr_rx1

in place, but not active.

**                                                                           **
****                                                                       ****
******************************************************************************/
void isr_rx1(void) __interrupt[USCIAB1RX_VECTOR] {

    csk_uart1_inchar(UCA1RXBUF);

} /* isr_rx1() */


/******************************************************************************
****                                                                       ****
**                                                                           **
Other (unused) ISRs -- trap for debugging purposes.

**                                                                           **
****                                                                       ****
******************************************************************************/
void isr_p2(void) __interrupt[PORT2_VECTOR] {  

  LOOP_HERE();
  
} /* isr_2() */


void isr_p1(void) __interrupt[PORT1_VECTOR] {

  LOOP_HERE();
  
} /* isr_p1() */


void isr_timera1(void) __interrupt[TIMERA1_VECTOR] {

  LOOP_HERE();
  
} /* isr_timera1() */


void isr_adc(void) __interrupt[ADC12_VECTOR] {

  LOOP_HERE();
  
} /* isr_adc() */


void isr_wdt(void) __interrupt[WDT_VECTOR] {

  LOOP_HERE();
  
} /* isr_wdt() */


void isr_cmpa(void) __interrupt[COMPARATORA_VECTOR] {

  LOOP_HERE();
  
} /* isr_cmpa() */


void isr_timerb1(void) __interrupt[TIMERB1_VECTOR] {

  LOOP_HERE();
  
} /* isr_timerb1() */


void isr_timerb0(void) __interrupt[TIMERB0_VECTOR] {

  LOOP_HERE();
  
} /* isr_timerb0() */


void isr_nmi(void) __interrupt[NMI_VECTOR] {

  LOOP_HERE();
  
} /* isr_nmi() */
