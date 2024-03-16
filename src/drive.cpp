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
