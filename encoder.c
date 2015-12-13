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
 * callback for encoders
 */
static void extcb(EXTDriver *extp, expchannel_t channel) {
  (void)extp;

  switch(channel) {
  case ENCODER_A_PIN:
    if( palReadPad( ENCODER_GPIO, ENCODER_A_PIN ) )
      palSetPad( GPIOD, GPIOD_LED3 );
    else
      palClearPad( GPIOD, GPIOD_LED3 );
    break;

  case ENCODER_B_PIN:
    if( palReadPad( ENCODER_GPIO, ENCODER_B_PIN ) )
      palSetPad( GPIOD, GPIOD_LED4 );
    else
      palClearPad( GPIOD, GPIOD_LED4 );
    break;

  case ENCODER_C_PIN:
    if( palReadPad( ENCODER_GPIO, ENCODER_C_PIN ) )
      palSetPad( GPIOD, GPIOD_LED5 );
    else
      palClearPad( GPIOD, GPIOD_LED5 );
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
  // Activate the EXT peripheral
  extStart( &EXTD1, &ext_config );

}
