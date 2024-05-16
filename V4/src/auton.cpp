#include "vex.h"

/**************************************************************************************/
/*                               Explanation Boxes!                                   */
/* These boxes will help explain what each part of the code does, however if the      */
/* code repeatedly uses the same part or sample of code                               */
/* there will not always be a full explanation box. For Example, every auton will     */
/* start with the same two functions, so a brief //Comment will be used instead.      */
/* If I copy and paste some sections of code, I will not remove the large explanations*/
/* so there may be multiple large explanations in the code                            */
/**************************************************************************************/

//////////////////////////////////
//Sudo Macros
///////////////////////////////////////
Odom odom;


int auton_odom(){
  chassis.drive_odometry();
  return 0;
}

void no_auton(){
  chassis.clearSensors(false);

  //Start Odom - Useful for testing
  vex::task odometry(auton_odom);

}
//////////////////////////////////////


/////////////////////////////////
//Auton Programs
///////////////////////////////////////

  /***************************************************************************************/
  /*                                  Left Autonomous                                    */
  /***************************************************************************************/
  /* This is the full left autonomous program for during competition (15 sec), we plan   */
  /* on making the auton remove the triball from alliance match load zone, then touching */
  /* the elevation bar. In the future I want to experiment with catapulting preload to   */
  /* mess up the opposing alliance's auton.                                              */
  /***************************************************************************************/

void left_auton(){
    




  /**************************************************************************************/
  /* Do not ever calibrate the gyro right as auton starts!                              */
  /* This is because the gyro will either pause the program, or miscalibrate the gyro   */
  /* because the robot is moving.                                                       */
  /**************************************************************************************/
  chassis.clearSensors(false); 

  /**************************************************************************************/
  /* Compiler kept spitting back errors because I was trying to call a function not in  */
  /* same class, to fix this I made a function that calls the function in the other     */
  /* class.                                                                             */
  /**************************************************************************************/
  vex::task odometry(auton_odom);
  
  
  


  //Auton Code goes here... soo get coding, self!
  //chassis.DriveFor(24);
  //chassis.TurnTo(-45);

  chassis.DriveFor(24);
  chassis.DriveFor(-18);
  chassis.DriveFor(6);
  chassis.TurnTo(-65);
  //chassis.DriveFor(36);
  //chassis.TurnTo(90);

  
  
  //chassis.DriveWithVoltage(12,12,12,12);
  
  
 
  chassis.stop_odometry();

}

/****************************************************************************************/
/*                                Left Auton w/o touching bar                           */
/****************************************************************************************/
/* We have decided to include this auton just in case the other robot will end up       */
/* touching the bar in a way that will disrupt our auton. Many of these other autons    */
/* may not be used more than once, but they often are simple modifications of the       */
/* original auton, and may win us a mach                                                */
/****************************************************************************************/

void left_auton_no_bar(){
  
  




  /**************************************************************************************/
  /* Do not ever calibrate the gyro right as auton starts!                              */
  /* This is because the gyro will either pause the program, or miscalibrate the gyro   */
  /* because the robot is moving.                                                       */
  /**************************************************************************************/
  chassis.clearSensors(false); 

  /**************************************************************************************/
  /* Compiler kept spitting back errors because I was trying to call a function not in  */
  /* same class, to fix this I made a function that calls the function in the other     */
  /* class.                                                                             */
  /**************************************************************************************/
  vex::task odometry(auton_odom);

  //Auton Code goes here... soo get coding, self!
  
  

}

/****************************************************************************************/
/*                              Left Auton w/ Catapult                                  */
/****************************************************************************************/
/* Currently I plan on using this as a sort of "experiment", and testing whether I can  */
/* catapult ALL triballs on our robot's quadrant to the other diagonal quadrant to      */
/* mess up the opposing alliance's auton(messing w/ intake, moving other triballs etc.) */
/****************************************************************************************/
void left_auton_catapult(){
  




  /**************************************************************************************/
  /* Do not ever calibrate the gyro right as auton starts!                              */
  /* This is because the gyro will either pause the program, or miscalibrate the gyro   */
  /* because the robot is moving.                                                       */
  /**************************************************************************************/
  chassis.clearSensors(false); 

  /**************************************************************************************/
  /* Compiler kept spitting back errors because I was trying to call a function not in  */
  /* same class, to fix this I made a function that calls the function in the other     */
  /* class.                                                                             */
  /**************************************************************************************/
  vex::task odometry(auton_odom);

  //Auton Code goes here... soo get coding, self!
  
  

}

/***************************************************************************************/
/*                                      Right Autonomous                               */
/***************************************************************************************/
/* The right autonomous has two goals, score an alliance triball in the net, and touch */
/* the elevation bar. It is a simple auton, and should be fairly consistent            */
/***************************************************************************************/

void right_auton(){
  




  /**************************************************************************************/
  /* Do not ever calibrate the gyro right as auton starts!                              */
  /* This is because the gyro will either pause the program, or miscalibrate the gyro   */
  /* because the robot is moving.                                                       */
  /**************************************************************************************/
  chassis.clearSensors(false); 

  /**************************************************************************************/
  /* Compiler kept spitting back errors because I was trying to call a function not in  */
  /* same class, to fix this I made a function that calls the function in the other     */
  /* class.                                                                             */
  /**************************************************************************************/
  //vex::task odometry(auton_odom);

  chassis.DriveFor(36);
  chassis.TurnTo(-45);
  //chassis.DriveFor(12);
  //chassis.TurnTo(0);
  //chassis.DriveFor(18);
  //chassis.TurnTo(90);



  //chassis.stop_odometry();
  
  
  

}

/****************************************************************************************/
/*                               Right Auton w/o touching bar                           */
/****************************************************************************************/
/* We have decided to include this auton just in case the other robot will end up       */
/* touching the bar in a way that will disrupt our auton. Many of these other autons    */
/* may not be used more than once, but they often are simple modifications of the       */
/* original auton, and may win us a mach                                                */
/****************************************************************************************/

void right_auton_no_bar(){
  




  /**************************************************************************************/
  /* Do not ever calibrate the gyro right as auton starts!                              */
  /* This is because the gyro will either pause the program, or miscalibrate the gyro   */
  /* because the robot is moving.                                                       */
  /**************************************************************************************/
  chassis.clearSensors(false); 

  /**************************************************************************************/
  /* Compiler kept spitting back errors because I was trying to call a function not in  */
  /* same class, to fix this I made a function that calls the function in the other     */
  /* class.                                                                             */
  /**************************************************************************************/
  vex::task odometry(auton_odom);

  //Auton Code goes here... soo get coding, self!
  
  

}
/////////////////////////////////////////////