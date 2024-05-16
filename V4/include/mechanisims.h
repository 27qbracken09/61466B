#pragma once
#include "vex.h"

enum arm_tracker_method{LIMIT, ROTATION, BUMPER};

class Catapult{
    public:
        Catapult(int Cata_Port_1, int Cata_Port_2, bool is_reversed,  int tracker_port);

        motor cata_motor_1;
        motor cata_motor_2;
        motor_group cata_motor;
        limit cata_limit;
        
        
        void update();
        

    private:
       // vex::triport ThreeWire = vex::triport(vex::PORT22);
        
        


       
}; 

extern Catapult cata;
void buttonR2pressed();
void buttonR2released();

void buttonR1pressed();
void buttonR1released();

void buttonL2pressed();
void buttonL2released();

void buttonL1pressed();
void buttonL1released();

void buttonRightpressed();

void debug(std::string msg);

