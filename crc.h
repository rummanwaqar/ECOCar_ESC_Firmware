/*
 * crc.h
 *
 *  Created on: Dec 8, 2015
 *      Author: Rumman
 */

#ifndef CRC_H_
#define CRC_H_

/*
 * calculate crc
 * @param buf - pointer to data
 * @param len - length of data
 */
unsigned short crc16(unsigned char *buf, unsigned int len);

#endif /* CRC_H_ */
