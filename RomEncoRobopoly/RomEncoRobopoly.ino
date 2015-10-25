
#include "RomEnco.h"

// Instanciate the encoder on pins 2 and 3.
RomEnco enco1(2, 3);
RomEnco enco2(4, 5);
RomEnco enco3(6, 7);

void setup(void)
{
	// Begin serial for debugging.
	Serial.begin(57600);
}

void loop(void)
{
	// Display the position (in divisions) each 200 ms.
	Serial.print(enco1.getIncrement());
	Serial.print(", ");
	Serial.print(enco2.getIncrement());
	Serial.print(", ");
	Serial.print(enco3.getIncrement());
	Serial.println(",");
	delay(200);
}
