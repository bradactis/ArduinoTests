#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // Minimum pulse length (out of 4096)
#define SERVOMAX  537.5 // Maximum pulse length (out of 4096)
#define SERVOMIN_ANGLE 0
#define SERVOMAX_ANGLE 155

int currentServoPosDeg = 1;


//start in the sleep mode
char state = 'z';

void setup() {
    //start serial comms
    Serial.begin(9600);

    //Wake up servo
    pwm.begin();
    pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
    delay(500); // Let the servo initialize

    //set servo actual pos to global servo pos
    setServoPosition(0, currentServoPosDeg);
}

void loop() {
  if (Serial.available() > 0) {
    String incomingString = Serial.readStringUntil("\n");
    Serial.println("Your Command: " + String(incomingString));
    state = incomingString[0];
    printMenuToSerial();
  }
  
  //STATES

  //Play or activate
  if (state == 'a') {
    //Active mode
  }

  //step forward 5 deg
  if (state == 'f') {
    if (currentServoPosDeg > SERVOMIN_ANGLE) {
      currentServoPosDeg += 5;
      setServoPosition(0, currentServoPosDeg);
      state = 'a';
    }
  }

  //step backward 5 deg
  if (state == 'b') {
    if (currentServoPosDeg < SERVOMAX_ANGLE) {
      currentServoPosDeg += -5;
      setServoPosition(0, currentServoPosDeg);
      state = 'a';
    }
  }

  //Deactive, prep for shut down
  if (state == 'z') {
    if (currentServoPosDeg != 1) {
      currentServoPosDeg = 1;
      setServoPosition(0, currentServoPosDeg);
    }    
  }
  
  
  delay(50); // Delay in milliseconds
}

//SET SERVO POS
void setServoPosition(uint8_t servonum, int angle) {
    int pulseLength = map(angle, SERVOMIN_ANGLE, SERVOMAX_ANGLE, SERVOMIN, SERVOMAX);
    pwm.setPWM(servonum, 0, pulseLength);
}

void printMenuToSerial () {
  Serial.println("Current mode: " + String(state) + "\n");
  Serial.println("States:");
  Serial.println(" a  -  Active");
  Serial.println(" f  -  Jog +5 deg");
  Serial.println(" b  -  Jog -5 deg");
  Serial.println(" z  -  Sleep/Prep offline");
}









