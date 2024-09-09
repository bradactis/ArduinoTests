#include "HX711.h"

// Define the pins connected to HX711 module
const int LOADCELL_DOUT_PIN = 5;  // DT pin on HX711 to pin 3 on Arduino
const int LOADCELL_SCK_PIN = 4;   // SCK pin on HX711 to pin 2 on Arduino

HX711 scale;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize the HX711 scale
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  // Set the scale calibration factor (adjust this based on your setup)
  scale.set_scale(2280.f);  // Adjust this value according to your load cell's calibration factor
  scale.tare();  // Reset the scale to zero
}

void loop() {
  // Read the weight from the load cell
  float weight = scale.get_units(5);  // Read average of 5 readings

  // Print the weight to the Serial Monitor
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" kg");  // Assuming you calibrated for kilograms

  // Pause for a bit before taking another reading
  delay(100);
}

