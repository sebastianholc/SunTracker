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

        servo_bottom.attach(servo_bottom_pin);
        servo_top.attach(servo_top_pin);
    }

    // Functions
    void setPosition(uint8_t servo_bottom_steer_val,uint8_t servo_top_steer_val) {
        this -> servo_bottom_steer_val = servo_bottom_steer_val;
        this -> servo_top_steer_val = servo_top_steer_val;

        servo_bottom.write(this -> servo_bottom_steer_val);
        servo_top.write(this -> servo_top_steer_val);
    }

    void trackHorizontal(int threshold,uint8_t servo_top_steer_val) {  
        /*
         using both pairs of photoresistors for more precise measurment.
         steering only bottom servo.
        */

        measurePhotoresistorsValues();
        
        int error_bottom = pr_BottomLeft_val - pr_BottomRight_val;
        int error_top = pr_TopLeft_val - pr_TopRight_val;

        int error_final = (error_bottom + error_top) / 2;

        if (error_final > threshold) {
            servo_bottom_steer_val += 1;
        } else if (error_final < -threshold) {
            servo_bottom_steer_val -= 1;
        }

        if (servo_bottom_steer_val > 180) {servo_bottom_steer_val = 180;}
        else if (servo_bottom_steer_val < 0) {servo_bottom_steer_val = 0;}

        // Steering with calculated value
        servo_bottom.write(servo_bottom_steer_val);
        this->servo_top_steer_val = servo_top_steer_val;
        servo_top.write(servo_top_steer_val);

    }
    void trackDualAxis() {

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


};




















