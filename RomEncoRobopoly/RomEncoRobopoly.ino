
#include "RomEnco.h"

RomEnco enco(2,3);

void setup(void)
{
	Serial.begin(57600);
}

void loop(void)
{
	Serial.println(enco.getPosition());
	delay(200);
}
