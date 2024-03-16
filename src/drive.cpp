//All header files feed through vex.h
#include "vex.h"

//Along with the overloaded constructors in drive.h, we need all three here as well

//6M Drive
Drive::Drive(vex::motor motorLF, vex::motor motorLM, vex::motor motorLR, vex::motor motorRF, vex::motor motorRM, vex::motor motorRB) : L(motorLF,motorLM,motorLR), R(motorRF, motorRM, motorRB){
   

}

//4M Drive
Drive::Drive(vex::motor motorLF, vex::motor motorLR, vex::motor motorRF, vex::motor motorRB) : L(motorLF,motorLR), R(motorRF,motorRB){
   

}

//2M Drive for crazy people
Drive::Drive(vex::motor motorLF, vex::motor motorRF ) : L(motorLF), R(motorRF){
   

}

//Low level access to hardware
void Drive::drive_with_voltage(float L_volt, float R_volt){
    L.spin(vex::forward,L_volt,vex::volt);
    R.spin(vex::forward,R_volt,vex::volt);
}


/* Started Drive Class by figuring out the most simple way to control the robot, and plan to build from there.
   The three levels of drive complexity is voltage controlled, driver controlled, and program controlled */