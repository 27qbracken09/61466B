#pragma once

#include "vex.h"

enum drive_method{NO_DRIVE, TANK, TANK_MECHANUM, ARCADE, ARCADE_MECHANUM};



class Drive
{
 public:

  Drive(int LF_port, int LB_port, int RF_port, int RB_port, inertial Gyro, float wheel_size);


  
  void SetPID(float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout);
  void SetTurnPID(float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout);

  void DriveWithVoltage(float LF_volt, float LB_volt, float RF_volt, float RB_volt);

  int DriveFor(float distance);
  int TurnTo(float angle);
  int TurnFor(float angle);

  void update(enum::drive_method drive_method);

  int drive_odometry();
  void stop_odometry();

  void clearSensors(bool calibrate);

  void thisisatest();

  motor LF;
  motor LB;

  motor RF;
  motor RB;

  inertial Gyro;


  float x = 0;
  float y = 0;

  bool drive_error = false;
  bool gyro_error = false;

  
  

  

private:
  float LF_volt;
  float LB_volt;
  float RF_volt;
  float RB_volt;

  float drive_kp;
  float drive_ki;
  float drive_kd;
  float drive_starti;
  float drive_settle_error;
  float drive_settle_time;
  float drive_timeout;
  

  float turn_kp;
  float turn_ki;
  float turn_kd;
  float turn_starti;
  float turn_settle_time;
  float turn_timeout;
  float turn_settle_error;

  
  float avg_left_wheel_rotation;
  float avg_right_wheel_rotation;

  float wheel_ratio;

  float rotation;

  float drive_volt = 0;
  float turn_volt;

  float total_desired_rotation = 0;
  float starting_angle;

  float avg_starting_postion;
  float avg_wheel_rotation;
  
  
  float current_rot;
  float prev_rot = 0;
  
  bool odom_is_enabled = true;

  


  int drive_motors_installed = 0;


  


  

  

  

  

};