#include "Servo.h"

int servo_pin=9, pot_pin=A0;
int potval;
int angle;
Servo servo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(servo_pin);
}

void loop() {
  // put your main code here, to run repeatedly:
  potval=analogRead(pot_pin);
  Serial.print("Potentiometer:");
  Serial.println(potval);

  angle=map(potval, 0, 1023, 0, 179);
  servo.write(angle);
  delay(200);
}
