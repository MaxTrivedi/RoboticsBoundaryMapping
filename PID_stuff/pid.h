// this #ifndef stops this file
// from being included mored than
// once by the compiler.
#ifndef _PID_H
#define _PID_H

// Class to contain generic PID algorithm.
class PID_c {
  public:

    float feedback;
    float p_term;
    float i_term;
    float d_term;
    float i_sum;

    float p_gain;
    float i_gain;
    float d_gain;

    float last_error;
    unsigned long ms_last_ts;


    // Constructor, must exist.
    PID_c() {

    }

    void initialise(float kp, float ki, float kd) {
      feedback = 0;
      last_error = 0;
      p_term = 0;
      i_term = 0;
      d_term = 0;
      i_sum = 0;

      p_gain = kp;
      i_gain = ki;
      d_gain = kd;

      ms_last_ts = millis();
    }

    void reset() {
      feedback = 0;
      p_term = 0;
      i_term = 0;
      d_term = 0;
      i_sum = 0;
      last_error = 0;
      ms_last_ts = millis();

    }

    float update(float measurement, float demand) {
      float error;
      unsigned long ms_now_ts;
      unsigned long ms_dt;
      float float_dt;
      float diff_error;

      ms_now_ts = millis();
      ms_dt = ms_now_ts - ms_last_ts;
      ms_last_ts = millis();

      float_dt = (float)ms_dt;
      if (float_dt == 0 ) return feedback;
      
      error = demand - measurement;

      p_term = error * p_gain;

      i_sum = i_sum + (error * float_dt);
      i_term = i_gain * i_sum;

      diff_error = (error - last_error) / float_dt;
      last_error = error;
      d_term = diff_error * d_gain;

    
      feedback = p_term + i_term + d_term;

      return feedback;
    }

};



#endif
