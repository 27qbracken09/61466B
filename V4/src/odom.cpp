#include "vex.h"

//Calculate x traveled
float Odom::calculate_x(float angle, float pos){
  return cos(to_rad(angle))*pos;
};


//Calculate y traveled
float Odom::calculate_y(float angle, float pos){
  return sin(to_rad(angle))*pos;
};

