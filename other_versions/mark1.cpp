/*
  Im więcej światła tym większa wartość odczytana z czujnika

  prawy fotorezystor do pinu A0
  lewy fotorezystor do pinu A1

*/

#include <Arduino.h>
#include <Servo.h>

#define servo_low_pin 5
#define servo_high_pin 3
#define photoresistor_right_pin A0 
#define photoresistor_left_pin A1

Servo servo_low;
Servo servo_high;

void setup() {
  servo_low.attach(servo_low_pin);
  servo_high.attach(servo_high_pin);
}

void loop() {
    for (int i=0;i<=180;i++) {
    servo_low.write(i);
    servo_high.write(i);
    delay(20);
  }
  for (int i=180;i>=0;i--) {
    servo_low.write(i);
    servo_high.write(i);
    delay(20);
  }
}


