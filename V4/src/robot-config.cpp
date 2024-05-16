#include "vex.h"



using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors

motor intake = motor(PORT2, true);
digital_out descorer = digital_out(Brain.ThreeWirePort.A);



// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  //Intake Controls - R1 is forward, R2 is back
 controller(primary).ButtonR1.pressed(buttonR1pressed);
 controller(primary).ButtonR1.released(buttonR1released);
 controller(primary).ButtonR2.pressed(buttonR2pressed);
 controller(primary).ButtonR2.released(buttonR2released);

/*
  //Catapult Controls - L1 is down, L2 is up(and sets hold to coast)
 controller(primary).ButtonL1.pressed(buttonL1pressed);
 controller(primary).ButtonL1.released(buttonL1released);
 controller(primary).ButtonL2.pressed(buttonL2pressed);
 controller(primary).ButtonL2.released(buttonL2released);
 */

 //Descorer
 controller(primary).ButtonRight.pressed(buttonRightpressed);
}
