#include "vex.h"

//This will reduce angles larger than 360 by removing multiples of 360 by way of a while loop and subtraction/addition
float reduce_0_to_360(float angle) {
  //While the angle is not within a 0 to 360 degree range
  while(!(angle >= 0 && angle < 360)) {
    //If angle is less than 0, add 360
    if( angle < 0 ) { angle += 360; }

    //if the angle is greator than 360, subtract 360
    if(angle >= 360) { angle -= 360; }
  }
  return(angle);
}

//This does the same thing as above, but with -180 and 180
float reduce_negative_180_to_180(float angle) {
  //While the angle is not within a -180 to 180 degree range
  while(!(angle >= -180 && angle < 180)) {
    //If the angle is less than -180, add 360 to make it "wrap" around
    if( angle < -180 ) { angle += 360; }

    //If angle is greator than 180, subtract
    if(angle >= 180) { angle -= 360; }
  }
  return(angle);
}

//Same thing as the top 2
float reduce_negative_90_to_90(float angle) {
  //While the angle is not within a -90 to 90 degree range
  while(!(angle >= -90 && angle < 90)) {
    if( angle < -90 ) { angle += 180; }
    if(angle >= 90) { angle -= 180; }
  }
  return(angle);
}

//Quickly converts degrees to radian following the standard formula
float to_rad(float angle_deg){
  return(angle_deg/(180.0/M_PI));
}

//Quickly converts back from radians following the standard formula
float to_deg(float angle_rad){
  return(angle_rad*(180.0/M_PI));
}


//This limits the max and min values
float clamp(float input, float min, float max){
  //If input is greator than max, return max
  if( input > max ){ return(max); }
  //If input is less than min, return min
  if(input < min){ return(min); }
  return(input);
}

//Quickly detect if a motor is reversed
bool is_reversed(double input){
  if(input<0) return(true);
  return(false);
}

//Convert pct to volt
float to_volt(float percent){
  return(percent*12.0/100.0);
}

//Not needed, but returns a port with the 0ith port accounted for
int to_port(int port){
  if(port>8){
    return(0);
  }
  return(port-1);
}

