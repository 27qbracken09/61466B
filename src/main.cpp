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



#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

// First, I need to declare a drivetrain
  // I want to code a custom drivetrain so that I can have more control
  // Declaration should look like this:
  // Drivetrain chassis(L motor group, R motor group, Gyro/Inertial, Track wheel 1, Track wheel 2);
  // I'm going to start with a drivetrain that responds to joystick inputs.
  //Created Drive.h and cpp

//Test Drivetrain Declaration, remove when actually using program

//Fake drive motors
vex::motor motor1(PORT1);
vex::motor motor2(PORT2);
vex::motor motor3(PORT3);
vex::motor motor4(PORT4);

//Actual Declaration
Drive chassis(motor1, motor2, motor3, motor4);


void pre_auton(void) {
  
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
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
  std::cout << "\nStarted Program: " << PROG_NAME;
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
