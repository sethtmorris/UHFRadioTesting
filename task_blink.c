#include "salvo.h"
#include "msp430f2618.h"
#include "main.h"
#include <__cross_studio_io.h>


void task_blink (void) {;
  P1DIR = 0xFF;
  P1OUT = 0x00;

  while (1) {
    P1OUT ^= BIT0;                                            // Toggle P1OUT:BIT0
    OS_Delay(1000/TIMER_RESOLUTION_MS);                       //context switch and return after 1 second
  }
}
