/*
 * commands.h
 *
 *  Created on: Dec 9, 2015
 *      Author: Rumman
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

/*
 * Initialize command thread
 */
void commands_init(void);

/*
 * Process command packet
 */
void commands_process_packet( unsigned char *data, unsigned int len );

/*
 * Send command data packet
 * @param data - pointer to data to be sent
 * @param len - length of data to be sent
 */
void commands_send_packet( unsigned char *data, unsigned int len );

#endif /* COMMANDS_H_ */
