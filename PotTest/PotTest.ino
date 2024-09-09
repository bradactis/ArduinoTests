
void setup() {
    // Start the serial communication
    Serial.begin(9600);
    // Print an initial message to the serial monitor
    Serial.println("Reading potentiometer values:");
}

void loop() {
    // Read the analog value from the potentiometer
    int potValue = analogRead(A0);
    
    // Print the potentiometer value to the serial monitor
    Serial.print("Potentiometer Value: ");
    Serial.println(potValue);
    
    // Wait for a short period before reading again
    delay(500); // Delay in milliseconds
}

