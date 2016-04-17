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
 * File:        RomEnco.h
 * Date:        2015-10-25
 * Author:      David Wuthier
 * Website:     https://github.com/Robopoly/Robopoly_RomEnco
 *
 ***************************************************************************************/

#ifndef _ROM_ENCO_H_
#define _ROM_ENCO_H_


#include <Arduino.h>


// Use the debug pin to know when the ISR occurs
// #define ROM_ENCO_DEBUG
// The debug pin.
#define ROM_ENCO_DEBUG_PIN 13
// Max amount of encoders.
#define ROM_ENCO_MAX_ENCODER_AMOUNT 4
// Select which timer to use
// #define ROME_ENCO_USE_TIMER0
// #define ROME_ENCO_USE_TIMER1
#define ROME_ENCO_USE_TIMER3
// #define ROME_ENCO_USE_TIMER4


class RomEnco
{
private:
	// Encoder amount
	static uint8_t _encoderAmount;
	// Id of the instance.
	uint8_t _id;
	// Where to read the A and B signals.
	static uint8_t _pinA[ROM_ENCO_MAX_ENCODER_AMOUNT],
		_pinB[ROM_ENCO_MAX_ENCODER_AMOUNT];
	// The corresponding signals.
	static volatile uint8_t _pinAState [ROM_ENCO_MAX_ENCODER_AMOUNT],
		_pinBState[ROM_ENCO_MAX_ENCODER_AMOUNT];
	// The positions.
	static volatile long _position[ROM_ENCO_MAX_ENCODER_AMOUNT];
	// Setup timer 4.
	void _SetupTimer(void);

public:
	// Constuctor with the A and B pins.
	RomEnco();
	// Destructor
	~RomEnco();

  // Select pins and start interrupt routine.
  void begin(uint8_t pinA, uint8_t pinB);
	// Update the positions.
	static void update(void);
	// Get the position.
	long getPosition(void);
	// Reset the position.
	void resetPosition(void);
	// Get the position and then reset it.
	long getIncrement(void);
};

#endif /* _ROM_ENCO_H_ */
