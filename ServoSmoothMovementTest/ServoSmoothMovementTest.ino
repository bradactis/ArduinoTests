#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create an instance of the PWM servo driver
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Define servo settings
#define SERVOMIN  150 // Minimum pulse length (out of 4096)
#define SERVOMAX  537.5 // Maximum pulse length (out of 4096)
#define SERVOMIN_ANGLE 0
#define SERVOMAX_ANGLE 155
#define SERVO_FREQ 60  // Servo frequency

const float angularResolution = 0.0174533; // about 1 deg

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~60 Hz update rate
  delay(1000);
  pwm.setPWM(0, 0, 0);
}

void loop() {

  if (Serial.available() > 0) {
    String newPos = Serial.readStringUntil('\n');

    newPos.trim();

    int commaIndex = newPos.indexOf(',');

    float newAngle = newPos.substring(0, commaIndex).toFloat();

    float newDist = newPos.substring(commaIndex + 1).toFloat();

    Serial.println("Your input: " + String(newAngle) + " : "  + String(newDist));

    moveMotor (newAngle, newDist);

  }

  // Pause before the next cycle
  delay(25);
}

void moveMotor (float newAngle, float dist) {

  /**
  FROM GODOT
  
  var velocity = snapped((dist + .5)**2, .01)
	#set max velocity
	if (velocity > 3):
		velocity = 3
  **/

  //rads/s
  float angularVelocity = pow(dist + .5, 2);
  if (angularVelocity > 3) {
    angularVelocity = 3;
  }

  float delayTime = (angularResolution / angularVelocity) * 1000;

  // Move servo smoothly to the target position
  for (int position = 0; position <= (newAngle * 180.0/PI); position += int(angularResolution * (180.0/PI))) {
    int pulseLength = map(position, SERVOMIN_ANGLE, SERVOMAX_ANGLE, SERVOMIN, SERVOMAX);
    pwm.setPWM(0, 0, pulseLength);
    delay(delayTime);  // Adjust this to control the speed
  }

  delay(1000);

    // Move servo smoothly to the target position
  for (int position = (newAngle * 180.0/PI); position >= 0; position -= int(angularResolution * (180.0/PI))) {
    int pulseLength = map(position, SERVOMIN_ANGLE, SERVOMAX_ANGLE, SERVOMIN, SERVOMAX);
    pwm.setPWM(0, 0, pulseLength);
    delay(delayTime);  // Adjust this to control the speed
  }

  Serial.println(delayTime);

}

