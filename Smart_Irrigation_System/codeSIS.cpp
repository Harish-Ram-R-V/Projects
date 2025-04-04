#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define the pins for the motor control
int enA = 5;  // Enable pin for the L293D motor driver
int in1 = 3;  // Input pin 1 for the L293D motor driver
int in2 = 4;  // Input pin 2 for the L293D motor driver

LiquidCrystal_I2C lcd(32,16,2);

// Define the pins for the sensors
int tempPin = A1;     // Temperature sensor is connected to A1
int lightPin = A2;    // Light sensor is connected to A2
int moisturePin = A0; // Soil moisture sensor is connected to A0

void setup() {
 // Initialize the Serial Monitor
  lcd.begin(16,2);
	lcd.init();
	lcd.backlight();
	Serial.begin(9600);

  
  // Set the motor control pins as outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
  // Read the sensor values
  int tempValue = analogRead(tempPin);
  int lightValue = analogRead(lightPin);
  int moistureValue = analogRead(moisturePin);

  // Convert the sensor values to their corresponding units
  float temp = (((tempValue * 5.0) / 1024.0)-0.5)*100;
  float light = (lightValue * 5.0) / 1024.0;
  float moisture = (moistureValue * 5.0) / 1024.0;


  Serial.print("Temp ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.print("Light:");
  Serial.print(light);
  Serial.println("V");
  Serial.print("Moist: ");
  Serial.print(moisture);
  Serial.println("V");
   
   // Display the sensor values on the LCD screen
  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0); // Set the cursor to the top-left corner
  lcd.print("Temp:"); // Print the temperature label
  lcd.print(temp); // Print the temperature value
  lcd.print("C"); // Print the temperature unit
  lcd.setCursor(0, 1); // Set the cursor to the second row
  lcd.print("Light:"); // Print the light label
  lcd.print(light); // Print the light value
  lcd.print("V"); // Print the light unit
  lcd.setCursor(8, 1); // Set the cursor to the second row, ninth column
  lcd.print("Moist:"); // Print the moisture label
  lcd.print(moisture); // Print the moisture value
  lcd.print("V"); // Print the moisture unit

  // Control the motor based on the sensor readings
  if((temp > 30 || light < 2)&& moisture < 4 ) {
    // If it's hot, the soil is dry, and it's morning, turn on the motor
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, 255); // Set the motor speed to maximum
    Serial.println("Turning on the motor...");
  } else {
    // Otherwise, turn off the motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA, 0); // Set the motor speed to 0
    Serial.println("Turning off the motor...");
  }

  // Wait for 1 second before taking another reading
  delay(1000);
}