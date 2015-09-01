
#include "RomEnco.h"


uint8_t RomEnco::_encoderAmount = 0;
volatile uint8_t RomEnco::_pinA = 0;
volatile uint8_t RomEnco::_pinB = 0;
volatile uint8_t RomEnco::_ledState = 0;

ISR (TIMER4_OVF_vect)
{
	RomEnco::_Update();
}

void RomEnco::_SetupTimer4(void)
{
	TCCR4B = 0b00000010;
	TIMSK4 = 0b00000100;
	//sei();
}

RomEnco::RomEnco(uint8_t pinA)
{
	_SetupTimer4();
	_pinA = pinA;
	pinMode(_pinA, OUTPUT);
}

RomEnco::~RomEnco()
{

}

void RomEnco::_Update(void)
{
	_ledState = !_ledState;
	digitalWrite(_pinA, _ledState);
}

int16_t RomEnco::getPosition(void)
{
	return 0;
}
