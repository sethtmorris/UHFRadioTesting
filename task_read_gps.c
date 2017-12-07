#include "salvo.h"
#include "csk_uart.h"
#include "main.h"
#include <__cross_studio_io.h>
#include "task_read_gps.h"

void task_read_gps (void) {
  	
  while(1) {
    OS_WaitBinSem(BINSEM_USB_COMPLETE, OSNO_TIMEOUT);
    finished = 0;
    memset(strGPSreadout, '\0', readout_size);   //set all entries in strGPSreadout to null

    csk_uart0_open(CSK_UART_9600_N81_ACLK);      //read from rx1 for 1.5 seconds. put chars from rx1 into ring buffer
    OS_Delay(1500/TIMER_RESOLUTION_MS);          //NOTE: opening a uart port via csk resets the ring buffer pointer
    csk_uart0_close();                           //close uart1 to prevent rx1 from interrupting the task

    c = csk_uart0_getchar();
    while (finished == 0) {
      if (usci_a0_uart_rx_count() == 0) {sprintf(strGPSreadout, "GPS output incomplete or not found"); break;}
      if (c == '$') {
        
        strGPSreadout[0] = c;
        for (i=1; i<header_size; i++) {
          strGPSreadout[i] = csk_uart0_getchar();
        } /* end for i < header_size, create header */
        
        if (arraycheck(strGPSreadout, str_gps_header, header_size) == 1) {
          
          lineCount = 1;
          for(i = header_size; i < readout_size; i++) {        // copy the buffer until told otherwise            
            c = csk_uart0_getchar();
            if (c == '$') {lineCount++;}                       // count the number of lines (there are 11 in a grouping)          
            if (lineCount == 12) {break;}                      // we have copied an entire grouping, so null the rest of the char array and break the for loop
            strGPSreadout[i] = c;                              //debug_printf("strGPSreadout is %d characters\n", i); 
          } /* end for i < readout_size, create readout string */

          finished = 1;                                        // we are done copying the buffer
        } 
      }
    
      c = csk_uart0_getchar();
    }

    OSSignalBinSem(BINSEM_GPS_READY);
  } /* end while(1) loop (which never actually ends) */
	
} /* end task_read_gps */

int arraycheck(char array[], char array2[], int arraysize) {						//function to test if two char arrays are equal   
    int j;
    for(j = 0; j < arraysize; j++)      
    {         
        if(array[j] != array2[j])
            return 0;
    }
	
    return 1;
}
