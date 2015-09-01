
#include <Arduino.h>

namespace rer
{
	typedef enum {S1, S2, S3, S4} State;
}

class RomEnco
{
	private:

		static uint8_t _encoderAmount;
		rer::State _state;
		uint8_t _pinA;

		void _setupInterrupt(void);

	public:

		RomEnco(uint8_t pinA, uint8_t pinB);
		~RomEnco();

		int16_t getPosition(void);
};
