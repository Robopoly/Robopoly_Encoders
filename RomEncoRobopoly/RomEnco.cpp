
#include "RomEnco.h"


const bool RomEnco::_debug = true;
const uint8_t RomEnco::_debugPin = 13;

uint8_t RomEnco::_encoderAmount = 0;
uint8_t RomEnco::_pinA = 0, RomEnco::_pinB = 0;
volatile uint8_t RomEnco::_pinAState = 0, RomEnco::_pinBState = 0,
	RomEnco::_oldPinAState = 0, RomEnco::_oldPinBState = 0;
volatile int RomEnco::_position = 0;

ISR (TIMER4_OVF_vect)
{
	RomEnco::update();
}

void RomEnco::_SetupTimer4(void)
{
	TCCR4B = 0b00000001;
	TIMSK4 = 0b00000100;
}

RomEnco::RomEnco(uint8_t pinA, uint8_t pinB)
{
	_pinA = pinA;
	_pinB = pinB;

	pinMode(_pinA, INPUT);
	pinMode(_pinB, INPUT);

	if (_debug)
		pinMode(_debugPin, OUTPUT);

	if (_encoderAmount == 0)
	_SetupTimer4();

	_encoderAmount++;
}

RomEnco::~RomEnco()
{

}

void RomEnco::update(void)
{
	if (_debug)
		digitalWrite(_debugPin, 1);

	TCNT4 = 200;

	_oldPinAState = _pinAState;
	_oldPinBState = _pinBState;
	_pinAState = (bool)digitalRead(_pinA);
	_pinBState = (bool)digitalRead(_pinB);

	bool tmpA = (_oldPinBState != _pinAState);
	bool tmpB = (_oldPinAState != _pinBState);

	if (tmpA && !tmpB)
		_position--;
	if (!tmpA && tmpB)
		_position++;

	if (_debug)
		digitalWrite(_debugPin, 0);
}

int RomEnco::getPosition(void)
{
	return _position;
}
