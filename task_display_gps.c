#include "salvo.h"
#include "main.h"
#include "csk_uart.h"
#include "csk_usb.h"

void task_display_gps (void) {
  csk_status.usb_present = 1;                                 // For now, until USB can be detected.  

  while (1) {
    OS_WaitBinSem(BINSEM_GPS_READY, OSNO_TIMEOUT);
      debug_printf("%s",strGPSreadout);
//    if (csk_status.usb_present) {                             // Is USB connected?
//      csk_uart1_open(CSK_UART_9600_N81_ACLK);
//      csk_usb_open();                                         // Access USB.
//      data_debug_msg(strGPSreadout);
//      OS_Delay(1500/TIMER_RESOLUTION_MS);                     // Don't close the USB connection until the message is completely gone                                                                                
//      csk_usb_close();                                        // Done w/USB.
//      csk_uart1_close();
//    } /* if */  
                    
    OSSignalBinSem(BINSEM_USB_COMPLETE);    
  } /* while */

} /* task_display_time */
