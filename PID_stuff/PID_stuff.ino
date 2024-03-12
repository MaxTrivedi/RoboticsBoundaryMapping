# include "motors.h"
# include "linesensor.h"
# include "encoders.h"
# include "kinematics.h"
# include "pid.h"

// create instance of motor and linesensor classes
LineSensor_c line_sensors;
Motors_c motors;
Kinematics_c kinematics;
PID_c spd_pid_left;
PID_c spd_pid_right;
PID_c heading_pid;

unsigned long start_time;
unsigned long end_time;
unsigned long elapsed_time;

unsigned long update_ts; // timestamp

unsigned long pid_test_ts;

long prev_count_left;
long prev_count_right;

float ave_spd_left;
float ave_spd_right;

float demand;

void setup() {

  // setup line sensors, motors and encoders
  line_sensors.initialise();
  motors.initialise();
  setupEncoder0();
  setupEncoder1();

  // setup kp, ki, kd
  spd_pid_left.initialise(100 , 0.5, -100);
  spd_pid_right.initialise(100 , 0.5, -100);
  heading_pid.initialise(1 , 0, -1);

  // Configure the Serial port
  Serial.begin(9600);
  delay(2000);
  Serial.println("***RESET***");

  update_ts = millis();

  prev_count_left = count_left;
  prev_count_right = count_right;
  
  motors.setMotorPower(0, 0);

  ave_spd_left = 0.0;
  ave_spd_right = 0.0;

  demand = 1.0;

  spd_pid_left.reset();
  spd_pid_right.reset();
  heading_pid.reset();
  
  pid_test_ts = millis();
}

void loop() {

  unsigned long elapsed;

  elapsed = millis() - update_ts;

  if (elapsed > 20) {
    update_ts = millis();

    long diff_left; // difference in encoder count
    float speed_left; // speed calculated for left encoder

    long diff_right; // difference in encoder count
    float speed_right; // speed calculated for left encoder

    diff_left = count_left - prev_count_left;
    diff_right = count_right - prev_count_right;
    prev_count_left = count_left;
    prev_count_right = count_right;
    
    // encoder counts per ms
    speed_left = (float)diff_left;
    speed_left /= (float)elapsed;
    speed_right = (float)diff_right;
    speed_right /= (float)elapsed;
    
    // low pass filtered speed
    ave_spd_left = (ave_spd_left * 0.7) + (speed_left * 0.3);
    ave_spd_right = (ave_spd_right * 0.7) + (speed_right * 0.3);

    /*
      Serial.print( speed_left * 100 );
      Serial.print(",");
      Serial.print( ave_spd_left * 100 );
      Serial.print("\n");
    */

    float heading_feedback;
    float pwm_l;
    float pwm_r;

    line_sensors.updateSensors();
    W = line_sensors.weightedMeasurement();
    heading_feedback = heading_pid.update(W , 0);

    pwm_l = spd_pid_left.update(ave_spd_left, 1 + heading_feedback);
    pwm_r = spd_pid_right.update(ave_spd_right, 1 - heading_feedback);

    
    motors.setMotorPower(pwm_l, pwm_r);

    Serial.print( W );
    Serial.print(",");
    Serial.print( heading_feedback );
    Serial.print(",");
    //Serial.print( pwm_l );
    //Serial.print(",");
    //Serial.print( pwm_r );
    Serial.print("\n");
    

    
  }
  
  
  if ( millis() - pid_test_ts > 4000) {
    pid_test_ts = millis();

    //demand = demand * -1;
    demand = 0;
  }
    
  /*
  kinematics.update();
  Serial.print(kinematics.XI);
  Serial.print(",");
  Serial.print(kinematics.YI);
  Serial.print(",");
  Serial.print(kinematics.thetaI);
  Serial.print("\n");
  */

}
