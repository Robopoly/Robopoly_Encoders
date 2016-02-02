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
 * Title:       Omniwheel Setup
 * Description: Display the amount of increments (in division) between each sampling
 *				time for three encoders.
 *
 ***************************************************************************************/


#include "RomEnco.h"


// Instanciate 3 encoders
RomEnco enco[3];

void setup(void)
{
  // Setup encoder 0 on pin 2 and 3. The interrupt routine will be run
  // on timer 4 (what can be changed by commenting/uncommenting #defines
  // in the library).
  enco[0].begin(2,3);
  // Setup encoder 1 on pin 4 and 5.
  enco[1].begin(4,5);
  // Setup encoder 2 on pin 6 and 7.
  enco[2].begin(6,7);
	// Begin serial for debugging.
	Serial.begin(57600);
}

void loop(void)
{
	// Display the position (in divisions) each 200 ms for each encoder.
	Serial.print(enco[0].getPosition());
	Serial.print(", ");
	Serial.print(enco[1].getPosition());
	Serial.print(", ");
	Serial.print(enco[2].getPosition());
	Serial.println(",");
	delay(200);
}
