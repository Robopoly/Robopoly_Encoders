
#include "RomEnco.h"

// Constant variable definitions.
const bool RomEnco::_debug = true;
const uint8_t RomEnco::_debugPin = 13;

// Variable definitions.
uint8_t RomEnco::_encoderAmount = 0;
uint8_t RomEnco::_pinA = 0, RomEnco::_pinB = 0;
volatile uint8_t RomEnco::_pinAState = 0, RomEnco::_pinBState = 0,
	RomEnco::_oldPinAState = 0, RomEnco::_oldPinBState = 0;
volatile long RomEnco::_position = 0;

ISR (TIMER4_OVF_vect)
{
	// Update the position via timer 4 ISR.
	RomEnco::update();
}

void RomEnco::_SetupTimer4(void)
{
	// Enable timer 4 with no divider.
	TCCR4B = 0b00000001;
	// Enable timer 4 overflow ISR.
	TIMSK4 = 0b00000100;
}

// Constructor.
RomEnco::RomEnco(uint8_t pinA, uint8_t pinB)
{
	// Assign A and B pins.
	_pinA = pinA;
	_pinB = pinB;
	// Set them as input.
	pinMode(_pinA, INPUT);
	pinMode(_pinB, INPUT);

	// If debug enabled, set debug pin as output.
	if (_debug)
		pinMode(_debugPin, OUTPUT);

	// If first encoder instantiated, setup timer 4.
	if (_encoderAmount == 0)
	_SetupTimer4();
	// Increment encoder amount.
	_encoderAmount++;
}

// Destructor.
RomEnco::~RomEnco()
{

}

// Update the position.
void RomEnco::update(void)
{
	// If debug enabled, indicate that the ISR begins.
	if (_debug)
		digitalWrite(_debugPin, 1);

	// Tune the period of the timer (should be less than 500 us).
	TCNT4 = 250;

	// Poll the encoders and store the previous state.
	_oldPinAState = _pinAState;
	_oldPinBState = _pinBState;
	_pinAState = (bool)digitalRead(_pinA);
	_pinBState = (bool)digitalRead(_pinB);

	// Apply the sommer algorithm to determine whether the
	// position is incremented or decremented.
	bool tmpA = (_oldPinBState != _pinAState);
	bool tmpB = (_oldPinAState != _pinBState);
	if (tmpA && !tmpB)
		_position--;
	if (!tmpA && tmpB)
		_position++;

	// If debug enabled, indicate that the ISR ends.
	if (_debug)
		digitalWrite(_debugPin, 0);
}

// Get the position.
long RomEnco::getPosition(void)
{
	return _position;
}

// Reset the position.
void RomEnco::resetPosition(void)
{
	_position = 0;
}

// Get the position and then reset it.
long RomEnco::getIncrement(void)
{
	// Store the current position.
	long position = _position;
	// Clear it.
	_position = 0;
	// Return the stored value.
	return position;
}
