/*
 * comm_uart.c
 *
 *  Created on: Dec 8, 2015
 *      Author: Rumman
 */

#include "ch.h"
#include "hal.h"
#include "comm_uart.h"
#include "packet.h"

#include <string.h>

// Settings
#define UART_BAUD               115200
#define UART_DEVICE             UARTD2
#define UART_TX_PORT            GPIOA
#define UART_TX_PIN             2
#define UART_RX_PORT            GPIOA
#define UART_RX_PIN             3
#define UART_RX_BUFFER_SIZE     1024

// Threads
static THD_FUNCTION( packet_process_thread, arg );
static THD_WORKING_AREA( packet_process_thread_wa, 4096 );
static thread_t *packet_process_tp;

// Variables
static uint8_t uart_rx_buffer[UART_RX_BUFFER_SIZE];
static int uart_rx_read_pos = 0;
static int uart_rx_write_pos = 0;

// Private functions
static void send_packet( unsigned char *data, unsigned int len );

/*
 * This callback is invoked when a transmission buffer has been completely
 * read by the driver.
 */
static void txend1(UARTDriver *uartp) {
  (void)uartp;
}

/*
 * This callback is invoked when a transmission has physically completed.
 */
static void txend2(UARTDriver *uartp) {
  (void)uartp;
}

/*
 * This callback is invoked on a receive error, the errors mask is passed
 * as parameter.
 */
static void rxerr(UARTDriver *uartp, uartflags_t e) {
  (void)uartp;
  (void)e;
}

/*
 * This callback is invoked when a character is received but the application
 * was not ready to receive it, the character is passed as parameter.
 */
static void rxchar(UARTDriver *uartp, uint16_t c) {
  (void)uartp;

  // Put the character in a buffer
  uart_rx_buffer[uart_rx_write_pos++] = c;

  // wrap back on overflow
  if( uart_rx_write_pos == UART_RX_BUFFER_SIZE )uart_rx_write_pos = 0;

  // notify the thread that there is data available
  chEvtSignalI( packet_process_tp, (eventmask_t) 1 );
}

/*
 * This callback is invoked when a receive buffer has been completely written.
 */
static void rxend(UARTDriver *uartp) {
  (void)uartp;
}

/*
 * UART driver configuration structure
 */
static UARTConfig uart_config = {
   // end of tx buffer callback
   txend1,
   // physical end of tx callback
   txend2,
   // rx buffer filled callback
   rxend,
   // character rx while out of UART_RECIEVE state
   rxchar,
   // rx error callback
   rxerr,
   // baud rate
   UART_BAUD,
   // CR1 reg
   0,
   // CR2 reg
   USART_CR2_LINEN,
   // CR3 reg
   0
};

/*
 * Thread function to process each received byte
 */
static THD_FUNCTION( packet_process_thread, arg ) {
  (void) arg;

  chRegSetThreadName( "comm_uart process" );
  // returns pointer to current thread
  packet_process_tp = chThdGetSelfX();

  // main loop
  while(1) {
    // wait for data available signal (sent by rxchar callback)
    chEvtWaitAny( (eventmask_t) 1 );

    // process data as long as it is available
    while( uart_rx_read_pos != uart_rx_write_pos ) {
      // TODO: call function to process the data and increment read pos
      // process( uart_rx_buffer[ uart_rx_read_pos++ ] );

      // wrap back on overflow (circular buffer)
      if( uart_rx_read_pos == UART_RX_BUFFER_SIZE ) uart_rx_read_pos = 0;
    }
  }
}

/*
 * send data packet over UART
 * @param data - pointer to data to send
 * @param len - length of data to send
 */
static void send_packet( unsigned char *data, unsigned int len ) {
  // wait for previous transmission to finish
  while( UART_DEVICE.txstate == UART_TX_ACTIVE ) chThdSleep(1);

  // copy data to another buffer
  static uint8_t buffer[PACKET_MAX_LEN + 5];
  memcpy( buffer, data, len );

  // send the data over UART
  uartStartSend( &UART_DEVICE, len, buffer );
}

void comm_uart_init(void) {
  // TODO: Initialize packet and pass send_packet function

  // Initialize UART
  uartStart( &UART_DEVICE, &uart_config );
  // Setup the UART pins
  palSetPadMode( UART_TX_PORT, UART_TX_PIN, PAL_MODE_ALTERNATE(7) |
                 PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUDR_PULLUP );
  palSetPadMode( UART_RX_PORT, UART_RX_PIN, PAL_MODE_ALTERNATE(7) |
                   PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUDR_PULLUP );

  // Start UART processing thread
  chThdCreateStatic( packet_process_thread_wa, sizeof(packet_process_thread_wa),
                     NORMALPRIO, packet_process_thread, NULL );
}
