
#include "RomEnco.h"


uint8_t RomEnco::_encoderAmount = 0;
uint8_t RomEnco::_pinA = 0, RomEnco::_pinB = 0;
volatile uint8_t RomEnco::_pinAState = 0, RomEnco::_pinBState = 0,
	RomEnco::_oldPinAState = 0, RomEnco::_oldPinBState = 0;
volatile int position = 0;

ISR (TIMER4_OVF_vect)
{
	RomEnco::Update();
}

void RomEnco::_SetupTimer4(void)
{
	TCCR4B = 0b00000010;
	TIMSK4 = 0b00000100;
}

RomEnco::RomEnco(uint8_t pinA, uint8_t pinB)
{
	_encoderAmount++;

	_pinA = pinA;
	_pinB = pinB;

	pinMode(_pinA, INPUT);
	pinMode(_pinB, INPUT);

	_SetupTimer4();
}

RomEnco::~RomEnco()
{

}

void RomEnco::_Update(void)
{
	_oldPinAState = _pinAState;
	_oldPinBState = _pinBState;
	_pinAState = (uint8_t)digitalRead(_pinA);
	_pinBState = (uint8_t)digitalRead(_pinB);

	uint8_t tmpA = _oldPinBState^_pinAState;
	uint8_t tmpB = _oldPinAState^_pinBState;

	if (tmpA && !tmpB)
		_position--;
	if (!tmpA && tmpB)
		_position++;
}

int RomEnco::getPosition(void)
{
	return _position;
}
