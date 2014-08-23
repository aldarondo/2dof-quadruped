#include <Servo.h>

//////////////////////////////////////////////////////////////////////////
//
// Constants used by the servos (time delay and angle defaults)
//
//////////////////////////////////////////////////////////////////////////

#define SERVO_DELAY_STEP 20
#define SERVO_ANGLE_MINIMUM 20
#define SERVO_ANGLE_MIDDLE 100
#define SERVO_ANGLE_MAXIMUM 180

//////////////////////////////////////////////////////////////////////////
//
//  The following are to control the quantity of servos attached, which
//  pins they are attached to, and preset position.
//
//////////////////////////////////////////////////////////////////////////

#define SERVOS 8

#define PIN_LEG_LEFT_BACK_HIP 4
#define PIN_LEG_LEFT_BACK_KNEE 5
#define PIN_LEG_LEFT_FRONT_KNEE 6
#define PIN_LEG_LEFT_FRONT_HIP 7
#define PIN_LEG_RIGHT_FRONT_HIP 8
#define PIN_LEG_RIGHT_FRONT_KNEE 9
#define PIN_LEG_RIGHT_BACK_KNEE 10
#define PIN_LEG_RIGHT_BACK_HIP 11

const byte SERVO_PINS[SERVOS] = {PIN_LEG_LEFT_BACK_HIP,
												 PIN_LEG_LEFT_BACK_KNEE,
												 PIN_LEG_LEFT_FRONT_KNEE,
												 PIN_LEG_LEFT_FRONT_HIP,
												 PIN_LEG_RIGHT_FRONT_HIP,
												 PIN_LEG_RIGHT_FRONT_KNEE,
												 PIN_LEG_RIGHT_BACK_KNEE,
												 PIN_LEG_RIGHT_BACK_HIP};
byte SERVO_POSITION_START[SERVOS] = {SERVO_ANGLE_MIDDLE, SERVO_ANGLE_MINIMUM, SERVO_ANGLE_MAXIMUM, SERVO_ANGLE_MIDDLE, SERVO_ANGLE_MIDDLE, SERVO_ANGLE_MINIMUM, SERVO_ANGLE_MAXIMUM, SERVO_ANGLE_MIDDLE };

//////////////////////////////////////////////////////////////////////////
//
// Unique elements to this project, rest of code is copied from acc-common
//
//////////////////////////////////////////////////////////////////////////

#define ANGLE_STEP 10
#define ANGLE_MINIMUM 20
#define ANGLE_KNEE_1 20
#define ANGLE_HIP_0 60
#define ANGLE_HIP_1 80
#define ANGLE_MIDDLE 100
#define ANGLE_HIP_2 130
#define ANGLE_HIP_3 150
#define ANGLE_KNEE_2 180
#define ANGLE_MAXIMUM 180

#define LEG_LEFT_BACK_HIP 0
#define LEG_LEFT_BACK_KNEE 1
#define LEG_LEFT_FRONT_KNEE 2
#define LEG_LEFT_FRONT_HIP 3
#define LEG_RIGHT_FRONT_HIP 4
#define LEG_RIGHT_FRONT_KNEE 5
#define LEG_RIGHT_BACK_KNEE 6
#define LEG_RIGHT_BACK_HIP 7

// LEFT BACK
const int LEG_LEFT_BACK_HIP_BACK = ANGLE_HIP_3;
const int LEG_LEFT_BACK_HIP_FORWARD = ANGLE_HIP_1;

const int LEG_LEFT_BACK_KNEE_UP = ANGLE_MIDDLE;
const int LEG_LEFT_BACK_KNEE_DOWN = ANGLE_KNEE_1;
//

// LEFT FRONT
const int LEG_LEFT_FRONT_KNEE_UP = ANGLE_MIDDLE;
const int LEG_LEFT_FRONT_KNEE_DOWN = ANGLE_KNEE_2;

const int LEG_LEFT_FRONT_HIP_BACK = ANGLE_HIP_2;
const int LEG_LEFT_FRONT_HIP_FORWARD = ANGLE_HIP_0;
//

// RIGHT FRONT
const int LEG_RIGHT_FRONT_HIP_BACK = ANGLE_HIP_1;
const int LEG_RIGHT_FRONT_HIP_FORWARD = ANGLE_HIP_3;

const int LEG_RIGHT_FRONT_KNEE_UP = ANGLE_MIDDLE;
const int LEG_RIGHT_FRONT_KNEE_DOWN = ANGLE_KNEE_1;
//

// RIGHT BACK
const int LEG_RIGHT_BACK_KNEE_UP = ANGLE_MIDDLE;
const int LEG_RIGHT_BACK_KNEE_DOWN = ANGLE_KNEE_2;

const int LEG_RIGHT_BACK_HIP_BACK = ANGLE_HIP_0;
const int LEG_RIGHT_BACK_HIP_FORWARD = ANGLE_HIP_2;
//

byte POSITION_STAND_STRAIGHT[SERVOS] = {ANGLE_MIDDLE, ANGLE_MINIMUM, ANGLE_MAXIMUM, ANGLE_MIDDLE, ANGLE_MIDDLE, ANGLE_MINIMUM, ANGLE_MAXIMUM, ANGLE_MIDDLE };
byte POSITION_FALL_DOWN[SERVOS] = {ANGLE_MIDDLE, ANGLE_MIDDLE, ANGLE_MIDDLE, ANGLE_MIDDLE, ANGLE_MIDDLE, ANGLE_MIDDLE, ANGLE_MIDDLE, ANGLE_MIDDLE };

//////////////////////////////////////////////////////////////////////////
//
// State variables for the servos
//
//////////////////////////////////////////////////////////////////////////

byte servoTargetPosition[SERVOS];
byte servoCurrentPosition[SERVOS];
Servo servoObjects[SERVOS];

//////////////////////////////////////////////////////////////////////////
//
// Wrapper to set single target position
//
//////////////////////////////////////////////////////////////////////////

void setTargetPosition(byte servo, byte position)
{
	servoTargetPosition[servo] = position;
}

//////////////////////////////////////////////////////////////////////////
//
// Wrapper to set all target positions
//
//////////////////////////////////////////////////////////////////////////

void setTargetPosition(byte listOfPositions[])
{
	memcpy(listOfPositions, servoTargetPosition, SERVOS);
}

//////////////////////////////////////////////////////////////////////////
//
// Sets starting position of servos
//
//////////////////////////////////////////////////////////////////////////

void setupServos()
{
  setTargetPosition(SERVO_POSITION_START);

	for (int i=0; i < SERVOS; i++) {
		servoObjects[i].attach(SERVO_PINS[i]);
		delay(SERVO_DELAY_STEP);
		servoObjects[i].write(servoTargetPosition[i]);
		delay(SERVO_DELAY_STEP);
		servoCurrentPosition[i] = servoTargetPosition[i];
	}

	if (debugMode)
	{
		Serial.println("To control servo(s), enter angle and letter starting with a for the first servo (eg: 100a).");
		Serial.println("To add delay between commands, enter a space before your next command.");
		Serial.println("Angle of motion restricted from " + String(SERVO_ANGLE_MINIMUM) + " to " + String(SERVO_ANGLE_MAXIMUM) + " degrees inclusive.");
	}
}

//////////////////////////////////////////////////////////////////////////
//
// Reads the serial port converting characters into either a position,
// a delay, or writing the position to the servo desired.
//
//////////////////////////////////////////////////////////////////////////

void manualServos()
{
	static int pos = 0;
  if (Serial.available()) {
    char ch = Serial.read();
    
    if (isDigit(ch)) {
      pos = pos * 10 + ch - '0';
    } else if (ch == ' ') {
      delay(SERVO_DELAY_STEP);
    } else if (ch >= 'a' && ch <= 'a' + SERVOS) {
		  if (pos >= SERVO_ANGLE_MINIMUM && pos <= SERVO_ANGLE_MAXIMUM)
			{
        servoObjects[ch - 'a'].write(pos);
  			servoCurrentPosition[ch - 'a'] = pos;
			}
      pos = 0;
    }
  }
}

//////////////////////////////////////////////////////////////////////////
//
// Move in steps to target position for all servos
//
//////////////////////////////////////////////////////////////////////////

void moveToTarget(int numberOfSteps)
{
	for (int step = 0; step < numberOfSteps; step++)
	{
		for (int s = 0; s < SERVOS; s++) {
			servoCurrentPosition[s] = servoCurrentPosition[s] + ((servoTargetPosition[s] - servoCurrentPosition[s]) / numberOfSteps);
			servoObjects[s].write(servoCurrentPosition[s]);
			delay(SERVO_DELAY_STEP);
		}
	}
}
