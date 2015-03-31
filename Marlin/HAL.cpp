/*
   Contributors:
   Copyright (c) 2014 Bob Cousins bobcousins42@googlemail.com
*/

/*
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
*/

// **************************************************************************
//
// Description:          *** HAL for Arduino Due ***
//
// **************************************************************************

// --------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------

#include "HAL.h"
#include "Configuration.h"

#include <Wire.h>
#include <malloc.h>

// --------------------------------------------------------------------------
// Externals
// --------------------------------------------------------------------------
extern "C" char *sbrk(int i);

// --------------------------------------------------------------------------
// Local defines
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Types
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Public Variables
// --------------------------------------------------------------------------

uint8_t MCUSR;
uint8_t HAL_step_timer_RC;

// --------------------------------------------------------------------------
// Private Variables
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Function prototypes
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Private functions
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Public functions
// --------------------------------------------------------------------------

// disable interrupts
void cli(void)
{
	// noInterrupts();
}

// enable interrupts
void sei(void)
{
	// interrupts();
}

void _delay_ms (int delay_ms)
{
	//todo: port for Due?
	delay (delay_ms);
}

void _delay_us (int delay_us)
{
  delayMicroseconds(delay_us);
}

// return free memory between end of heap (or end bss) and whatever is current
int freeMemory() {
  struct mallinfo memstruct = mallinfo();
  register char * stack_ptr asm ("sp");

  return (memstruct.fordblks + (int)stack_ptr -  (int)sbrk(0));
}

// --------------------------------------------------------------------------
// eeprom
// --------------------------------------------------------------------------

static bool eeprom_initialised = false;
static uint8_t eeprom_device_address = 0x50;

static void eeprom_init(void)
{
	if (!eeprom_initialised)
	{
		Wire.begin();
		eeprom_initialised = true;
	}
}

void eeprom_write_byte(unsigned char *pos, unsigned char value)
{
	unsigned eeprom_address = (unsigned) pos;

	eeprom_init();

	Wire.beginTransmission(eeprom_device_address);
	Wire.write((int)(eeprom_address >> 8));   // MSB
	Wire.write((int)(eeprom_address & 0xFF)); // LSB
    Wire.write(value);
	Wire.endTransmission();

	// wait for write cycle to complete
	// this could be done more efficiently with "acknowledge polling"
	delay(5);
}


unsigned char eeprom_read_byte(unsigned char *pos)
{
	byte data = 0xFF;
	unsigned eeprom_address = (unsigned) pos;

	eeprom_init ();

	Wire.beginTransmission(eeprom_device_address);
	Wire.write((int)(eeprom_address >> 8));   // MSB
	Wire.write((int)(eeprom_address & 0xFF)); // LSB
	Wire.endTransmission();
	Wire.requestFrom(eeprom_device_address, (byte)1);
	if (Wire.available())
		data = Wire.read();
	return data;
}

// --------------------------------------------------------------------------
// Timers
// --------------------------------------------------------------------------

typedef struct
{
    Tc          *pTimerRegs;
    uint16_t    channel;
    IRQn_Type   IRQ_Id;
  } tTimerConfig ;

#define  NUM_HARDWARE_TIMERS 9

static const tTimerConfig TimerConfig [NUM_HARDWARE_TIMERS] =
  {
    { TC0, 0, TC0_IRQn},
    { TC0, 1, TC1_IRQn},
    { TC0, 2, TC2_IRQn},
    { TC1, 0, TC3_IRQn},
    { TC1, 1, TC4_IRQn},
    { TC1, 2, TC5_IRQn},
    { TC2, 0, TC6_IRQn},
    { TC2, 1, TC7_IRQn},
    { TC2, 2, TC8_IRQn},
  };

  
/*
	Timer_clock1: Prescaler 2 -> 42MHz
	Timer_clock2: Prescaler 8 -> 10.5MHz
	Timer_clock3: Prescaler 32 -> 2.625MHz
	Timer_clock4: Prescaler 128 -> 656.25kHz
*/
	
// new timer by Ps991
// thanks for that work
// http://forum.arduino.cc/index.php?topic=297397.0

void HAL_step_timer_start()
{
  uint32_t tc_count, tc_clock;
  uint8_t timer_num;
  
  pmc_set_writeprotect(false); //remove write protection on registers
  NVIC_SetPriorityGrouping(4);
  
  // Timer for stepper
  // Timer 3 HAL.h STEP_TIMER_NUM
  timer_num = STEP_TIMER_NUM;
  
  // Get the ISR from table
  Tc *tc = TimerConfig [timer_num].pTimerRegs;
  IRQn_Type irq = TimerConfig [timer_num].IRQ_Id;
  uint32_t channel = TimerConfig [timer_num].channel;
  
  pmc_enable_periph_clk((uint32_t)irq); //we need a clock?
  NVIC_SetPriority(irq, NVIC_EncodePriority(4, 4, 0));
  
  TC_Configure(tc, channel, TC_CMR_TCCLKS_TIMER_CLOCK1 | TC_CMR_CPCTRG); //set clock rate (CLOCK1 is MCK/2) and reset counter register C on match
  tc->TC_CHANNEL[channel].TC_IER |= TC_IER_CPCS; //enable interrupt on timer match with register C

  tc->TC_CHANNEL[channel].TC_RC   = (VARIANT_MCK >> 1) / 1000; // start with 1kHz as frequency; //interrupt occurs every x interations of the timer counter
  TC_Start(tc, channel); //start timer counter
    
  tc->TC_CHANNEL[channel].TC_IER = TC_IER_CPCS;
  tc->TC_CHANNEL[channel].TC_IDR =~ TC_IER_CPCS;
  
  NVIC_EnableIRQ(irq); //enable Nested Vector Interrupt Controller
}


void HAL_temp_timer_start (uint8_t timer_num)
{
		
	Tc *tc = TimerConfig [timer_num].pTimerRegs;
	IRQn_Type irq = TimerConfig [timer_num].IRQ_Id;
	uint32_t channel = TimerConfig [timer_num].channel;

	pmc_set_writeprotect(false);
	pmc_enable_periph_clk((uint32_t)irq);
	
	NVIC_SetPriorityGrouping(4);
	
	NVIC_SetPriority(irq, NVIC_EncodePriority(4, 6, 0));
	
	TC_Configure (tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);

	uint32_t rc = VARIANT_MCK / 128 / (500);
	TC_SetRC(tc, channel, rc);
	TC_Start(tc, channel);

	//enable interrupt on RC compare
	tc->TC_CHANNEL[channel].TC_IER = TC_IER_CPCS;
	tc->TC_CHANNEL[channel].TC_IDR = ~TC_IER_CPCS;

	NVIC_EnableIRQ(irq);
}

void HAL_timer_enable_interrupt (uint8_t timer_num)
{
	const tTimerConfig *pConfig = &TimerConfig [timer_num];

	pConfig->pTimerRegs->TC_CHANNEL [pConfig->channel].TC_IER = TC_IER_CPCS;
	
}

void HAL_timer_disable_interrupt (uint8_t timer_num)
{
	const tTimerConfig *pConfig = &TimerConfig [timer_num];

	pConfig->pTimerRegs->TC_CHANNEL [pConfig->channel].TC_IDR = ~TC_IER_CPCS;
}

void HAL_timer_set_count (uint8_t timer_num, uint32_t count)
{
	if(count < 210) count = 210;
	const tTimerConfig *pConfig = &TimerConfig [timer_num];
	pConfig->pTimerRegs->TC_CHANNEL [pConfig->channel].TC_RC = count;
	
	//TC_SetRC (pConfig->pTimerRegs, pConfig->channel, count);
	
	if(TC_ReadCV(pConfig->pTimerRegs, pConfig->channel)>count)
		TC_Start(pConfig->pTimerRegs, pConfig->channel);
}

void HAL_timer_isr_prologue (uint8_t timer_num)
{
	const tTimerConfig *pConfig = &TimerConfig [timer_num];
	pConfig->pTimerRegs->TC_CHANNEL [pConfig->channel].TC_SR;
	// TC_GetStatus (pConfig->pTimerRegs, pConfig->channel);
}

int HAL_timer_get_count (uint8_t timer_num)
{
	Tc *tc = TimerConfig [timer_num].pTimerRegs;
	uint32_t channel = TimerConfig [timer_num].channel;
	return tc->TC_CHANNEL[channel].TC_RC;
}

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
//! @brief
//! @param[in]
//! @param[out]
//! @return
// --------------------------------------------------------------------------
