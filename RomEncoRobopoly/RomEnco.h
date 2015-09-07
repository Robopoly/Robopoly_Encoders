
#include <Arduino.h>


class RomEnco
{
private:
	static const bool _debug;
	static const uint8_t _debugPin;

	static uint8_t _encoderAmount;
	static uint8_t _pinA, _pinB;
	static volatile uint8_t _pinAState, _pinBState,
		_oldPinAState, _oldPinBState;
	static volatile int _position;

	void _SetupTimer4(void);

public:
	RomEnco(uint8_t pinA, uint8_t pinB);
	~RomEnco();

	static void update(void);
	int getPosition(void);
};
