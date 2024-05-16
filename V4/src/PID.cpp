#include "vex.h"

//PID constructor #1
PID::PID(float kp, float ki, float kd, float starti) :
  
  kp(kp),
  ki(ki),
  kd(kd),
  starti(starti)
{};

//PID constructor #2
PID::PID(float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout) :
  
  kp(kp),
  ki(ki),
  kd(kd),
  starti(starti),
  settle_error(settle_error),
  settle_time(settle_time),
  timeout(timeout)
{};


//Calculate "voltage" from error
float PID::compute(float error){
  if (fabs(error) < starti){
    accumulated_error+=error;
  }
  if ((error>0 && previous_error<0)||(error<0 && previous_error>0)){ 
    accumulated_error = 0; 
  }
  output = kp*error + ki*accumulated_error + kd*(error-previous_error);

  previous_error=error;

  if(fabs(error)<settle_error){
    time_spent_settled+=10;
  } else {
    time_spent_settled = 0;
  }

  time_spent_running+=10;

  return output;
}

//Settled Function
bool PID::is_settled(){
  if (time_spent_running>timeout && timeout != 0){
    return(true);
  }
  if (time_spent_settled>settle_time){
    return(true);
  }
  return(false);
}