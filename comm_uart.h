/*
 * comm_uart.h
 *
 *  Created on: Dec 8, 2015
 *      Author: Rumman
 */

#ifndef COMM_UART_H_
#define COMM_UART_H_

/*
 * Initializes uart communication thread
 * Using UART2 on PA2 (TX) and PA3 (RX)
 * @param process_function - pointer to command processing function
 */
void comm_uart_init( void (*process_function)(unsigned char *data, unsigned int len) );

#endif /* COMM_UART_H_ */
