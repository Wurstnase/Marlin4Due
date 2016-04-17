/*
 Contributors:
    Copyright (c) 2014 Bob Cousins bobcousins42@googlemail.com
    Copyright (c) 2015-2016 Nico Tonnhofer wurstnase.reprap@gmail.com
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
// Description: Fast IO functions for Arduino Due
//
// ARDUINO_ARCH_SAM
// **************************************************************************

#ifndef	_FASTIO_H
#define	_FASTIO_H

/*
  utility functions
*/

#ifndef MASK
  #define MASK(PIN)  (1 << PIN)
#endif


// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------

/// Read a pin
//#define	READ(pin)  PIO_Get(g_APinDescription[pin].pPort, PIO_INPUT, g_APinDescription[pin].ulPin)
/// write to a pin
//#define	WRITE(pin, v) do{if(v) {g_APinDescription[pin].pPort->PIO_SODR = g_APinDescription[pin].ulPin;} else {g_APinDescription[pin].pPort->PIO_CODR = g_APinDescription[pin].ulPin; }}while(0)
  
static inline void digitalFastWrite(int pin, bool v) {
  if (v) g_APinDescription[pin].pPort->PIO_SODR = g_APinDescription[pin].ulPin;
  else g_APinDescription[pin].pPort->PIO_CODR = g_APinDescription[pin].ulPin;
}

// static inline bool digitalFastRead(int pin) {
  // return PIO_Get(g_APinDescription[pin].pPort, PIO_INPUT, g_APinDescription[pin].ulPin);
// }

#define _FASTREAD(IO) ((bool)(DIO ## IO ## _WPORT -> PIO_PDSR & (MASK(DIO ## IO ## _PIN))))

#define _FASTWRITE(IO, v) do {  if (v) {DIO ## IO ## _WPORT -> PIO_SODR = MASK(DIO ## IO ##_PIN); } \
                                else {DIO ##  IO ## _WPORT -> PIO_CODR = MASK(DIO ## IO ## _PIN); }; \
                          } while (0)

// #define READ(pin) digitalFastRead(pin)
#define READ(pin) _FASTREAD(pin)
#define WRITE_VAR(pin, v) digitalFastWrite(pin, v)
#define WRITE(pin, v) _FASTWRITE(pin, v)

#define	SET_INPUT(pin) pmc_enable_periph_clk(g_APinDescription[pin].ulPeripheralId); \
    PIO_Configure(g_APinDescription[pin].pPort, PIO_INPUT, g_APinDescription[pin].ulPin, 0) 

#define	SET_OUTPUT(pin) PIO_Configure(g_APinDescription[pin].pPort, PIO_OUTPUT_1, \
	g_APinDescription[pin].ulPin, g_APinDescription[pin].ulPinConfiguration)

/// toggle a pin	
#define TOGGLE(pin) WRITE(pin,!READ(pin))

// Write doesn't work for pullups
#define PULLUP(IO,v) {pinMode(IO, (v!=LOW ? INPUT_PULLUP : INPUT)); }

/// check if pin is an input
#define GET_INPUT(IO)
/// check if pin is an output
#define GET_OUTPUT(IO)

/// check if pin is an timer
#define GET_TIMER(IO)

// Shorthand
#define OUT_WRITE(IO, v) { SET_OUTPUT(IO); WRITE(IO, v); }

/*
** direct pins
*/

#define DIO0_PIN 8
#define DIO0_WPORT PIOA

#define DIO1_PIN 9
#define DIO1_WPORT PIOA

#define DIO2_PIN 25
#define DIO2_WPORT PIOB

#define DIO3_PIN 28
#define DIO3_WPORT PIOC

#define DIO4_PIN 26
#define DIO4_WPORT PIOC

#define DIO5_PIN 25
#define DIO5_WPORT PIOC

#define DIO6_PIN 24
#define DIO6_WPORT PIOC

#define DIO7_PIN 23
#define DIO7_WPORT PIOC

#define DIO8_PIN 22
#define DIO8_WPORT PIOC

#define DIO9_PIN 21
#define DIO9_WPORT PIOC

#define DIO10_PIN 29
#define DIO10_WPORT PIOC

#define DIO11_PIN 7
#define DIO11_WPORT PIOD

#define DIO12_PIN 8
#define DIO12_WPORT PIOD

#define DIO13_PIN 27
#define DIO13_WPORT PIOB

#define DIO14_PIN 4
#define DIO14_WPORT PIOD

#define DIO15_PIN 5
#define DIO15_WPORT PIOD

#define DIO16_PIN 13
#define DIO16_WPORT PIOA

#define DIO17_PIN 12
#define DIO17_WPORT PIOA

#define DIO18_PIN 11
#define DIO18_WPORT PIOA

#define DIO19_PIN 10
#define DIO19_WPORT PIOA

#define DIO20_PIN 12
#define DIO20_WPORT PIOB

#define DIO21_PIN 13
#define DIO21_WPORT PIOB

#define DIO22_PIN 26
#define DIO22_WPORT PIOB

#define DIO23_PIN 14
#define DIO23_WPORT PIOA

#define DIO24_PIN 15
#define DIO24_WPORT PIOA

#define DIO25_PIN 0
#define DIO25_WPORT PIOD

#define DIO26_PIN 1
#define DIO26_WPORT PIOD

#define DIO27_PIN 2
#define DIO27_WPORT PIOD

#define DIO28_PIN 3
#define DIO28_WPORT PIOD

#define DIO29_PIN 6
#define DIO29_WPORT PIOD

#define DIO30_PIN 9
#define DIO30_WPORT PIOD

#define DIO31_PIN 7
#define DIO31_WPORT PIOA

#define DIO32_PIN 10
#define DIO32_WPORT PIOD

#define DIO33_PIN 1
#define DIO33_WPORT PIOC

#define DIO34_PIN 2
#define DIO34_WPORT PIOC

#define DIO35_PIN 3
#define DIO35_WPORT PIOC

#define DIO36_PIN 4
#define DIO36_WPORT PIOC

#define DIO37_PIN 5
#define DIO37_WPORT PIOC

#define DIO38_PIN 6
#define DIO38_WPORT PIOC

#define DIO39_PIN 7
#define DIO39_WPORT PIOC

#define DIO40_PIN 8
#define DIO40_WPORT PIOC

#define DIO41_PIN 9
#define DIO41_WPORT PIOC

#define DIO42_PIN 19
#define DIO42_WPORT PIOA

#define DIO43_PIN 20
#define DIO43_WPORT PIOA

#define DIO44_PIN 19
#define DIO44_WPORT PIOC

#define DIO45_PIN 18
#define DIO45_WPORT PIOC

#define DIO46_PIN 17
#define DIO46_WPORT PIOC

#define DIO47_PIN 16
#define DIO47_WPORT PIOC

#define DIO48_PIN 15
#define DIO48_WPORT PIOC

#define DIO49_PIN 14
#define DIO49_WPORT PIOC

#define DIO50_PIN 13
#define DIO50_WPORT PIOC

#define DIO51_PIN 12
#define DIO51_WPORT PIOC

#define DIO52_PIN 21
#define DIO52_WPORT PIOB

#define DIO53_PIN 14
#define DIO53_WPORT PIOB

#define DIO54_PIN 16
#define DIO54_WPORT PIOA

#define DIO55_PIN 24
#define DIO55_WPORT PIOA

#define DIO56_PIN 23
#define DIO56_WPORT PIOA

#define DIO57_PIN 22
#define DIO57_WPORT PIOA

#define DIO58_PIN 6
#define DIO58_WPORT PIOA

#define DIO59_PIN 4
#define DIO59_WPORT PIOA

#define DIO60_PIN 3
#define DIO60_WPORT PIOA

#define DIO61_PIN 2
#define DIO61_WPORT PIOA

#define DIO62_PIN 17
#define DIO62_WPORT PIOB

#define DIO63_PIN 18
#define DIO63_WPORT PIOB

#define DIO64_PIN 19
#define DIO64_WPORT PIOB

#define DIO65_PIN 20
#define DIO65_WPORT PIOB

#define DIO66_PIN 15
#define DIO66_WPORT PIOB

#define DIO67_PIN 16
#define DIO67_WPORT PIOB

#define DIO68_PIN 1
#define DIO68_WPORT PIOA

#define DIO69_PIN 0
#define DIO69_WPORT PIOA

#define DIO70_PIN 17
#define DIO70_WPORT PIOA

#define DIO71_PIN 18
#define DIO71_WPORT PIOA

#define DIO72_PIN 30
#define DIO72_WPORT PIOC

#define DIO73_PIN 21
#define DIO73_WPORT PIOA

#define DIO74_PIN 25
#define DIO74_WPORT PIOA

#define DIO75_PIN 26
#define DIO75_WPORT PIOA

#define DIO76_PIN 27
#define DIO76_WPORT PIOA

#define DIO77_PIN 28
#define DIO77_WPORT PIOA

#define DIO78_PIN 23
#define DIO78_WPORT PIOB

#define DIO79_PIN 17
#define DIO79_WPORT PIOA

#define DIO80_PIN 12
#define DIO80_WPORT PIOB

#define DIO81_PIN 8
#define DIO81_WPORT PIOA

#define DIO82_PIN 11
#define DIO82_WPORT PIOA

#define DIO83_PIN 13
#define DIO83_WPORT PIOA

#define DIO84_PIN 4
#define DIO84_WPORT PIOD

#define DIO85_PIN 11
#define DIO85_WPORT PIOB

#define DIO86_PIN 21
#define DIO86_WPORT PIOB

#define DIO87_PIN 29
#define DIO87_WPORT PIOA

#define DIO88_PIN 15
#define DIO88_WPORT PIOB

#define DIO89_PIN 14
#define DIO89_WPORT PIOB

#define DIO90_PIN 1
#define DIO90_WPORT PIOA

#define DIO91_PIN 15
#define DIO91_WPORT PIOB

#endif	/* _FASTIO_H */
