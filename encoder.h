/*
 * encoder.h
 *
 *  Created on: Dec 12, 2015
 *      Author: Rumman
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include "datatypes.h"

/*
 * Initialized the interrupts to read interrupts
 */
void encoder_init(void);

/*
 * Gets the interrupt values
 * @returns encoder values
 */
encoder_type encoder_values(void);

#endif /* ENCODER_H_ */
