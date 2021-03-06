/*
    EcoCar Brushless DC Motor Controller Firmware
    Rumman Waqar 2015
*/

#include "ch.h"
#include "hal.h"
#include "comm_uart.h"
#include "datatypes.h"
#include "commands.h"
#include "comm_usb_serial.h"
#include "encoder.h"
#include "chprintf.h"

/*
 * printf function
 */
void main_printf(const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    chvprintf((BaseSequentialStream*)&SDU1, fmt, ap);
    va_end(ap);
}

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

  // initialize serial USB
  comm_usb_serial_init();

  // enable encoder
  encoder_init();

  // spawn blink thread
  (void)chThdCreateStatic(waBlink, sizeof(waBlink),LOWPRIO, blinkThread, NULL);
  comm_uart_init( commands_process_packet );

  // spin the main loop
  while(1){
    encoder_type encoder_data = encoder_values();
    main_printf( "A:%d B:%d C:%d\r\n", encoder_data.A, encoder_data.B, encoder_data.C );
    chThdSleepMilliseconds(50);
  }
  return 0;
}
