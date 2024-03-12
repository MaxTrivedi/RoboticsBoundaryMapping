// this #ifndef stops this file from being included more than once by the compiler. 
#ifndef _MOTORS_H
#define _MOTORS_H
#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN 9
#define R_DIR_PIN 15
#define FWD LOW
#define REV HIGH
#define PWM_LIMIT 35

// Class to operate the motor(s).
class Motors_c {
  public:
    // Constructor, must exist.
    Motors_c() {
      }
      
    // initialise pins and motor states.
    void initialise() {
        pinMode(L_PWM_PIN, OUTPUT);
        pinMode(L_DIR_PIN, OUTPUT);
        pinMode(R_PWM_PIN, OUTPUT);
        pinMode(R_DIR_PIN, OUTPUT);
        digitalWrite(L_DIR_PIN, FWD); 
        digitalWrite(R_DIR_PIN, FWD);
    }

    void setMotorPower(float left_pwm, float right_pwm) {
        // restrict pwm value to limit
        if (left_pwm > PWM_LIMIT) left_pwm = PWM_LIMIT;
        if (left_pwm < -PWM_LIMIT) left_pwm = -PWM_LIMIT;
        if (right_pwm > PWM_LIMIT) right_pwm = PWM_LIMIT;
        if (right_pwm < -PWM_LIMIT) right_pwm = -PWM_LIMIT;

        // set direction of motors depending on sign
        digitalWrite(L_DIR_PIN, left_pwm >= 0 ? FWD : REV);
        digitalWrite(R_DIR_PIN, right_pwm >= 0 ? FWD : REV);

        // set power of motors
        analogWrite(L_PWM_PIN, abs(left_pwm));
        analogWrite(R_PWM_PIN, abs(right_pwm));
    }
};
#endif
