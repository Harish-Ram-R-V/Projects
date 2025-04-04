#include <Servo.h>

int movement = 0;

int height = 0;

int i = 0, j = 0;

Servo servo;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(8, OUTPUT);
  pinMode(11, OUTPUT);
  servo.attach(2, 500, 2500);
  pinMode(13, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(4, INPUT);
}

void loop()
{
  //digitalWrite(8, HIGH);
  //digitalWrite(11, LOW);
  servo.write(0);
  digitalWrite(13, HIGH);
  height = 0.01723 * readUltrasonicDistance(13, A0);
  if (height > 7) {
    digitalWrite(8, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(7, HIGH);
    movement = digitalRead(4);
    if (movement == HIGH) {
      digitalWrite(7, LOW);
      servo.write(90);
    }
    delay(1000); // Wait for 1000 millisecond(s)
    digitalWrite(7, HIGH);
    movement = digitalRead(4);
    if (movement == LOW) {
      servo.write(0);
    }
  } else {
    if (height <= 7) {
      digitalWrite(8, LOW);
      digitalWrite(11, HIGH);
      // Next Step : Send Message through GSM
    }
  }
}