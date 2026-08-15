#include "SunTracker.h"

SunTracker suntracker(A0,A1,A2,A3,5,3);

void setup() {
  Serial.begin(115200);
  suntracker.initializeServos();
  
  
}

void loop() {

  // threshold = 200, top servo value = 120
  suntracker.trackHorizontal(200,120);
  

  Serial.print(">Top Left:");
  Serial.println(suntracker.pr_TopLeft_val);

  Serial.print(">Top Right:");
  Serial.println(suntracker.pr_TopRight_val);

  Serial.print(">Servo steer value:");
  Serial.println(suntracker.servo_bottom_steer_val);
  
  

  delay(100);
}


