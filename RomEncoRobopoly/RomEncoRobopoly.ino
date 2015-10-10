
#include "RomEnco.h"

// Instanciate the encoder on pins 2 and 3.
RomEnco enco(2,3);

void setup(void)
{
	// Begin serial for debugging.
	Serial.begin(57600);
}

void loop(void)
{
	// Display the position (in divisions) each 200 ms.
	Serial.println(enco.getIncrement());
	delay(200);
}
