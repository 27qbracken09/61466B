//All header files feed through vex.h
#include "vex.h"

//Along with the overloaded constructors in drive.h, we need all three here as well

//6M Drive
Drive::Drive(int L_Port1, int L_Port2, int L_Port3, int R_Port1, int R_Port2, int R_Port3) : 
L1(L_Port1),
L2(L_Port2),
L3(L_Port3),

R1(R_Port1, true),
R2(R_Port2, true),
R3(R_Port3, true),

L(L1, L2, L3),
R(R1, R2, R3)
{
   

}

//4M Drive
Drive::Drive(int L_Port1, int L_Port2, int R_Port1, int R_Port2):
L1(L_Port1),
L2(L_Port2),
L3(NULL),

R1(R_Port1, true),
R2(R_Port2, true),
R3(NULL, true),

L(L1, L2, L3),
R(R1, R2, R3)
{
   

}

//2M Drive for crazy people
Drive::Drive(int L_Port1, int R_Port1):
L1(L_Port1),
L2(NULL),
L3(NULL),

R1(R_Port1, true),
R2(NULL, true),
R3(NULL, true),

L(L1, L2, L3),
R(R1, R2, R3)
{
   

}

//Low level access to hardware
void Drive::drive_with_voltage(float L_volt, float R_volt){
    L.spin(vex::forward,L_volt,vex::volt);
    R.spin(vex::forward,R_volt,vex::volt);
}

//Driver control
void Drive::update(enum::drive_method drive_method){

    //Declare Voltage variables for computations within arcade control styles
    //They are set to zero to avoid garbage values
    float L_volt = 0;
    float R_volt = 0;

    //Read Joystick values and store them - I create a seperate "controller" every time so this doesn't interfere with potential mechanism control
    float axis1 = vex::controller(vex::primary).Axis1.position();
    float axis2 = vex::controller(vex::primary).Axis2.position();
    float axis3 = vex::controller(vex::primary).Axis3.position();
    float axis4 = vex::controller(vex::primary).Axis4.position();

    //Scale values to 12 volts - not strictly nessisary, but worth trying to see if it makes a difference
    //Seperated from other part to meet goal of modularity
    axis1 = axis1/8.33333333333333;
    axis2 = axis2/8.33333333333333;
    axis3 = axis3/8.33333333333333;
    axis4 = axis4/8.33333333333333;

    
    //Check which drive method is requested, and apply that method
    //I'm using a switch statement because they are faster than if statements
    switch (drive_method){

        //In the case of no driver control do nothing - mostly just a placeholder
        case NO_DRIVE:
            break;

        //In the case of tank, set motors to correct values to accomplish layout, refer to vex tank control
        case TANK:
            
            //Axis 3 is left stick up and down
            L.spin(vex::forward, axis3, vex::volt);

            //Axis 2 is right stick up and down
            R.spin(vex::forward, axis2, vex::volt);
            break;

        //In the case of split arcade, use the controller values to modify final motor speed
        case SPLIT_ARCADE:
            
            //Axis 3 is the "power", then we need to remove power to turn left, but since the controller goes negative as we push left. this needs to add to the total voltage
            //It is still adding a negative value though
            L_volt = axis3 + axis1;

            //Exactly the same thing for Right side, but negative as it will need to do the opposite of the left
            R_volt = axis3 - axis1;

            //Apply voltages to the motors
            L.spin(vex::forward, L_volt, vex::volt);
            R.spin(vex::forward, R_volt, vex::volt);
            break;

        //In the case of combined arcade left (all on the left joystick), follow the same process as split arcade, but with left stick not 2 seperate ones
        case COMB_ARCADE_L:

            //Axis 3 is the "power", then we need to remove power to turn left, but since the controller goes negative as we push left. this needs to add to the total voltage
            //It is still adding a negative value though
            L_volt = axis3 + axis4;

            //Exactly the same thing for Right side, but negative as it will need to do the opposite of the left
            R_volt = axis3 - axis4;

            //Apply voltages to the motors
            L.spin(vex::forward, L_volt, vex::volt);
            R.spin(vex::forward, R_volt, vex::volt);
            break;

        //In the case of Right combined arcade, do the same thing as left comb, but with different axis values
        case COMB_ARCADE_R:

            //Axis 3 is the "power", then we need to remove power to turn left, but since the controller goes negative as we push left. this needs to add to the total voltage
            //It is still adding a negative value though
            L_volt = axis2 + axis1;

            //Exactly the same thing for Right side, but negative as it will need to do the opposite of the left
            R_volt = axis2 - axis1;

            //Apply voltages to the motors
            L.spin(vex::forward, L_volt, vex::volt);
            R.spin(vex::forward, R_volt, vex::volt);
            break;





    };


    
}

void Drive::drive_for_degrees(float degrees){
    
    //Spin each motor to target
    L.spinFor(degrees, vex::degrees);
    R.spinFor(degrees, vex::degrees);
    
    
    

}

/* Started Drive Class by figuring out the most simple way to control the robot, and plan to build from there.
   The three levels of drive complexity is voltage controlled, driver controlled, and program controlled */