// this #ifndef stops this file
// from being included mored than
// once by the compiler.
#ifndef _MOTORS_H
#define _MOTORS_H

# define L_PWM_PIN 10
# define L_DIR_PIN 16
# define R_PWM_PIN 9
# define R_DIR_PIN 15

# define FWD LOW
# define REV HIGH

float biasPWM = 30.0;
float maxTurnPWM = 60.0;
float leftPWM = 0.0;
float rightPWM = 0.0;

float upp_lim = 100;
float low_lim = 0;

// Class to operate the motor(s).
class Motors_c {
  public:

    // Constructor, must exist.
    Motors_c() {

    }

    // Use this function to
    // initialise the pins and
    // state of your motor(s).
    void initialise() {
      // Set all the motor pins as outputs.
      // There are 4 pins in total to set.
      pinMode( L_PWM_PIN, OUTPUT );
      pinMode( L_DIR_PIN, OUTPUT );
      pinMode( R_PWM_PIN, OUTPUT );
      pinMode( R_DIR_PIN, OUTPUT );

      // Set initial direction (HIGH/LOW)
      // for the direction pins.
      digitalWrite( L_DIR_PIN, FWD );
      digitalWrite( R_DIR_PIN, FWD );

      // Set initial power values for the PWM
      // Pins.
      analogWrite( L_PWM_PIN, 0 );
      analogWrite( R_PWM_PIN, 0 );

    }

    // Write a function to operate
    // your motor(s)
    void setMotorPower( float left_pwm, float right_pwm ) {
      // Set direction given by sign of pwm arguments
      if (left_pwm < 0) {
        digitalWrite( L_DIR_PIN, REV );
      } else {
        digitalWrite( L_DIR_PIN, FWD );
      }

      if (right_pwm < 0) {
        digitalWrite( R_DIR_PIN, REV );
      } else {
        digitalWrite( R_DIR_PIN, FWD );
      }

      // Limit values to acceptable range
      if (abs(left_pwm) > upp_lim) {
        left_pwm = upp_lim;
      }
      if (abs(right_pwm) > upp_lim) {
        right_pwm = upp_lim;
      }
      if (abs(left_pwm) < low_lim) {
        left_pwm = low_lim;
      }
      if (abs(right_pwm) < low_lim) {
        right_pwm = low_lim;
      }


      // Set power using magnitude of pwm arguments
      analogWrite( L_PWM_PIN, abs(left_pwm) );
      analogWrite( R_PWM_PIN, abs(right_pwm) );
    }
    void driveForwards() {
      setMotorPower(20, 20);
    }


    void weightedFollow( float W) {
      leftPWM = biasPWM - (W * maxTurnPWM);
      rightPWM = biasPWM + (W * maxTurnPWM);
      setMotorPower(leftPWM, rightPWM);
    }



};



#endif
