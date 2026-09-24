#include <Arduino.h>
#include <Servo.h>




class SunTracker {

    /*
        pr - photoresistor
    */



public:

    // Pins
    uint8_t pr_BottomLeft_pin;
    uint8_t pr_BottomRight_pin;
    uint8_t pr_TopLeft_pin;
    uint8_t pr_TopRight_pin;

    uint8_t servo_bottom_pin;
    uint8_t servo_top_pin;


    // Values
    uint16_t pr_BottomLeft_val;
    uint16_t pr_BottomRight_val;
    uint16_t pr_TopLeft_val;
    uint16_t pr_TopRight_val;

    uint8_t servo_bottom_steer_val;
    uint8_t servo_top_steer_val;

    // Other
    const uint8_t MAX_TILT_DOWN = 90;
    const uint8_t MAX_TILT_UP = 140;


    // Objects
    Servo servo_bottom;
    Servo servo_top;




    // Constructors
    SunTracker(uint8_t pr_BottomLeft_pin,uint8_t pr_BottomRight_pin,uint8_t pr_TopLeft_pin,uint8_t pr_TopRight_pin,uint8_t servo_bottom_pin,uint8_t servo_top_pin) {
        this -> pr_BottomLeft_pin = pr_BottomLeft_pin;
        this -> pr_BottomRight_pin = pr_BottomRight_pin;
        this -> pr_TopLeft_pin = pr_TopLeft_pin;
        this -> pr_TopRight_pin = pr_TopRight_pin;

        this -> servo_bottom_pin = servo_bottom_pin;
        this -> servo_top_pin = servo_top_pin;
    }

    // Functions

    void initializeServos() {
        servo_bottom.attach(servo_bottom_pin);
        servo_top.attach(servo_top_pin);
    }
    
    void setPosition(uint8_t servo_bottom_steer_val,uint8_t servo_top_steer_val) {
        this -> servo_bottom_steer_val = servo_bottom_steer_val;
        this -> servo_top_steer_val = servo_top_steer_val;

        steerServos();
    }

    void steerServos() {
        servo_bottom.write(servo_bottom_steer_val);
        servo_top.write(servo_top_steer_val);
    }

    void trackHorizontal(int threshold,uint8_t servo_top_steer_val) {  
        /*
         using only top photoresistors.
        */

        measurePhotoresistorsValues();
        
        int error_bottom = pr_BottomLeft_val - pr_BottomRight_val;
        int error_top = pr_TopLeft_val - pr_TopRight_val;

        if (error_top > threshold || error_bottom > threshold) {
            if (servo_bottom_steer_val > 0) {
                servo_bottom_steer_val -= 1;
            }
        } else if (error_top < -threshold || error_bottom < -threshold) {
            if (servo_bottom_steer_val < 180) {
                servo_bottom_steer_val += 1;
            }
        }

        // saving photoresistors values to suntracker variables
        //this -> servo_bottom_steer_val = servo_bottom_steer_val;
        this -> servo_top_steer_val = servo_top_steer_val;

        steerServos();

    }

    void trackDualAxis(int threshold) {

        measurePhotoresistorsValues();

        // horizontal
        int error_bottom = pr_BottomLeft_val - pr_BottomRight_val;
        int error_top = pr_TopLeft_val - pr_TopRight_val;

        if (error_top > threshold || error_bottom > threshold) {
            if (servo_bottom_steer_val > 0) {
                servo_bottom_steer_val -= 1;
            }
        } else if (error_top < -threshold || error_bottom < -threshold) {
            if (servo_bottom_steer_val < MAX_TILT_UP) {
                servo_bottom_steer_val += 1;
            }
        }

        // vertical
        int error_left = pr_BottomLeft_val - pr_TopLeft_val;
        int error_right = pr_BottomRight_val - pr_TopRight_val;

        if (error_left > threshold || error_right > threshold) {
            if (servo_top_steer_val > MAX_TILT_DOWN) {
                servo_top_steer_val -= 1;
            }
        } else if (error_left < -threshold || error_right < -threshold) {
            if (servo_top_steer_val < MAX_TILT_UP) {
                servo_top_steer_val += 1;
            }
        }

        steerServos();
    }


    void measurePhotoresistorsValues() {
        pr_BottomLeft_val = analogRead(pr_BottomLeft_pin);
        pr_BottomRight_val = analogRead(pr_BottomRight_pin);
        pr_TopLeft_val = analogRead(pr_TopLeft_pin);
        pr_TopRight_val = analogRead(pr_TopRight_pin);
    }
    uint16_t getPhotoresistorsValues() {
        measurePhotoresistorsValues();
        return pr_BottomLeft_val, pr_BottomRight_val, pr_TopLeft_val, pr_TopRight_val;
    }

    void infoPrint() {
        Serial.print(">Top Left:");
        Serial.println(pr_TopLeft_val);

        Serial.print(">Top Right:");
        Serial.println(pr_TopRight_val);

        Serial.print(">Bottom Left:");
        Serial.println(pr_BottomLeft_val);

        Serial.print(">Bottom Right:");
        Serial.println(pr_BottomRight_val);

        Serial.print(">Servo bottom steer value:");
        Serial.println(servo_bottom_steer_val);

        Serial.print(">Servo top steer value:");
        Serial.println(servo_top_steer_val);

    }
};




















