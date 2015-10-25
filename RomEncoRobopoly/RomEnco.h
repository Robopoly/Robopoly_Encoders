
#include <Arduino.h>


// Use the debug pin to know when the ISR occurs?
#define ROM_ENCO_DEBUG 1
// The debug pin.
#define ROM_ENCO_DEBUG_PIN 13
// Max amount of encoders.
#define ROM_ENCO_MAX_ENCODER_AMOUNT 4


class RomEnco
{
private:
	// Encoder amount
	static uint8_t _encoderAmount;
	// Id of the instance.
	uint8_t _id;
	// Where to read the A and B signals.
	static uint8_t _pinA[ROM_ENCO_MAX_ENCODER_AMOUNT],
		_pinB[ROM_ENCO_MAX_ENCODER_AMOUNT];
	// The corresponding signals.
	static volatile uint8_t _pinAState [ROM_ENCO_MAX_ENCODER_AMOUNT],
		_pinBState[ROM_ENCO_MAX_ENCODER_AMOUNT];
	// The positions.
	static volatile long _position[ROM_ENCO_MAX_ENCODER_AMOUNT];
	// Setup timer 4.
	void _SetupTimer4(void);

public:
	// Constuctor with the A and B pins.
	RomEnco(uint8_t pinA, uint8_t pinB);
	// Destructor
	~RomEnco();

	// Update the positions.
	static void update(void);
	// Get the position.
	long getPosition(void);
	// Reset the position.
	void resetPosition(void);
	// Get the position and then reset it.
	long getIncrement(void);
};
