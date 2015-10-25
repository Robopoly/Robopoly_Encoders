
#include "RomEnco.h"


// Variable definitions.
uint8_t RomEnco::_encoderAmount = 0;
uint8_t RomEnco::_pinA[ROM_ENCO_MAX_ENCODER_AMOUNT] = {0, 0, 0, 0},
	RomEnco::_pinB[ROM_ENCO_MAX_ENCODER_AMOUNT] = {0, 0, 0, 0};
volatile uint8_t RomEnco::_pinAState[ROM_ENCO_MAX_ENCODER_AMOUNT] = {0, 0, 0, 0},
	RomEnco::_pinBState[ROM_ENCO_MAX_ENCODER_AMOUNT] = {0, 0, 0, 0};
volatile long RomEnco::_position[ROM_ENCO_MAX_ENCODER_AMOUNT] = {0, 0, 0, 0};


// Constructor.
RomEnco::RomEnco(uint8_t pinA, uint8_t pinB)
{
	// If first encoder instantiated, setup timer 4.
	if (_encoderAmount == 0)
		_SetupTimer4();
	// Increment encoder amount if smaller than maximum.
	if (_encoderAmount < ROM_ENCO_MAX_ENCODER_AMOUNT)
		_encoderAmount++;
	// Get an id for this instance.
	_id = _encoderAmount - 1;

	// Assign A and B pins.
	_pinA[_id] = pinA;
	_pinB[_id] = pinB;
	// Set them as input.
	pinMode(_pinA[_id], INPUT);
	pinMode(_pinB[_id], INPUT);

	// If debug enabled, set debug pin as output.
	#if ROM_ENCO_DEBUG
		pinMode(ROM_ENCO_DEBUG_PIN, OUTPUT);
	#endif
}

// Destructor.
RomEnco::~RomEnco()
{

}

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

// Update the position.
void RomEnco::update(void)
{
	// If debug enabled, indicate that the ISR begins.
	#if ROM_ENCO_DEBUG
		digitalWrite(ROM_ENCO_DEBUG_PIN, 1);
	#endif

	// Tune the period of the timer (should be less than 500 us).
	TCNT4 = 250;

	// Temporary variables.
	bool oldPinAState, oldPinBState, tmpA, tmpB;

	// Poll each instanciated encoder.
	for (uint8_t i = 0; i < _encoderAmount; i++)
	{
		// Poll the encoders and store the previous state.
		oldPinAState = _pinAState[i];
		oldPinBState = _pinBState[i];
		_pinAState[i] = (bool)digitalRead(_pinA[i]);
		_pinBState[i] = (bool)digitalRead(_pinB[i]);

		// Apply the sommer algorithm to determine whether the
		// position is incremented or decremented.
		tmpA = (oldPinBState != _pinAState[i]);
		tmpB = (oldPinAState != _pinBState[i]);
		if (tmpA && !tmpB)
			_position[i]--;
		if (!tmpA && tmpB)
			_position[i]++;
	}

	// If debug enabled, indicate that the ISR ends.
	#if ROM_ENCO_DEBUG
		digitalWrite(ROM_ENCO_DEBUG_PIN, 0);
	#endif
}

// Get the position.
long RomEnco::getPosition(void)
{
	return _position[_id];
}

// Reset the position.
void RomEnco::resetPosition(void)
{
	_position[_id] = 0;
}

// Get the position and then reset it.
long RomEnco::getIncrement(void)
{
	// Store the current position.
	long position = _position[_id];
	// Clear it.
	_position[_id] = 0;
	// Return the stored value.
	return position;
}
