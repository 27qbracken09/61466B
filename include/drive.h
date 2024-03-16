//I'm going to have the header files all feed into vex.h, so we need this compiler command
#pragma once

//Inclusion of vex.h
#include "vex.h"

//Declaration of Drive class
//This allows me to create a "template" that can be easily modified by feeding it certain variables
//Sort of like a function on steroids
class Drive
{
    //Stuff in the public line can be accessed by other parts of my program, sort of like the front end of a service
    public:

        //Multiple class constructors so that I can "overload" them and have multiple argument amounts

        //6M Drive
        Drive(vex::motor motorLF, vex::motor motorLM, vex::motor motorLR, vex::motor motorRF, vex::motor motorRM, vex::motor motorRB);
        
        //4M Drive
        Drive(vex::motor motorLF, vex::motor motorLR, vex::motor motorRF, vex::motor motorRB);

        //2M Drive for whatever crazy reason
        Drive(vex::motor motorLF,vex::motor motorRF);

        //Motor groups that the motors "feed" into so they can all be controlled together
        vex::motor_group L;
        vex::motor_group R;

        //Functions that can be used to control newly constructed Drivetrain
        
        //Drive with voltage is low level access to hardware
        void drive_with_voltage(float L_volt, float R_volt);


};