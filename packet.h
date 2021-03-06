/*
 * packet.h
 *
 *  Created on: Dec 8, 2015
 *      Author: Rumman
 */

#ifndef PACKET_H_
#define PACKET_H_

#include <stdint.h>
#include "datatypes.h"

/*
 * Data Packaging:
 * - 1 Start byte (0x01)
 * - 1 Length byte
 * - Data bytes
 * - 2 CRC bytes
 * - 1 Stop bytes (0x02)
 */

// Settings
#define PACKET_RX_TIMEOUT           2
#define PACKET_HANDLERS             2
#define PACKET_MAX_LEN              256

#define START_COND                  0x01
#define STOP_COND                   0x02

// Functions
void packet_init( void (*send_function)(unsigned char *data, unsigned int len),
                  void (*process_function)(unsigned char *data, unsigned int len),
                  packet_type handler_num );
void packet_process_byte( uint8_t rx_data, packet_type handler_num );
void packet_send_packet( unsigned char *data, unsigned int len, packet_type handler_num);

#endif /* PACKET_H_ */
