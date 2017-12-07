#ifndef __main_h
#define __main_h

    /* timer stuff */
#define TIMER_RESOLUTION_MS   100  //tick rate in ms
#define TIMERA0_RELOAD        1000000/2/1000*TIMER_RESOLUTION_MS - 1//--> Clock freq/divisions/ms conversion*tick rate

    /* Symbols, etc. */
#define STR_TASK_DISPLAY_TIME     "task_display_time: " STR_1TAB
#define STR_1TAB                  "\t"
#define STR_2TABS                 "\t\t"
#define STR_CRLF                  "\r\n"
#define user_debug_msg(x)         csk_uart0_msg(x)
#define data_debug_msg(x)         csk_uart1_msg(x)
#define BINSEM_USB_COMPLETE       OSECBP(1)
#define BINSEM_GPS_READY          OSECBP(2)

    /* task_read_gps symbols */
#define header_size               6
#define readout_size              1025


    /* Target-specific symbols, etc. */
#define STR_CSK_TARGET "CubeSat Kit /MSP430 (PPM A1|A2|A3)"

    /* structs */
typedef struct {
  unsigned int usb_present:1;
  unsigned int usb_connected:1;
  unsigned int mhx_connected:1;
  unsigned int MCLKOutEnabled:2;
  unsigned int exercise_io_running:1;
} csk_status_t;

extern csk_status_t csk_status;

    /* global variables */
extern unsigned int tick;

extern char str_gps_header[];
extern char strGPSreadout[readout_size];
extern char c;
extern unsigned int i;
extern unsigned int lineCount;
extern unsigned int finished;
#endif /* __main_h */