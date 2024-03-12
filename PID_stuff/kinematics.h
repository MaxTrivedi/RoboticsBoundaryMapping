// this #ifndef stops this file
// from being included mored than
// once by the compiler.
#ifndef _KINEMATICS_H
#define _KINEMATICS_H

// Class to track robot position.
class Kinematics_c {
  public:

    float XI;
    float YI;
    float thetaI;

    float XdotR;
    float thetadotR;

    float CPR; // counts per revolution
    float DPR; // distance per revolution
    float r; // Theoretical is 16mm
    float l; // Theoretical is ~ 42mm
    float DPC; // distance per count

    long prev_count_left;
    long prev_count_right;

    int diff_left;
    int diff_right;

    // Constructor, must exist.
    Kinematics_c() {

    }

    void initialise() {

      XI = 0.0;
      YI = 0.0;
      thetaI = 0.0;

      XdotR = 0.0;
      thetadotR = 0.0;

      CPR = 358; // counts per revolution
      DPR = 106; // distance per revolution
      r = 16.0; // Theoretical is 16mm
      l = 42; // Theoretical is ~ 40mm
      //DPC = DPR / CPR; // distance per count
      DPC = 0.29703; // experimental measurement

      prev_count_left = 0;
      prev_count_right = 0;

      diff_left = 0;
      diff_right = 0;
    }


    // Use this function to update
    // your kinematics
    void update() {

      diff_left = count_left - prev_count_left;
      diff_right = count_right - prev_count_right;

      XdotR = (DPC * diff_left) / 2.0 + (DPC * diff_right) / 2.0;
      thetadotR = (DPC * diff_left) / (2.0 * l) - (DPC * diff_right) / (2.0 * l);

      XI = XI + (XdotR * cos(thetaI));
      YI = YI + (XdotR * sin(thetaI));
      //thetaI = fmod((thetaI + thetadotR), 2.0 * PI);
      thetaI = (thetaI + thetadotR);

      prev_count_left = count_left;
      prev_count_right = count_right;

    }

};



#endif
