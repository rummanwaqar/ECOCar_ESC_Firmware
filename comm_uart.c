/*
 * comm_uart.c
 *
 *  Created on: Dec 8, 2015
 *      Author: Rumman
 */

#include "comm_uart.h"
#include "ch.h"
#include "hal.h"

// Settings
#define UART_BAUD               115200
#define UART_DEVICE             UARTD2
#define UART_TX_PORT            GPIOA
#define UART_TX_PIN             2
#define UART_RX_PORT            GPIOA
#define UART_RX_PIN             3

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
  (void)c;
  // TODO: process the characters here
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

void comm_uart_init(void) {
  // Initialize UART
  uartStart( &UART_DEVICE, &uart_config );
  // Setup the UART pins
  palSetPadMode( UART_TX_PORT, UART_TX_PIN, PAL_MODE_ALTERNATE(7) |
                 PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUDR_PULLUP );
  palSetPadMode( UART_RX_PORT, UART_RX_PIN, PAL_MODE_ALTERNATE(7) |
                   PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUDR_PULLUP );

  // Start UART processing thread
  // TODO: chThdCreateStatic( );
}
