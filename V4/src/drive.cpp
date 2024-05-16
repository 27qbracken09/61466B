#include "vex.h"


/**************************************************************************************/
/*                                      Drive.cpp                                     */
/**************************************************************************************/
/* This year we are not using vex's drivetrain configuration, because, even though it */
/* is functional and simple, that is also it's downside. I don't get to see it's      */
/* guts :( and it is very limited in what it can do, that is why we wrote our own.    */
/* Our drive class is split into three main parts, the Drive constructor, where we    */
/* will check if the motors are installed for any future program that wants to check  */
/* that, the autonomous control (driveForward, turnTo, etc...), and usercontrol, the  */
/* different drive methods, eponential or linear, etc...                              */
/**************************************************************************************/

//Drive Constructor - Future self, when you have a chance, please investigate why Past self made the ratio *2 and DIDNT COMMENT IT
Drive::Drive(int LF_port, int LB_port, int RF_port, int RB_port, inertial Gyro, float wheel_size) : LF(LF_port, true), LB(LB_port, true), RF(RF_port), RB(RB_port), Gyro(Gyro), wheel_ratio(wheel_size/360*2) {
 
 //Check if motors are installed
 if(LF.installed()){
   drive_motors_installed += 1;
 }
 if(LB.installed()){
   drive_motors_installed += 1;
 }
 if(RF.installed()){
   drive_motors_installed += 1;
 }
 if(RB.installed()){
   drive_motors_installed += 1;
 }
 if (!Gyro.installed()){
   gyro_error = true;
 }

 //Throw Error
 if (drive_motors_installed != 4 || gyro_error){
   drive_error = true;
   //Brain.Screen.print("Error!!!!!!!!!");
 }
 //This is for mechanum wheels, we are not using them this year
 wheel_ratio = (wheel_size*M_PI)/360;
}

//Drive with voltage - Just like it's name
void Drive::DriveWithVoltage(float LF_volt, float LB_volt, float RF_volt, float RB_volt){
  LF.spin(forward,LF_volt, volt);
  LB.spin(forward,LB_volt, volt);
  RF.spin(forward,RF_volt, volt);
  RB.spin(forward,RB_volt, volt);
}


//Set Drive PID constants - This is used to make the pid object for drive commands
void Drive::SetPID(float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout){

   drive_kp = kp;
   drive_ki = ki;
   drive_kd = kd;
   drive_starti = starti;
   drive_settle_error = settle_error;
   drive_settle_time = settle_time;
   drive_timeout = timeout;
   
}

//Set Turn PID constants - used to create the TurnPID object for turn commands
void Drive::SetTurnPID(float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout){
   turn_kp = kp;
   turn_ki = ki;
   turn_kd = kd;
   turn_starti = starti;
   turn_settle_error = settle_error;
   turn_settle_time = settle_time;
   turn_timeout = timeout;
   
}

//DriveFor Function - Drives for set distance
int Drive::DriveFor(float distance){

  //Create PID objects for turn and drive
  PID drivePID(drive_kp,drive_ki,drive_kd,drive_starti,drive_settle_error,drive_settle_time,drive_timeout);
  PID turnPID(turn_kp,turn_ki,turn_kd,turn_starti,turn_settle_error,turn_settle_time,turn_timeout);
  
  //Find Avgs of wheel rotation - If we add odometry, these will be replaced
  avg_left_wheel_rotation = (LF.position(degrees)+LB.position(degrees))/2;
  avg_right_wheel_rotation = (RF.position(degrees)+RB.position(degrees))/2;
  avg_wheel_rotation = (avg_left_wheel_rotation+avg_right_wheel_rotation)/2;
  
  //Set Starting Position to offset code later so that the robot will not drive backwards to get to 50 when it is at 80 instead of 130
  avg_starting_postion = avg_wheel_rotation;
  starting_angle = Gyro.angle();
  turn_volt = 0;  
  
  //While DrivePID has not met settled criteria - Not close enough to 0 (tolerances set in pid commands)
  while(!drivePID.is_settled()){

    //Calculate avg rot again
    avg_left_wheel_rotation = -(LF.position(degrees)+LB.position(degrees))/2;
    avg_right_wheel_rotation = -(RF.position(degrees)+RB.position(degrees))/2;
    avg_wheel_rotation = (avg_left_wheel_rotation+avg_right_wheel_rotation)/2;
    
    //Re-ad if doesn't work
    //starting_angle = Gyro.rotation();
    


    //Convert distance to rotation
    rotation = distance/wheel_ratio;

    //Find voltage/error for drive
    drive_volt = -drivePID.compute((rotation-avg_starting_postion)-avg_wheel_rotation);


    //Course Correct - Future self should test on robot, shouldn't this always run
    //if (!turnPID.is_settled()){
    turn_volt = turnPID.compute(starting_angle-Gyro.rotation());
    //} else {
      turn_volt = 0;
    //}
    
    
    //Calculate Wheel Voltages
    LF_volt = drive_volt + turn_volt;
    LB_volt = drive_volt + turn_volt;

    RF_volt = drive_volt - turn_volt;
    RB_volt = drive_volt - turn_volt;


    //Spin wheels
    LF.spin(forward,LF_volt,volt);
    RF.spin(forward,RF_volt,volt);
    LB.spin(forward,LB_volt,volt);
    RB.spin(forward,RB_volt,volt);


    //For Debugging only
    Brain.Screen.clearScreen(); Brain.Screen.setCursor(1, 1); Brain.Screen.print(rotation); Brain.Screen.print(", "); Brain.Screen.print(avg_wheel_rotation);
    Brain.Screen.newLine(); Brain.Screen.print(rotation*wheel_ratio); Brain.Screen.print(", "); Brain.Screen.print(avg_wheel_rotation*wheel_ratio);
    wait(1,msec);
    

  
  }

  //Log data to help understand why auton is not working, goal is to print mm as well
  std::cout << "Drive completed within " << avg_starting_postion-avg_wheel_rotation+rotation << " degrees\n";
  return 0;

  LF.stop(brake);
  LB.stop(brake);
  RF.stop(brake);
  RB.stop(brake);

}


//Just like it's name - turn to angle. If at 70, and told to turn to 90, it turns to 90, if at 20 and told to turn to 90, it turns to 90
//Future Self, make it take shortest turn, 70 - 130, clockwise or counterclockwise
int Drive::TurnTo(float angle){

 //Declare Turn Object
 PID TurnPID(turn_kp,turn_ki,turn_kd,turn_starti,turn_settle_error,turn_settle_time,turn_timeout);

 
 //While TurnPID has not met settled criteria
 while(!TurnPID.is_settled()){

   //Calculate 
   turn_volt = TurnPID.compute(angle-Gyro.rotation(degrees));


   //Apply voltages
   LF_volt = -turn_volt; 
   LB_volt = -turn_volt; 
   RF_volt = turn_volt; 
   RB_volt = turn_volt; 
   LF.spin(forward, LF_volt,volt);
   LB.spin(forward,LB_volt,volt);
   RF.spin(forward,RF_volt,volt);
   RB.spin(forward,RB_volt,volt);
   std::cout << turn_volt;
   std::cout << "\n";

   //Update position, may be used in future
   total_desired_rotation = Gyro.angle();
   
   //Delay to stop motors from shuddering at "resonant command times"
   vex::task::sleep(1);
   
 } 

 //Log data
 std::cout << "Turn completed within " << angle-Gyro.rotation(deg) << " degrees\n";
 return 0;
}

//Turn For, this one is a little bit different from the one above, but almost identical. It just applies an offset so it turns for an amount of degrees
int Drive::TurnFor(float angle){

  //PID Constants
  PID TurnPID(turn_kp,turn_ki,turn_kd,turn_starti,turn_settle_error,turn_settle_time,turn_timeout);


  //Offset Angle
  starting_angle = Gyro.angle();

  
  while(!TurnPID.is_settled()){

  //Calculate
   turn_volt = TurnPID.compute((angle+starting_angle)-Gyro.angle());

   //Update Angle
   total_desired_rotation = Gyro.angle();

  //Update Angle
   LF_volt = -turn_volt; 
   LB_volt = -turn_volt;
   LF.spin(forward, LF_volt,volt);
   LB.spin(forward,LB_volt,volt);
   RF.spin(forward,RF_volt,volt);
   RB.spin(forward,RB_volt,volt);
   
   //Future Self, test whether this needs the wait
   //wait(1,msec);
   
 } 
 std::cout << "Turn completed within " << angle+starting_angle-Gyro.rotation() << " degrees\n";
  return 0;
}

//This clears the sensors (encoders etc), and calibrates the gyro if the arg is true
void Drive::clearSensors(bool calibrate){
  LF.setPosition(0, deg);
  LB.setPosition(0, deg);
  RF.setPosition(0, deg);
  RB.setPosition(0, deg);
  if (calibrate){
    Gyro.calibrate();
    
  } else {
  Gyro.setRotation(0,deg);
}
}

//Update Wheel voltage based on joystic position, and drive method

/***********************************************************************************************************************************/
/* To the exponent is for testing only, make sure to add -1 if using exponent. Remove pow(), and if function if not using exponent */
/* Currently exponent is only implemented in arcade mechanum, if works implement in other functions.                               */
/***********************************************************************************************************************************/
//It works! Future self, add to other drive stuff
void Drive::update(enum::drive_method drive_method){

  if (drive_method != NO_DRIVE){
    if (drive_method == TANK){
      LF.spin(forward, controller(primary).Axis2.position(), percent);
      LB.spin(forward, controller(primary).Axis2.position(), percent);

      RF.spin(forward, controller(primary).Axis3.position(), percent);
      RB.spin(forward, controller(primary).Axis3.position(), percent);
    }
    else if (drive_method == TANK_MECHANUM){
      LF.spin(forward, (controller(primary).Axis2.position()-controller(primary).Axis1.position()), percent);
      LB.spin(forward, (controller(primary).Axis2.position()+controller(primary).Axis1.position()), percent);
      RF.spin(forward, (controller(primary).Axis3.position()+controller(primary).Axis4.position()), percent);
      RB.spin(forward, (controller(primary).Axis3.position()-controller(primary).Axis4.position()), percent);
    }
    else if (drive_method == ARCADE){
      LF.spin(forward, controller(primary).Axis3.position()-controller(primary).Axis1.position(), percent);
      LB.spin(forward, controller(primary).Axis3.position()-controller(primary).Axis1.position(), percent);
      RF.spin(forward, controller(primary).Axis3.position()+controller(primary).Axis1.position(), percent);
      RB.spin(forward, controller(primary).Axis3.position()+controller(primary).Axis1.position(), percent);

    }
    else if (drive_method == ARCADE_MECHANUM){

      /************************************************************************/
      /* We are using exponential control to make the robot easier to control */
      /* Because of this, we need to detect whether the joystick is positive  */
      /* or negative, and then reverse the joystick sign(make it +),          */
      /* Calculate the exponent, then reverse the final value to make the     */
      /* motor go backwards.                                                  */
      /************************************************************************/

      //Right Front Wheel
      if ((-controller(primary).Axis3.position() + (controller(primary).Axis4.position() +  controller(primary).Axis1.position())) > 0){
        RF.spin(forward,pow(1.0259812724,(-controller(primary).Axis3.position() + (controller(primary).Axis4.position() +  controller(primary).Axis1.position())))-1, volt);
      } else {
        
        if ((-controller(primary).Axis3.position() + (controller(primary).Axis4.position() +  controller(primary).Axis1.position())) == 0){
          RF.spin(forward,0, volt);
        } else {
        RF.spin(forward,-pow(1.0259812724,-(-controller(primary).Axis3.position() + (controller(primary).Axis4.position() +  controller(primary).Axis1.position())))-1, volt);
        }
      }

      //Left Front Wheel
      if ((-controller(primary).Axis3.position() - (controller(primary).Axis4.position() +  controller(primary).Axis1.position())) > 0){
        LF.spin(forward,pow(1.0259812724,(-controller(primary).Axis3.position() - (controller(primary).Axis4.position() +  controller(primary).Axis1.position())))-1, volt);
      } else {

        if ((-controller(primary).Axis3.position() - (controller(primary).Axis4.position() +  controller(primary).Axis1.position())) == 0){
          LF.spin(forward,0, volt);
        } else {
        LF.spin(forward,-pow(1.0259812724,-(-controller(primary).Axis3.position() - (controller(primary).Axis4.position() +  controller(primary).Axis1.position())))-1, volt);
        }
      }

      //Right Back Wheel
      if ((-controller(primary).Axis3.position() - (controller(primary).Axis4.position() -  controller(primary).Axis1.position())) > 0){
        RB.spin(forward,pow(1.0259812724,(-controller(primary).Axis3.position() - (controller(primary).Axis4.position() -  controller(primary).Axis1.position())))-1, volt);
      } else {

       if ((-controller(primary).Axis3.position() - (controller(primary).Axis4.position() -  controller(primary).Axis1.position())) == 0){
       RB.spin(forward,0,volt);
       } else {
        RB.spin(forward,-pow(1.0259812724,-(-controller(primary).Axis3.position() - (controller(primary).Axis4.position() -  controller(primary).Axis1.position())))-1, volt);
       }
      }

      //Left Back Wheel
      if ((-controller(primary).Axis3.position() + (controller(primary).Axis4.position() -  controller(primary).Axis1.position())) > 0){
        LB.spin(forward,pow(1.0259812724,(-controller(primary).Axis3.position() + (controller(primary).Axis4.position() -  controller(primary).Axis1.position())))-1, volt);
      } else {
        if ((-controller(primary).Axis3.position() + (controller(primary).Axis4.position() -  controller(primary).Axis1.position())) == 0){
        LB.spin(forward,0,volt);
        } else{
        LB.spin(forward,-pow(1.0259812724,-(-controller(primary).Axis3.position() + (controller(primary).Axis4.position() -  controller(primary).Axis1.position())))-1, volt);
        }
      }
      

    }
  }

  //Update Rotation
  total_desired_rotation = Gyro.rotation();

}


int Drive::drive_odometry(){

    //Declare Odometry Object
    Odom odom;

    
    
    //Start Odom Loop
    odom_is_enabled = true;
    while(odom_is_enabled){

    //Calculate from avg wheel rotation
    //Doesn't work because of mechanum wheels sqr(2)
    current_rot = /*avg_wheel_rotation*wheel_ratio;*/ ((LF.position(deg)+LB.position(degrees))/2 + (RF.position(deg)+RB.position(degrees)))/2*wheel_ratio;
    x = x + odom.calculate_x(Gyro.angle(), current_rot-prev_rot);
    y = y + odom.calculate_y(Gyro.angle(), current_rot-prev_rot);
    prev_rot = current_rot;

    //For Debugging only
    //Brain.Screen.clearScreen(); Brain.Screen.setCursor(1, 1); Brain.Screen.newLine(); Brain.Screen.print("X:");  Brain.Screen.print(x); Brain.Screen.print(", Y:"); Brain.Screen.print(y);
    //Brain.Screen.newLine(); Brain.Screen.print(current_rot);
    
    std::cout << "X Position: " << x << " Y Position: " << y << "\n";
    wait(10,msec);
    }
    return 0;
}


//Stop Odom
void Drive::stop_odometry(){
  odom_is_enabled = false;
}


