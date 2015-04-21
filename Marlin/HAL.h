/*
 Contributors:
    Copyright (c) 2014 Bob Cousins bobcousins42@googlemail.com
*/
/* **************************************************************************
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

// **************************************************************************
//
// Description:          *** HAL for Arduino Due ***
//
// ARDUINO_ARCH_SAM
// **************************************************************************

#ifndef _HAL_H
#define _HAL_H

// --------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------

#include <stdint.h>

#include "Arduino.h"
#include "fastio.h"

// --------------------------------------------------------------------------
// Defines
// --------------------------------------------------------------------------

#define analogInputToDigitalPin(IO) IO

#define     CRITICAL_SECTION_START	uint32_t primask=__get_PRIMASK(); __disable_irq();
#define     CRITICAL_SECTION_END    if (primask==0) __enable_irq();

// On AVR this is in math.h?
#define square(x) ((x)*(x))

#define strncpy_P(dest, src, num) strncpy((dest), (src), (num))

#define HIGH 1
#define LOW 0

// --------------------------------------------------------------------------
// Types
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Public Variables
// --------------------------------------------------------------------------

// reset reason set by bootloader
extern uint8_t MCUSR;
static uint32_t tone_pin;

// --------------------------------------------------------------------------
// Public functions
// --------------------------------------------------------------------------

// Disable interrupts
void cli(void);

// Enable interrupts
void sei(void);

static inline void _delay_ms(uint32_t msec) {
	delay(msec);
}

static inline void _delay_us(uint32_t usec) {
  uint32_t n = usec * (F_CPU / 3000000);
  asm volatile(
      "L2_%=_delayMicroseconds:"       "\n\t"
      "subs   %0, #1"                 "\n\t"
      "bge    L2_%=_delayMicroseconds" "\n"
      : "+r" (n) :  
  );
}

int freeMemory(void);
void eeprom_write_byte(unsigned char *pos, unsigned char value);
unsigned char eeprom_read_byte(unsigned char *pos);


// timers
#define STEP_TIMER_NUM 2
#define TEMP_TIMER_NUM 3
#define BEEPER_TIMER_NUM 4

#define HAL_TIMER_RATE 		     (long)(F_CPU/2)
#define TICKS_PER_NANOSECOND   (HAL_TIMER_RATE)/1000

#define ENABLE_STEPPER_DRIVER_INTERRUPT()	HAL_timer_enable_interrupt (STEP_TIMER_NUM)
#define DISABLE_STEPPER_DRIVER_INTERRUPT()	HAL_timer_disable_interrupt (STEP_TIMER_NUM)

//
#define HAL_STEP_TIMER_ISR 	void TC2_Handler()
#define HAL_TEMP_TIMER_ISR 	void TC3_Handler()
#define HAL_BEEPER_TIMER_ISR  void TC4_Handler()

void HAL_step_timer_start(void);
void HAL_temp_timer_start (uint8_t timer_num);
void HAL_timer_set_count (uint8_t timer_num, uint32_t count);

void HAL_timer_enable_interrupt (uint8_t timer_num);
void HAL_timer_disable_interrupt (uint8_t timer_num);

void HAL_timer_isr_status (uint8_t timer_num);
int HAL_timer_get_count (uint8_t timer_num);
//

void tone(uint8_t pin, int frequency);
void noTone(uint8_t pin);

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------

#endif // _HAL_H

