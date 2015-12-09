/*
 * commands.c
 *
 *  Created on: Dec 9, 2015
 *      Author: Rumman
 */

#include "ch.h"
#include "hal.h"
#include "commands.h"
#include "datatypes.h"
#include "packet.h"

// Private variables
static uint8_t send_buffer[PACKET_MAX_LEN];

/*
 * Process command packet
 */
void commands_process_packet( unsigned char *data, unsigned int len ) {
  if(!len) return;

  // Get command ID
  comm_packet_id packet_id = data[0];
  data++; len--;

  int32_t index = 0;

  switch(packet_id) {
  case COMM_FW_VERSION:
    index = 0;
    send_buffer[index++] = COMM_FW_VERSION;
    send_buffer[index++] = FW_VERSION_MAJOR;
    send_buffer[index++] = FW_VERSION_MINOR;
    commands_send_packet( send_buffer, index );
    break;

  }
}

/*
 * Send command data packet
 * @param data - pointer to data to be sent
 * @param len - length of data to be sent
 */
void commands_send_packet( unsigned char *data, unsigned int len ){
  packet_send_packet( data, len, UART_PACKET_HANDLER );
}
