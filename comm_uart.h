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
 */
void comm_uart_init(void);

#endif /* COMM_UART_H_ */
