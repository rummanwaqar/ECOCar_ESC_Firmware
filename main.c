/*
    EcoCar Brushless DC Motor Controller Firmware
    Rumman Waqar 2015
*/

#include "ch.h"
#include "hal.h"

/*
 * Blinking LED (CPU Alive) Thread
 */
static THD_WORKING_AREA(waBlink, 128);
static THD_FUNCTION(blinkThread, arg) {
  (void)arg;
  chRegSetThreadName("blink");
  while(1) {
    palSetPad(GPIOD, GPIOD_LED6); // blue LED
    chThdSleepMilliseconds(400);
    palClearPad(GPIOD, GPIOD_LED6); // blue LED
    chThdSleepMilliseconds(400);
  }
}

/*
 * main function
 */
int main() {
  // system initializations
  halInit();
  chSysInit();

  // spawn blink thread
  (void)chThdCreateStatic(waBlink, sizeof(waBlink),LOWPRIO, blinkThread, NULL);

  // spin the main loop
  while(1){
    chThdSleepMilliseconds(500);
  }
  return 0;
}
