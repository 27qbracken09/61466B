//Standard Header stuff to allow for everything to feed through vex.h
#pragma once
#include "vex.h"

//I put this in a class so that it can store data, the kP, kI, and kD terms
class Drive_PID
{
    public:
        //Declare PID Object - startd in inches
        Drive_PID(float kp, float ki, float kd, float constant);

        //Start with P, then move on to I, then D
        float calculate(float error);

        //To tell external loops when they should exit
        bool close_enough(float degree);
        
    
    private:
        float kp;
        float ki;
        float kd;
        float prev_error = 0;
        float starti = 0;
        float constant = 2;
        float prev_i = 0;


};

