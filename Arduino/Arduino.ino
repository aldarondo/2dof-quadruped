#include <Servo.h>

#define MODE_MANUAL 1
#define MODE_FORWARD 2

const byte mode = MODE_MANUAL;

const boolean debugMode = false;

#define DELAY_STEP 20

void setup()
{
	Serial.begin(9600);
	setupServos();

	delay(1000);
	if (debugMode)
	{
		Serial.println("Ready to party!");
	}
}

void loop()
{
	switch (mode)
	{
		case MODE_MANUAL:
			modeManual();
			break;
		case MODE_FORWARD:
			modeForward();
			break;
	}
}

