#include "encoders.h"
// this #ifndef stops this file
// from being included mored than
// once by the compiler. 
#ifndef _KINEMATICS_H
#define _KINEMATICS_H

// Class to track robot position.
class Kinematics_c {
  public:
    
    long counter = 0;
    long period = 1;//10;
    long prev[2] = {0, 0};
    long change[2] = {0, 0};

    int r = 16;
    float l = 42.5;
    float Xt = 0;
    float Yt = 0;
    float Ot = 0;
    float rotation = 358.3;
    float pi = 3.1415926535897932384626433832795;
    
    // Constructor, must exist.
    Kinematics_c() {

    } 

    void update() {
        if (counter >= period) {
            change[0] = count_e1-prev[0];
            change[1] = count_e0-prev[1];
            counter = 0;
            prev[0] = count_e1;
            prev[1] = count_e0;

            float Ol = 2*pi*change[0]/rotation;
            float Or = 2*pi*change[1]/rotation;
            float dXrdt = (r*Ol)/2 + (r*Or)/2;
            float dOrdt = (r*Ol)/(2*l) - (r*Or)/(2*l);
        
            Xt = Xt + dXrdt*cos(Ot);
            Yt = Yt + dXrdt*sin(Ot);
            // Reset Ot if >2pi
            Ot = Ot + dOrdt;
        }
        else {
            counter++;
        }
    }

};



#endif
