/*
 * encoder.c
 *
 *  Created on: Dec 12, 2015
 *      Author: Rumman
 */

#include "ch.h"
#include "hal.h"
#include "encoder.h"

#define ENCODER_GPIO    GPIOE
#define ENCODER_A_PIN   0
#define ENCODER_B_PIN   2
#define ENCODER_C_PIN   4

/*
 * Encode state variable
 */
static encoder_type encoder_data;

/*
 * callback for encoders
 */
static void extcb(EXTDriver *extp, expchannel_t channel) {
  (void)extp;

  // update the encoder data structure
  switch(channel) {
  case ENCODER_A_PIN:
    encoder_data.A = palReadPad( ENCODER_GPIO, ENCODER_A_PIN );
    break;

  case ENCODER_B_PIN:
    encoder_data.B = palReadPad( ENCODER_GPIO, ENCODER_B_PIN );
    break;

  case ENCODER_C_PIN:
    encoder_data.C = palReadPad( ENCODER_GPIO, ENCODER_C_PIN );
    break;
  }
}


/*
 * EXT config
 * Set interrupts for all 3 encoder pins
 */
static const EXTConfig ext_config = {
  {
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOE, extcb},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOE, extcb},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOE, extcb},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL},
    {EXT_CH_MODE_DISABLED, NULL}
  }
};

void encoder_init(void) {
  // Initialize encoder data
  encoder_data = (encoder_type) {0, 0, 0};
  // Activate the EXT peripheral
  extStart( &EXTD1, &ext_config );
}

encoder_type encoder_values(void) {
  return encoder_data;
}
