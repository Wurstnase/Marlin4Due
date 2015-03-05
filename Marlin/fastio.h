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
// Description: Fast IO functions for Arduino Due
//
// ARDUINO_ARCH_SAM
// **************************************************************************

#ifndef	_FASTIO_H
#define	_FASTIO_H

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------

/// Read a pin
#define	READ(pin)  PIO_Get(g_APinDescription[pin].pPort, PIO_INPUT, g_APinDescription[pin].ulPin)
/// write to a pin
#define	WRITE(pin, v) do{if(v) {g_APinDescription[pin].pPort->PIO_SODR = g_APinDescription[pin].ulPin;} else {g_APinDescription[pin].pPort->PIO_CODR = g_APinDescription[pin].ulPin; }}while(0)

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

#endif	/* _FASTIO_H */