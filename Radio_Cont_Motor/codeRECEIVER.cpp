//RF RECEIVER CODE

#include <RH_ASK.h> // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h> // Include dependant SPI Library
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
int SpeedVal = 0;
void setup()
{
  // Initialize ASK Object
  rf_driver.init();
  // Setup Serial Monitor
  Serial.begin(9600);
  //Setup pins for motor driver
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
}
  
void loop()
{
  // Set buffer to size of expected message
  char buf[11];
  uint8_t buflen = sizeof(buf);
  // Check if received packet is correct size
  if (rf_driver.recv(buf, &buflen))
  {
  // Message received with valid che-cksum
  Serial.print("Message Received: ");
  Serial.println((char*)buf);
  }
  char msg = buf;
  //Makes the motor rotate to stop rotating if so.
  if(buf == "ZERO"){
    digitalWrite(3, LOW);
    SpeedVal = 0;
    analogWrite(2,SpeedVal);
  }
  
  //Makes the motor rotate in the clockwise direction. 
  else if(buf == "ONE"){
    digitalWrite(3, LOW); 
    SpeedVal = 200;
    analogWrite(2,SpeedVal);
  }
}