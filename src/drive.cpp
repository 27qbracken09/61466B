//All header files feed through vex.h
#include "vex.h"

//Along with the overloaded constructors in drive.h, we need all three here as well
//Unused motors have their ports set as NULL - This satisfies the requirement that all motors must be declared, while not actually giving them a port

//6M Drive
Drive::Drive(int L_Port1, int L_Port2, int L_Port3, int R_Port1, int R_Port2, int R_Port3, float wheel_size, int I_Port) : 
L1(L_Port1),
L2(L_Port2),
L3(L_Port3),

R1(R_Port1, true),
R2(R_Port2, true),
R3(R_Port3, true),

L(L1, L2, L3),
R(R1, R2, R3),
//First, we need to convert diameter to Circumference, then we can use that to find the ratio of degrees to inches
wheel_ratio((wheel_size*M_PI)/360),
I(I_Port),
parallel(NULL),
perpendicular(NULL)
{
//Calibrate Inertial/Gyro
I.calibrate();
while(I.isCalibrating()) wait(20,vex::msec);

}

//4M Drive
Drive::Drive(int L_Port1, int L_Port2, int R_Port1, int R_Port2, float wheel_size, int I_Port):
L1(L_Port1),
L2(L_Port2),
L3(NULL),

R1(R_Port1, true),
R2(R_Port2, true),
R3(NULL, true),

L(L1, L2, L3),
R(R1, R2, R3),
//First, we need to convert diameter to Circumference, then we can use that to find the ratio of degrees to inches
wheel_ratio((wheel_size*M_PI)/360),
I(I_Port),
parallel(NULL),
perpendicular(NULL)
{
   

}

//2M Drive for crazy people
Drive::Drive(int L_Port1, int R_Port1, float wheel_size, int I_Port):
L1(L_Port1),
L2(NULL),
L3(NULL),

R1(R_Port1, true),
R2(NULL, true),
R3(NULL, true),

L(L1, L2, L3),
R(R1, R2, R3),
//First, we need to convert diameter to Circumference, then we can use that to find the ratio of degrees to inches
wheel_ratio((wheel_size*M_PI)/360),
I(I_Port),
parallel(NULL),
perpendicular(NULL)
{
   

}

//Odom Constructors
//6M Drive
Drive::Drive(
    int L_Port1, 
    int L_Port2, 
    int L_Port3, 
    int R_Port1, 
    int R_Port2, 
    int R_Port3, 
    float wheel_size, 
    int I_Port, 
    int Parallel_to_wheels_tracker_port, 
    int Perpendicular_to_wheels_tracker_port, 
    float Parallel_distance_from_center, 
    float Perpendicular_distance_from_center,
    float Tracking_wheel_diameter
    
    ) : 
    L1(L_Port1),
    L2(L_Port2),
    L3(L_Port3),

    R1(R_Port1, true),
    R2(R_Port2, true),
    R3(R_Port3, true),

    L(L1, L2, L3),
    R(R1, R2, R3),
    //First, we need to convert diameter to Circumference, then we can use that to find the ratio of degrees to inches
    wheel_ratio((wheel_size*M_PI)/360),
    I(I_Port),
    parallel(Parallel_to_wheels_tracker_port),
    perpendicular(Perpendicular_to_wheels_tracker_port),
    parallel_dist_from_center(Parallel_distance_from_center),
    perpendicular_dist_from_center(Perpendicular_distance_from_center),
    tracked_wheel_ratio((Tracking_wheel_diameter*M_PI)/360)
   


    {
//Calibrate Inertial/Gyro
        I.calibrate();
        while(I.isCalibrating()) wait(20,vex::msec);

    }

//4M Drive
Drive::Drive(
    int L_Port1, 
    int L_Port2, 
    int R_Port1, 
    int R_Port2, 
    float wheel_size, 
    int I_Port,
    int Parallel_to_wheels_tracker_port, 
    int Perpendicular_to_wheels_tracker_port, 
    float Parallel_distance_from_center, 
    float Perpendicular_distance_from_center,
    float Tracking_wheel_diameter
    
    ):
    L1(L_Port1),
    L2(L_Port2),
    L3(NULL),

    R1(R_Port1, true),
    R2(R_Port2, true),
    R3(NULL, true),

    L(L1, L2, L3),
    R(R1, R2, R3),
    //First, we need to convert diameter to Circumference, then we can use that to find the ratio of degrees to inches
    wheel_ratio((wheel_size*M_PI)/360),
    I(I_Port),
    parallel(NULL),
    perpendicular(NULL)
    {}

//2M Drive for crazy people
Drive::Drive(
    int L_Port1, 
    int R_Port1, 
    float wheel_size, 
    int I_Port,
    int Parallel_to_wheels_tracker_port, 
    int Perpendicular_to_wheels_tracker_port, 
    float Parallel_distance_from_center, 
    float Perpendicular_distance_from_center,
    float Tracking_wheel_diameter
    
    ):
    L1(L_Port1),
    L2(NULL),
    L3(NULL),

    R1(R_Port1, true),
    R2(NULL, true),
    R3(NULL, true),

    L(L1, L2, L3),
    R(R1, R2, R3),
    //First, we need to convert diameter to Circumference, then we can use that to find the ratio of degrees to inches
    wheel_ratio((wheel_size*M_PI)/360),
    I(I_Port),
    parallel(NULL),
    perpendicular(NULL)
    {}


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

//When tuning drive PID I started by finding a number that would have a slope of 1, with the way the math works out, 0.35 was close
//I then noticed that the PID couldn't achive its goal because the voltage was getting too low, I doubled the kP constant and tried a gain
//It worked better but still didn't achieve the target
//Finally I decided to add kC to overcome static friction because increasing kP anymore made the robot Jerky
//Note: This was for a test robot, and these parameters will change with a new robot next year

Drive_PID Drive_PID_L(0.07,0,0, 1);
Drive_PID Drive_PID_R(0.07,0.0001,0, 1);

//Drive_for command will use a Drive_PID in combination with the wheel size to drive a real-world distance
float Drive::drive_for(float inches){

    std::cout << "\nDrivefor Started";
    //Start by converting inches into degrees, to do this, we need the wheel size, which we can put in the constructor.
    float desired_degrees = inches/wheel_ratio;

    //Output for debugging
    std::cout << "\nDesired Degrees: " << desired_degrees;

    //Then set desired degrees to distance from target - I'm going to try one for each wheel to help with accuracy
    float target_L_degrees = desired_degrees+L.position(vex::degrees);
    float target_R_degrees = desired_degrees+R.position(vex::degrees);

    //While loop for testing
    while(!(Drive_PID_L.close_enough(5) || Drive_PID_R.close_enough(5))){

    //We then have to compute error to feed into our Drive_PID function
    float error_L_degrees = target_L_degrees-L.position(vex::degrees);
    float error_R_degrees = target_R_degrees-R.position(vex::degrees);

    //We'll use two Drive_PID's because we have two wheels, and therefore two calculations - They were declared above this function
    float L_volts = Drive_PID_L.calculate(error_L_degrees);
    float R_volts = Drive_PID_R.calculate(error_R_degrees);

    //Output To terminal for debugging
    //std::cout << "\n" << L_volts << ", " << R_volts << ", " << L.position(vex::degrees) << ", " << R.position(vex::degrees);

    //Then Apply to motors
    L.spin(vex::forward, L_volts, vex::volt);
    R.spin(vex::forward, R_volts, vex::volt);
    wait(20,vex::msec);
    }

    std::cout << "\ndrive_for done";

    //Added hold so motors do not coast - And had them stop in the first place to negate the affects of residual voltage
    L.stop(vex::hold);
    R.stop(vex::hold);

    //Return avg for testing and datalogging
    return (L.position(vex::degrees)+R.position(vex::degrees))/2;

    
    
}

Drive_PID Turn_PID(0.1,0,0,1.5);
float Drive::turn_to(float degrees){
    //Notify that turn has started
    std::cout << "\nTurnto Started";

   

    //Collect initial gyro/inertial heading - In degrees from 0 - 360
    float normalized_target_I_degrees = reduce_negative_180_to_180(degrees);

    

    //Use PID declared above to turn to correct heading
    while (!Turn_PID.close_enough(5)){

            
            //Updated to handle "directional" 360 degrees to easily calculate 
            //Helpful document: https://forum.arduino.cc/t/calculating-heading-distance-and-direction/92144/5
            float normalized_current_I_degrees = reduce_negative_180_to_180(I.heading());

            float normalized_error_I_degrees = reduce_negative_180_to_180(normalized_target_I_degrees-normalized_current_I_degrees);

            float I_voltage = Turn_PID.calculate(normalized_error_I_degrees);


        

        
        
        //Not needed, left here so I can refer back to it
        //Calculate Voltage needed - Left wheel will be swapped to negative because that will make the robot turn in the direction of the gyro
        //float I_voltage = Turn_PID.calculate(error_I_degrees);

        //Debugging
        //std::cout << "\n" << I_voltage;

        //Spin wheels
        L.spin(vex::forward,I_voltage,vex::volt);
        R.spin(vex::forward,-I_voltage,vex::volt);

        //delay to even stuff out
        wait(20,vex::msec);


    }

    //When PID thinks it's close enough, stop motors
    L.stop(vex::hold);
    R.stop(vex::hold);

    //Notify user
    std::cout << "\nTurnTo Done";

    return I.heading();

}

/* Started Drive Class by figuring out the most simple way to control the robot, and plan to build from there.
   The three levels of drive complexity is voltage controlled, driver controlled, and program controlled */