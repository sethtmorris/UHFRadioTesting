#include "main.h"
#include "salvo.h"
#include "msp430f2618.h"
#include "csk_uart.h"

void init (void) {  
  
  WDTCTL = WDTPW + WDTHOLD;             // Stop Watchdog Timer.  
  __disable_interrupt();
  
  csk_usb_close();                      // setup usb for use

  TACTL  = TASSEL1 + ID_1 + MC_1;       // SMCLK, clear TAR, up mode (MC_2 for continuous mode)
  TACCR0 = TIMERA0_RELOAD - 1;          // 100ms ticks.
  TACCTL0  = CCIE;                      // CCR0 interrupt enabled.
  
  DCOCTL = 0;                           // configure clock module - MCLK = 1 MHz
  BCSCTL1 = CALBC1_1MHZ;
  DCOCTL = CALDCO_1MHZ;
                                        // Init USARTs to 9600,N,8,1. UARTs won't transmit until interrupts are enabled ...
  //csk_uart0_open(CSK_UART_9600_N81_ACLK); //moved to task_read_gps
  //csk_uart1_open(CSK_UART_9600_N81_ACLK);
  
}