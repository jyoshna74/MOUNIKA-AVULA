// Pin Definitions
int soilMoisturePin = A0;   // Soil moisture sensor connected to analog pin A0
int pumpRelayPin = 7;        // Relay module connected to digital pin 7

int soilMoistureValue = 0;   // Variable to store the moisture value
int moistureThreshold = 500;  // Moisture threshold (adjustable based on your needs)
int pumpDelayTime = 5000;    // Time (in milliseconds) to run the pump (e.g., 5 seconds)

void setup() {
  // Initialize the serial monitor for debugging
  Serial.begin(9600);
  
  // Set relay pin as output
  pinMode(pumpRelayPin, OUTPUT);
  
  // Initially turn off the pump
  digitalWrite(pumpRelayPin, LOW);
}

void loop() {
  // Read the soil moisture level (0 to 1023, where 0 is completely dry and 1023 is fully wet)
  soilMoistureValue = analogRead(soilMoisturePin);
  
  // Print the moisture value to the serial monitor for debugging
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilMoistureValue);
  
  // If soil moisture is below the threshold, turn on the pump
  if (soilMoistureValue < moistureThreshold) {
    Serial.println("Soil is dry. Turning on the water pump...");
    
    // Activate the water pump (Relay ON)
    digitalWrite(pumpRelayPin, HIGH);
    
    // Keep the pump on for a defined period to water the plants
    delay(pumpDelayTime);
    
    // Turn off the water pump
    digitalWrite(pumpRelayPin, LOW);
    Serial.println("Pump turned off.");
  } else {
    Serial.println("Soil is wet. No need to water.");
  }
  
  // Wait a bit before taking the next reading (optional)
  delay(10000);  // Check every 10 seconds
}
