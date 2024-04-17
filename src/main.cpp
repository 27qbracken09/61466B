/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       quinnbracken                                              */
/*    Created:      3/16/2024, 11:54:25 AM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

//Goal: Design a functional and modular system to control the robot, should also be accurate
//Constraints: Different motor ports must not cause a difference in performance, must be able to be applied to 2, 4, and 6 motor drive

//Goal for 3/16/24: Start creating drive control - make it modular

//Goal for 3/17/24: Start on Some form of Odometry - Validate Accuracy of robot

//Goal for 4/11/24: Create Lvgl custom functions and set library - Never finished, due to time
//Goal for 4/14/24: Start implementing log handler
//Log Handler Implemented 4/17/23 - Issues include printing strings to sd card file (Abandoned), Learned how to use ostrinstream, scoped value in main for battery report, slightly worried about mem usage
//Goal for 4/17/24 - Add logging to drive class



#include "vex.h"

using namespace vex;



// A global instance of competition
competition Competition;


// First, I need to declare a drivetrain
  // I want to code a custom drivetrain so that I can have more control
  // Declaration should look like this:
  // Drivetrain chassis(L motor group, R motor group, Gyro/Inertial, Track wheel 1, Track wheel 2);
  // I'm going to start with a drivetrain that responds to joystick inputs.
  //Created Drive.h and cpp

//Test Drivetrain Declaration, remove when actually using program


//Actual Declaration - L1, L2, R1, R2, Wheel Diameter, Inertial Port

Drive chassis(PORT14, PORT16, PORT12, PORT13, 4, PORT3);





void pre_auton(void) {
  log("main.cpp/pre_auton", STATUS, "Pre Auton Started");
  
  
}



void autonomous(void) {
  log("main.cpp/autonomous", STATUS, "Auton Started");
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}



void usercontrol(void) {
  log("main.cpp/usercontrol", STATUS, "Usercontrol Started");
  while (1) {
    
    
    //Update Driver control Drivetrain velocities using update function - Drivetrain is called chassis in this
    chassis.update(TANK);
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  log("main.cpp/main", STATUS, "Program Started");

  { //Scope Pct Var so it's cleared after use
  std::ostringstream BattpctString;
  BattpctString << "Battery Percent: " << Brain.Battery.capacity(pct) << "%";
  log("Battery", STATUS, BattpctString.str());
  }
  
  
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
