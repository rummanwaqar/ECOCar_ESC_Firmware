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

// Packet handler datatype
// Max packet handlers defined inside packet.h
typedef enum {
  UART_PACKET_HANDLER = 0,  // UART
  CAN_PACKET_HANDLER = 1    // CAN Bus
} packet_type;

#endif /* DATATYPES_H_ */
