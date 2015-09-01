
#include <Arduino.h>

namespace rer
{
	enum Quarter {Q1, Q2, Q3, Q4};
}

class RomEnco
{
private:
	static uint8_t _encoderAmount;
	volatile rer::Quarter _lastQuarter;
	volatile rer::Quarter _currentQuarter;
	static volatile uint8_t _pinA, _pinB;
	static volatile uint8_t _ledState;

	void _SetupTimer4(void);

public:
	RomEnco(uint8_t pinA);
	~RomEnco();

	static void _Update(void);
	int16_t getPosition(void);
};
