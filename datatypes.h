/*
 * datatypes.h
 *
 *  Created on: Dec 9, 2015
 *      Author: Rumman
 */

#ifndef DATATYPES_H_
#define DATATYPES_H_

#include <stdint.h>
#include <stdbool.h>
#include "ch.h"

#define FW_VERSION_MAJOR        0
#define FW_VERSION_MINOR        1

/*
 * Encoder data type
 */
typedef struct {
  int A : 1;
  int B : 1;
  int C : 1;
} encoder_type;

/*
 * Packet handler datatype
 * Max packet handlers defined inside packet.h
 */
typedef enum {
  UART_PACKET_HANDLER = 0,  // UART
  CAN_PACKET_HANDLER = 1    // CAN Bus
} packet_type;

/*
 * Communication commands
 */
typedef enum {
  COMM_FW_VERSION = 0
} comm_packet_id;

#endif /* DATATYPES_H_ */
