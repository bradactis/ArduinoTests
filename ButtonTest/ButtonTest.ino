const int buttonPin = 8;  // Pin connected to the button

void setup() {
  // Initialize the button pin as an input with an internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the state of the button
  int buttonState = digitalRead(buttonPin);

  // Check if the button is pressed (buttonState will be LOW when pressed)
  if (buttonState == LOW) {
    // Button is pressed, take some action
    Serial.println("Button is pressed!" + String(buttonState));
  } else {
    // Button is not pressed
    Serial.println("Button is not pressed" + String(buttonState));
  }

  // Wait a bit before checking again
  delay(100);  // 100 milliseconds
}

