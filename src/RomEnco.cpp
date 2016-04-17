/*******************************************************************************
 * Copyright (c) 2015, Robopoly Development Team
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

  /***************************************************************************************
 *
 * Title:       RomEnco library v1.5
 * File:        RomEnco.cpp
 * Date:        2015-10-25
 * Author:      David Wuthier
 * Website:     https://github.com/Robopoly/Robopoly_RomEnco
 *
 ***************************************************************************************/


#include "RomEnco.h"


// Variable definitions.
uint8_t RomEnco::_encoderAmount = 0;
uint8_t RomEnco::_pinA[ROM_ENCO_MAX_ENCODER_AMOUNT] = {0, 0, 0, 0},
	RomEnco::_pinB[ROM_ENCO_MAX_ENCODER_AMOUNT] = {0, 0, 0, 0};
volatile uint8_t RomEnco::_pinAState[ROM_ENCO_MAX_ENCODER_AMOUNT] = {0, 0, 0, 0},
	RomEnco::_pinBState[ROM_ENCO_MAX_ENCODER_AMOUNT] = {0, 0, 0, 0};
volatile long RomEnco::_position[ROM_ENCO_MAX_ENCODER_AMOUNT] = {0, 0, 0, 0};


// Constructor.
RomEnco::RomEnco()
{
  // Nothing has to be done here, as the Arduino environnement may overwrite some settings.
}

// Destructor.
RomEnco::~RomEnco()
{
}

// Arduino constructor.
void RomEnco::begin(uint8_t pinA, uint8_t pinB)
{
	// If first encoder instantiated, setup timer #timerId.
	if (_encoderAmount == 0)
		_SetupTimer();
	// Increment encoder amount if smaller than maximum.
	if (_encoderAmount < ROM_ENCO_MAX_ENCODER_AMOUNT)
		_encoderAmount++;
	// Get an id for this instance.
	_id = _encoderAmount - 1;

	// Assign A and B pins.
	_pinA[_id] = pinA;
	_pinB[_id] = pinB;
	// Set them as input.
	pinMode(_pinA[_id], INPUT);
	pinMode(_pinB[_id], INPUT);

	// If debug enabled, set debug pin as output.
	#ifdef ROM_ENCO_DEBUG
		pinMode(ROM_ENCO_DEBUG_PIN, OUTPUT);
	#endif
}

#ifdef ROME_ENCO_USE_TIMER0
	ISR (TIMER0_OVF_vect)
#endif
#ifdef ROME_ENCO_USE_TIMER1
	ISR (TIMER1_OVF_vect)
#endif
#ifdef ROME_ENCO_USE_TIMER3
	ISR (TIMER3_OVF_vect)
#endif
#ifdef ROME_ENCO_USE_TIMER4
	ISR (TIMER4_OVF_vect)
#endif
	{
		// Update the position via timer X ISR.
		RomEnco::update();
	}



void RomEnco::_SetupTimer(void)
{
#ifdef ROME_ENCO_USE_TIMER0
	#ifdef __AVR_ATmega2560__
	// TODO
	#elif defined (__AVR_ATmega32U4__)
		// Enable timer 4 with no divider.
		TCCR0B = 0b00000101;
		// Enable timer 4 overflow ISR.
		TIMSK0 = 0b00000001;
	#endif
#endif

#ifdef ROME_ENCO_USE_TIMER1
	#ifdef __AVR_ATmega2560__
	// TODO
	#elif defined (__AVR_ATmega32U4__)
		// Enable timer 4 with no divider.
		TCCR1B = 0b00000101;
		// Enable timer 4 overflow ISR.
		TIMSK1 = 0b00000001;
	#endif
#endif

#ifdef ROME_ENCO_USE_TIMER3
	#ifdef __AVR_ATmega2560__
	// TODO
	#elif defined (__AVR_ATmega32U4__)
		// Enable timer 4 with no divider.
		TCCR3B = 0b00000101;
		// Enable timer 4 overflow ISR.
		TIMSK3 = 0b00000001;
	#endif
#endif

#ifdef ROME_ENCO_USE_TIMER4
	#ifdef __AVR_ATmega2560__
		// Enable timer 4 with no divider.
		TCCR4B = 0b00000101;
		// Enable timer 4 overflow ISR.
		TIMSK4 = 0b00000001;
	#elif defined (__AVR_ATmega32U4__)
		// Enable timer 4 with no divider.
		TCCR4B = 0b00000101;
		// Enable timer 4 overflow ISR.
		TIMSK4 = 0b00000100;
	#endif
#endif
}

// Update the position.
void RomEnco::update(void)
{
	// If debug enabled, indicate that the ISR begins.
#ifdef ROM_ENCO_DEBUG
		digitalWrite(ROM_ENCO_DEBUG_PIN, 1);
#endif

// Adjust timer period if needed.
/*#ifdef ROME_ENCO_USE_TIMER0
	TCNT0 = 100;
#endif
#ifdef ROME_ENCO_USE_TIMER1
	TCNT1 = 100;
#endif
#ifdef ROME_ENCO_USE_TIMER3
	TCNT3 = 100;
#endif
#ifdef ROME_ENCO_USE_TIMER4
	TCNT4 = 100;
#endif*/

	// Temporary variables.
	static bool oldPinAState, oldPinBState;

	// Poll each instanciated encoder.
	for (uint8_t i = 0; i < _encoderAmount; i++)
	{
		// Poll the encoders and store the previous state.
		oldPinAState = _pinAState[i];
		oldPinBState = _pinBState[i];
		_pinAState[i] = (bool)digitalRead(_pinA[i]);
		_pinBState[i] = (bool)digitalRead(_pinB[i]);

		// Apply the sommer algorithm to determine whether the
		// position is incremented or decremented.
		if ((oldPinBState != _pinAState[i]) && !(oldPinAState != _pinBState[i]))
			_position[i]--;
		if (!(oldPinBState != _pinAState[i]) && (oldPinAState != _pinBState[i]))
			_position[i]++;
	}

	// If debug enabled, indicate that the ISR ends.
#ifdef ROM_ENCO_DEBUG
		digitalWrite(ROM_ENCO_DEBUG_PIN, 0);
#endif
}

// Get the position.
long RomEnco::getPosition(void)
{
	return _position[_id];
}

// Reset the position.
void RomEnco::resetPosition(void)
{
	_position[_id] = 0;
}

// Get the position and then reset it.
long RomEnco::getIncrement(void)
{
	// Store the current position.
	long position = _position[_id];
	// Clear it.
	_position[_id] = 0;
	// Return the stored value.
	return position;
}
