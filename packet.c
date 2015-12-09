/*
 * packet.c
 *
 *  Created on: Dec 8, 2015
 *      Author: Rumman
 */

#include "packet.h"
//#include "crc.h"

#include <string.h>

/*
 * Typedef for packet state
 */
typedef struct {
  volatile unsigned char rx_state;
  volatile unsigned char rx_timeout;
  void(*send_func)(unsigned char *data, unsigned int len);
  void(*process_func)(unsigned char *data, unsigned int len);
  unsigned int payload_len;
  unsigned char rx_buff[PACKET_MAX_LEN];
  unsigned char tx_buff[PACKET_MAX_LEN + 6];
  unsigned int rx_data_ptr;
  unsigned char crc_low;
  unsigned char crc_high;
} PACKET_STATE_T;

// array to hold different packet handlers (uart, can)
static PACKET_STATE_T handler_states[PACKET_HANDLERS];

/*
 * initializes the packet for a particular handler
 * @param send_function - pointer to TX function
 * @param process_function - pointer to processing function
 * @param handler_num - handler number
 */
void packet_init( void (*send_function)(unsigned char *data, unsigned int len),
                  void (*process_function)(unsigned char *data, unsigned int len),
                  int handler_num ) {
  handler_states[handler_num].send_func = send_function;
  handler_states[handler_num].process_func = process_function;
}

/*
 * packages the data to be send and calling the send function
 * @param data - pointer to data to be transmitted
 * @param len - length of data to be transmitted
 * @handler_num - handler number
 */
void packet_send_packet( unsigned char *data, unsigned int len, int handler_num) {
  // ensure length of data is less than max size
  if( len > PACKET_MAX_LEN ) return;

  int i = 0;

  // start byte
  handler_states[handler_num].tx_buff[i++] = START_COND;
  // length byte
  handler_states[handler_num].tx_buff[i++] = len;
  // copy the data bytes
  memcpy( handler_states[handler_num].tx_buff + i, data, len );
  i += len;
  // add the crc bytes
  unsigned short crc = 4; // TODO: replace with crc function
  handler_states[handler_num].tx_buff[i++] = (uint8_t) (crc >> 8);
  handler_states[handler_num].tx_buff[i++] = (uint8_t) (crc & 0xFF);
  // stop byte
  handler_states[handler_num].tx_buff[i++] = STOP_COND;

  // send the data
  if( handler_states[handler_num].send_func )
    handler_states[handler_num].send_func( handler_states[handler_num].tx_buff, i );
}

/*
 * call this function every millisecond
 */
void packet_timerfunc( void ) {
  // for each packet handler
  for(int i=0; i<PACKET_HANDLERS; i++) {
    if( handler_states[i].rx_timeout )
      handler_states[i].rx_timeout--;   // if timeout != 0 subtract 1
    else
      handler_states[i].rx_state = 0;   // if timeout == 0 reset rx_state
  }
}

/*
 * process a packet byte
 * @param rx_data - data byte received
 * @param handler_num - handler number
 */
void packet_process( uint8_t rx_data, int handler_num ) {
  switch( handler_states[handler_num].rx_state ){
  // start byte (initialize)
  case 0:
    if( rx_data == START_COND ) {
      handler_states[handler_num].rx_state++;
      handler_states[handler_num].rx_timeout = PACKET_RX_TIMEOUT;
      handler_states[handler_num].rx_data_ptr = 0;
      handler_states[handler_num].payload_len = 0;
    } else { // wrong start condition
      handler_states[handler_num].rx_state = 0;
    }
    break;

  // length byte
  case 1:
    handler_states[handler_num].payload_len = rx_data;
    handler_states[handler_num].rx_state++;
    handler_states[handler_num].rx_timeout = PACKET_RX_TIMEOUT;
    break;

  // data bytes
  case 2:
    handler_states[handler_num].rx_buff[handler_states[handler_num].rx_data_ptr++] = rx_data;
    // if all data read
    if( handler_states[handler_num].rx_data_ptr == handler_states[handler_num].payload_len )
      handler_states[handler_num].rx_state++;
    handler_states[handler_num].rx_timeout = PACKET_RX_TIMEOUT;
    break;

  // crc high byte
  case 3:
    handler_states[handler_num].crc_high = rx_data;
    handler_states[handler_num].rx_state++;
    handler_states[handler_num].rx_timeout = PACKET_RX_TIMEOUT;
    break;

  // crc low byte
  case 4:
    handler_states[handler_num].crc_low = rx_data;
    handler_states[handler_num].rx_state++;
    handler_states[handler_num].rx_timeout = PACKET_RX_TIMEOUT;
    break;

  // stop byte (reset)
  case 5:
    if( rx_data == STOP_COND ){
      if( 1 ) { // TODO: check crc here
        // Packet received
        if( handler_states[handler_num].process_func ) {
          handler_states[handler_num].process_func( handler_states[handler_num].rx_buff,
                                                    handler_states[handler_num].payload_len );
        }
      }
    }
    handler_states[handler_num].rx_state = 0;
    break;

  default:
    handler_states[handler_num].rx_state = 0;
    break;
  }
}
