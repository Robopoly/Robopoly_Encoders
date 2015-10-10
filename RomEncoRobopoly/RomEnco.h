
#include <Arduino.h>


class RomEnco
{
private:
	// Use the debug pin to know when the ISR occurs.
	static const bool _debug;
	// The debug pin.
	static const uint8_t _debugPin;
	// Max encoder amount
	static uint8_t _encoderAmount;
	// Where to read the A and B signals.
	static uint8_t _pinA, _pinB;
	// The corresponding signal (current and previous state).
	static volatile uint8_t _pinAState, _pinBState,
		_oldPinAState, _oldPinBState;
	// The position.
	static volatile long _position;
	// Setup timer 4.
	void _SetupTimer4(void);

public:
	// Constuctor with the A and B pins.
	RomEnco(uint8_t pinA, uint8_t pinB);
	// Destructor
	~RomEnco();

	// Update the position.
	static void update(void);
	// Get the position.
	long getPosition(void);
	// Reset the position.
	void resetPosition(void);
	// Get the position and then reset it.
	long getIncrement(void);
};
