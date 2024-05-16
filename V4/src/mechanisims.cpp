#include "vex.h"
#include <string.h>


void debug(std::string msg, int debug_level){
  if (DEBUGGING == debug_level){
    std::cout << msg;

  }
  else if (DEBUGGING == debug_level) {
    std::cout << msg;

  }
}

Catapult::Catapult(int Cata_Port_1, int Cata_Port_2, bool is_reversed, int tracker_port): cata_motor_1(Cata_Port_1,is_reversed), cata_motor_2(Cata_Port_2), cata_limit(Brain.ThreeWirePort.B)
{
 cata_motor_1.setVelocity(100,percent);  
 cata_motor_1.setMaxTorque(100,percent);
 cata_motor_2.setVelocity(100,percent);  
 cata_motor_2.setMaxTorque(100,percent);
}

PID CataPID(0.1,0,0,0);
void Catapult::update(){

 
  if (cata_limit.pressing()){
    //controller(primary).rumble(".-");
    if (controller(primary).ButtonL1.pressing()){

      //calculate Error for P loop
      //Not Done Right Now!!

      cata_motor_1.spin(forward);
      cata_motor_2.spin(forward);
      wait(0.1,sec);
      cata_motor_1.stop();
      cata_motor_2.stop();
      wait(0.5,sec);
    }else if (controller(primary).ButtonL2.pressing()){
      cata_motor_1.spin(reverse);
      cata_motor_2.spin(reverse);

    } else{
      
    cata_motor_1.stop(hold);
    cata_motor_2.stop(hold);
    }
    

  } else {
    if (controller(primary).ButtonL2.pressing()){
        cata_motor_1.setVelocity(50,percent);
        cata_motor_1.setMaxTorque(100,percent);
        cata_motor_1.spin(reverse);

        cata_motor_2.setVelocity(50,percent);
        cata_motor_2.setMaxTorque(100,percent);
        cata_motor_2.spin(reverse);

      } else {
    cata_motor_1.setVelocity(100,percent);
    cata_motor_1.setMaxTorque(100,percent);
    cata_motor_1.spin(forward);

    cata_motor_2.setVelocity(100,percent);
    cata_motor_2.setMaxTorque(100,percent);
    cata_motor_2.spin(forward);
  }
  }
}

//Declare catapult object for use in manual loading
Catapult cata(PORT11,PORT4,true,2);


//Intake Triballs
void buttonR1pressed(){
  debug("Button R1 Pressed\n",2);
  intake.spin(forward,12,volt);
}

//Stop intake
void buttonR1released(){
  debug("Button R1 Released!\n",2);
  intake.stop(); 
}

//Outtake Triball
void buttonR2pressed(){
   debug("Button R2 Pressed!\n",2);
  intake.spin(reverse,12,volt);
}

//Stop Intake
void buttonR2released(){
  debug("Button R2 Released\n",2);
  intake.stop();
}
/*
//Manually Reload Catapult
void buttonL1pressed(){
  std::cout << "Button L1 Pressed!\n";
  cata.cata_motor.spin(forward,9,volt);

}

void buttonL1released(){
  std::cout << "Button L1 Released\n";
  cata.cata_motor.stop(hold);
}
/*
void buttonL2pressed(){
  std::cout << "Button L2 Pressed\n";
  cata.cata_motor.spin(reverse,12,volt);

}

void buttonL2released(){
  std::cout << "Button L2 Released!\n";
  //This is coast, so when we release it, it will continue going upwards as well.
  cata.cata_motor.stop(coast);
}
*/
bool enabled = false;
void buttonRightpressed(){
  
  
  if (!enabled){
    
    enabled = true;
    descorer.set(1);
    debug("Descorer Disabled\n",2);
  }
  else if (enabled){
    
    enabled = false;
    descorer.set(0);

    debug("Descorer Disabled\n",2);

  }

}

