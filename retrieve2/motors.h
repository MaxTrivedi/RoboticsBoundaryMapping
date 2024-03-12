#define L_PWM_PIN 10
#define L_DIR_PIN 16
#define R_PWM_PIN 9
#define R_DIR_PIN 15

#define FWD LOW
#define REV HIGH

class Motors_c {

  public:

    int max_speed = 40;
    int min_speed = 10;
    int left_vol_now;
    int right_vol_now;
    // A class must have a special function
    // called a "constructor".  This function
    // must be named the same as the data type
    // in this case, Motor_c.  Note, there is
    // no return type, and this is how you know
    // this is the special constructor function.
    Motors_c() {

    }
    
    void init(){
        pinMode(L_PWM_PIN, OUTPUT);
        pinMode(L_DIR_PIN, OUTPUT);
        pinMode(R_PWM_PIN, OUTPUT);
        pinMode(R_DIR_PIN, OUTPUT);
        
        digitalWrite(L_PWM_PIN, LOW);
        digitalWrite(R_PWM_PIN, LOW);
        analogWrite(L_PWM_PIN, 0);
        left_vol_now = 0;
        analogWrite(R_PWM_PIN, 0);
        right_vol_now = 0;
    }

    // A function to operate the motors and stop
    // any errors in use.
    void setMotorPower( float left_pwm, float right_pwm ) {
      if ((left_pwm<min_speed && left_pwm>-min_speed) || left_pwm>max_speed || left_pwm<-max_speed){
        analogWrite(L_PWM_PIN, 0);
        left_vol_now = 0;
        analogWrite(R_PWM_PIN, 0);
        right_vol_now = 0; 
      }
      else if ((right_pwm<min_speed && right_pwm>-min_speed) || right_pwm>max_speed || right_pwm<-max_speed) {
        analogWrite(L_PWM_PIN, 0);
        left_vol_now = 0;
        analogWrite(R_PWM_PIN, 0);
        right_vol_now = 0;
      }
      else{
        if (left_pwm>0){
          digitalWrite(L_DIR_PIN, FWD);
          analogWrite(L_PWM_PIN, left_pwm);
          left_vol_now = left_pwm;
        }
        else {
          digitalWrite(L_DIR_PIN, REV);
          analogWrite(L_PWM_PIN, -left_pwm);
          left_vol_now = left_pwm;
        }
  
        if (right_pwm>0) {
          digitalWrite(R_DIR_PIN, FWD);
          analogWrite(R_PWM_PIN, right_pwm);
          right_vol_now = right_pwm;
        }
        else {
          digitalWrite(R_DIR_PIN, REV);
          analogWrite(R_PWM_PIN, -right_pwm);
          right_vol_now = right_pwm;
        }
      }
    }
};
