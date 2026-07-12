/*
  Im więcej światła tym większa wartość odczytana z czujnika

  prawy fotorezystor do pinu A0
  lewy fotorezystor do pinu A1

*/

#include <Arduino.h>
#include <Servo.h>

#define servo_pin 3
#define photoresistor_right_pin A0 
#define photoresistor_left_pin A1

Servo servo;
int steerValue = 90;

void servoSweep(Servo &servo, int degree, int delay_);
int servoSunTracking(int valueL, int valueR, int threshold = 200);

void setup() {
  servo.attach(servo_pin);
  
  Serial.begin(115200);
}

void loop() {

  int valueL = analogRead(photoresistor_left_pin);
  int valueR = analogRead(photoresistor_right_pin);

  //int steerValue = servoSunTracking(valueL,valueR);
  //servo.write(steerValue);

  servoSweep(servo,180,10);


  Serial.print(">Right:");
  Serial.println(valueR);

  Serial.print(">Left:");
  Serial.println(valueL);

  Serial.print(">steerValue:");
  Serial.println(steerValue);

  delay(50);

}

void servoSweep(Servo &servo,int degree,int delay_) {
  for (int i=0;i<=degree;i++) {
    servo.write(i);
    delay(delay_);
  }
  for (int i=degree;i>=0;i--) {
    servo.write(i);
    delay(delay_);
  }
}

int servoSunTracking(int valueL, int valueR, int threshold) {
  int error = valueL - valueR;

  if (error > threshold) {
    steerValue += 1;
  } else if (error < -threshold) {
    steerValue -= 1;
  }

  if (steerValue > 180) {steerValue = 180;}
  else if (steerValue < 0) {steerValue = 0;}

  return steerValue;
}