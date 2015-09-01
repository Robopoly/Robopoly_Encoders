
#include "RomEnco.h"

static volatile uint8_t ledOn = 0u;

static void (*callback)(void);

ISR (TIMER4_OVF_vect)
{
	ledOn = !ledOn;
}

static void testFct(void)
{

}

uint8_t RomEnco::_encoderAmount = 0u;

void RomEnco::_setupInterrupt(void)
{
	TCCR4B = 0b00000010;
	TIMSK4 = 0b00000100;
	callback = testFct;
	pinMode(13, OUTPUT);
	sei();
}

RomEnco::RomEnco(uint8_t pinA, uint8_t pinB)
{
	if (_encoderAmount == 0u)
		_setupInterrupt();

	_encoderAmount++;
}

RomEnco::~RomEnco()
{

}

int16_t RomEnco::getPosition(void)
{
	digitalWrite(13, ledOn);
	return 0;
}
