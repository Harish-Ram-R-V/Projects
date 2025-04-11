//RF TRANSCEIVER CODE

#include <RH_ASK.h> // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h> // Include dependant SPI Library
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
 
void setup()
{
  // Initialize ASK Object
  rf_driver.init();
  // Setup Serial Monitor
  Serial.begin(9600);
}
 
void loop()
{
  const char *msg;
  Serial.println("DO YOU WANT MOTOR TO RUN? (ONE/ZERO): ");
  while (Serial.available ()!=0) {
  String msg = Serial.readString();
  };
  
  rf_driver.send((char *)msg, msg);

  rf_driver.waitPacketSent();
  {
  // Message Transmitted
  Serial.println("Message Transmitted! ");
  delay(1000);
  }
}