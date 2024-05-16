#include "vex.h"

//PID constructor, takes in initial variables - starti is in degrees
Drive_PID::Drive_PID(float kp, float ki, float kd, float constant) : kp(kp), ki(ki), kd(kd), constant(constant){};

//Where the PID calculation happens
float Drive_PID::calculate(float error){
    //Initially start by returning the error * kp
    //I clamped it to make it easier to tune, no robot should take more than 12 inches to stop
    float P = clamp(error * kp, -12, 12);
    
    //Not convinced it's needed
    float I = 0;
    //if (error < starti) I = clamp(prev_i+(error*ki), -12, 12);
    
    //Calculate the derivitve 
    float D = (error - prev_error)*kd;
    prev_error = error;
    //prev_i = I;

    //Testing whether having a constant would help
    float C = 0;
    if (error > 0) C = constant;
    else C = -constant;


    return (P+I+D+C);

}

//Signal to a loop that the error is close enough
bool Drive_PID::close_enough(float degree){
    if (prev_error < degree && prev_error > 0) return true;
    if (prev_error > -degree && prev_error < 0) return true;
    return false;
}