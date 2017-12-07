#include <__cross_studio_io.h>

#include "salvo.h"       //include Pumpkin Salvo headers
#include "csk_uart.h"    //include necessary CubeSat Kit headers

//include written header files
#include "main.h"
#include "init.h"
#include "task_read_gps.h"
#include "task_blink.h"
#include "task_display_gps.h"

//Configuration Commands
#define NO_OP_COMMAND 0x01
#define RESET_SYSTEM 0x02
#define TRANSMIT_DATA 0x03
#define RECEIVE_DATA 0x04
#define GET_TRANSCEIVER_CONFIG 0x05
#define SET_TRANSCEIVER_CONFIG 0x06
#define TELEMETRY_QUERY 0x07
#define WRITE_FLASH 0x08
#define RF_CONFIG 0x09
#define I_MESSAGE_TYPE 0x10
#define BEACON_DATA 0x10
#define BEACON_CONFIG 0x11
#define READ_FIRMWARE_REVISION 0x12
#define WRITE_OVER_AIR_KEY 0x13
#define FIRMWARE_UPDATE 0x14
#define FIRMWARE_PACKET 0x15
#define FAST_PA_SET 0x20
#define TELEMETRY_DUMP_COMMAND 0x30
#define PING_RETURN_COMMAND 0x31
#define CODE_UPLOAD_COMMAND 0x32
#define RADIO_RESET_COMMAND 0x33
#define PIN_TOGGLE_COMMAND 0x34

// create global variables
csk_status_t csk_status;
unsigned int tick;
//char str_radio_header[] = "";
char c;
unsigned int i;
unsigned int lineCount;
unsigned int finished = 0;
unsigned int CK_A = 0;
unsigned int CK_B = 0;
char buffer[];

void Blink (void) {
  P1DIR = 0xFF;
  P1OUT = 0x00;
  while (1) {
    P1OUT ^= BIT0;                      // Toggle P1OUT:BIT0
    OS_Delay(10);                       //context switch and return after 1 second
  }
}

void calculate_header_checksum (char otherbytes []) { //double check this 
  int i;
  for(i=0; i<8; i++) {
    CK_A = CK_A + buffer[i];
    CK_B = CK_B + CK_A;
  }
 }

void NoOpRequest (void) {
  buffer[0] = 0x48; //This is a #define value of ‘H’
  buffer[1] = 0x65; //This is a #define value of ‘e’
  buffer[2] = I_MESSAGE_TYPE; //This is a #define value of 0x10
  buffer[3] = NO_OP_COMMAND; //This is a #define value of 0x01
  buffer[4] = 0x00; //There is no payload size information in a No-Op request
  buffer[5] = 0x00;
  calculate_header_checksum(&buffer[2]); //The first two synch bytes are not included in the checksum
  csk_uart1_puts(buffer);
}

void Recieve(void) {
  while(1) {
    debug_printf("%i", csk_uart1_getchar());
    debug_printf(" Recieved\n");
    OS_Yield();
  }
}

void Transmit(void) {
    char * message;
     *message = 'k';
    //csk_uart1_open(CSK_UART_9600_N81_ACLK);

  while(1) {
    //csk_uart1_puts(message);
    //csk_uart1_putchar(20);
    NoOpRequest();
    debug_printf("NoOpRequest Transmitted\n");
    OS_Yield();
  }
}

int main(void) {
  WDTCTL = WDTPW + WDTHOLD;
  __disable_interrupt();
  OSInit();

  csk_uart1_open(CSK_UART_9600_N81_ACLK);

  OSCreateTask(Transmit, OSTCBP(1), 10);
  OSCreateTask(Recieve, OSTCBP(2), 10);

  __enable_interrupt();

  while (1) {
    OSSched();
  }
  //csk_uart1_close();
}
