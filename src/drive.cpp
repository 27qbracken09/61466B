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

//Log which motors are plugged in
if (!L1.installed()) log("Motor_L1", WARNING, "Motor Disconnected!");
if (!L2.installed()) log("Motor_L2", WARNING, "Motor Disconnected!");
if (!L3.installed()) log("Motor_L3", WARNING, "Motor Disconnected!");
if (!R1.installed()) log("Motor_R1", WARNING, "Motor Disconnected!");
if (!R2.installed()) log("Motor_R2", WARNING, "Motor Disconnected!");
if (!R3.installed()) log("Motor_R3", WARNING, "Motor Disconnected!");

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
    if (!L1.installed()) log("Motor_L1", WARNING, "Motor Disconnected!");
    if (!L2.installed()) log("Motor_L2", WARNING, "Motor Disconnected!");
    //if (!L3.installed()) log("Motor_L3", WARNING, "Motor Disconnected!");
    if (!R1.installed()) log("Motor_R1", WARNING, "Motor Disconnected!");
    if (!R2.installed()) log("Motor_R2", WARNING, "Motor Disconnected!");
    //if (!R3.installed()) log("Motor_R3", WARNING, "Motor Disconnected!");

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
    if (!L1.installed()) log("Motor_L1", WARNING, "Motor Disconnected!");
    if (!R1.installed()) log("Motor_R1", WARNING, "Motor Disconnected!");
   
   

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
        if (!L1.installed()) log("Motor_L1", WARNING, "Motor Disconnected!");
        if (!L2.installed()) log("Motor_L2", WARNING, "Motor Disconnected!");
        if (!L3.installed()) log("Motor_L3", WARNING, "Motor Disconnected!");
        if (!R1.installed()) log("Motor_R1", WARNING, "Motor Disconnected!");
        if (!R2.installed()) log("Motor_R2", WARNING, "Motor Disconnected!");
        if (!R3.installed()) log("Motor_R3", WARNING, "Motor Disconnected!");


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
    {
        if (!L1.installed()) log("Motor_L1", WARNING, "Motor Disconnected!");
        if (!L2.installed()) log("Motor_L2", WARNING, "Motor Disconnected!");
        
        if (!R1.installed()) log("Motor_R1", WARNING, "Motor Disconnected!");
        if (!R2.installed()) log("Motor_R2", WARNING, "Motor Disconnected!");
        

    }

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
    {
        if (!L1.installed()) log("Motor_L1", WARNING, "Motor Disconnected!");
        if (!R1.installed()) log("Motor_R1", WARNING, "Motor Disconnected!");

    }


//Low level access to hardware
void Drive::drive_with_voltage(float L_volt, float R_volt){
    { //Scoping like this seems neater to combine stuff - Also saves memory by deleting objects once out of scope
    std::ostringstream VoltageLabel;
    VoltageLabel << "l_motor_group set to: " << L_volt << " r_motor_group set to: " << R_volt;
    log("drive.cpp/Drive/drive_with_voltage", DEBUG, VoltageLabel.str());
    }
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

    //Check if the motors are getting too hot during driver

    //Level 1
    if (L.temperature(vex::celsius) > 50) log("l_motor_group", WARNING, "Motor Temp close to lv1(55C)!");
    if (R.temperature(vex::celsius) > 50) log("r_motor_group", WARNING, "Motor Temp close to lv1(55C)!");

    //Level 2
    if (L.temperature(vex::celsius) > 55) log("l_motor_group", WARNING, "Motor Temp close to lv2(60C)!");
    if (R.temperature(vex::celsius) > 55) log("r_motor_group", WARNING, "Motor Temp close to lv2(60C)!");

    //Level 3
    if (L.temperature(vex::celsius) > 60) log("l_motor_group", WARNING, "Motor Temp close to lv3(65C)!");
    if (R.temperature(vex::celsius) > 60) log("r_motor_group", WARNING, "Motor Temp close t0 lv3(65C)!");

    //Level 4 not implemented because motors would stop


    
}

void Drive::drive_for_degrees(float degrees){
    
    //Spin each motor to target
    L.spinFor(degrees, vex::degrees);
    R.spinFor(degrees, vex::degrees);

    //Check if the motors are getting too hot during movement

    //Level 1
    if (L.temperature(vex::celsius) > 50) log("l_motor_group", WARNING, "Motor Temp close to lv1(55C)!");
    if (R.temperature(vex::celsius) > 50) log("r_motor_group", WARNING, "Motor Temp close to lv1(55C)!");

    //Level 2
    if (L.temperature(vex::celsius) > 55) log("l_motor_group", WARNING, "Motor Temp close to lv2(60C)!");
    if (R.temperature(vex::celsius) > 55) log("r_motor_group", WARNING, "Motor Temp close to lv2(60C)!");

    //Level 3
    if (L.temperature(vex::celsius) > 60) log("l_motor_group", WARNING, "Motor Temp close to lv3(65C)!");
    if (R.temperature(vex::celsius) > 60) log("r_motor_group", WARNING, "Motor Temp close t0 lv3(65C)!");
    
    
    

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

    log("Drivetrain", STATUS, "Drive Started");
    //Start by converting inches into degrees, to do this, we need the wheel size, which we can put in the constructor.
    float desired_degrees = inches/wheel_ratio;

    {
    std::ostringstream label;
    label << "Computed Degrees" << desired_degrees;
    log("drive.cpp/Drive/drive_for_degrees", DEBUG, label.str());
    }
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

    //Check if the motors are getting too hot during movement

    //Level 1
    if (L.temperature(vex::celsius) > 50) log("l_motor_group", WARNING, "Motor Temp close to lv1(55C)!");
    if (R.temperature(vex::celsius) > 50) log("r_motor_group", WARNING, "Motor Temp close to lv1(55C)!");

    //Level 2
    if (L.temperature(vex::celsius) > 55) log("l_motor_group", WARNING, "Motor Temp close to lv2(60C)!");
    if (R.temperature(vex::celsius) > 55) log("r_motor_group", WARNING, "Motor Temp close to lv2(60C)!");

    //Level 3
    if (L.temperature(vex::celsius) > 60) log("l_motor_group", WARNING, "Motor Temp close to lv3(65C)!");
    if (R.temperature(vex::celsius) > 60) log("r_motor_group", WARNING, "Motor Temp close to lv3(65C)!");

    //Log Motor Positions for debugging

    {
    std::ostringstream label;
    label << "l_group @ " << L.position(vex::deg) << " (deg) r_group @ " << R.position(vex::deg) << " (deg)";
    log("Drivetrain", DEBUG, label.str());

    //Clear String and print motor voltages
    label.str("");
    label << "l_volt @ " << L_volts << " (volts) r_volt @ " << R_volts << " (volts)";
    log("drive.cpp/Drive/drive_for", DEBUG, label.str());
    }

    //Then Apply to motors
    L.spin(vex::forward, L_volts, vex::volt);
    R.spin(vex::forward, R_volts, vex::volt);
    wait(20,vex::msec);
    }

    
    //Added hold so motors do not coast - And had them stop in the first place to negate the affects of residual voltage
    L.stop(vex::hold);
    R.stop(vex::hold);

    {
    std::ostringstream label;

    label << "Drive Completed within " << (L.position(vex::degrees)+R.position(vex::degrees))/2 << " degrees";
    log("Drivetrain", STATUS, label.str());
    }

    //Return avg for testing and datalogging
    return (L.position(vex::degrees)+R.position(vex::degrees))/2;

    
    
}

Drive_PID Turn_PID(0.1,0,0,1.5);
float Drive::turn_to(float degrees){
    //Notify that turn has started
    log("Drivetrain", STATUS, "TurnTo Started");

   

    //Collect initial gyro/inertial heading - In degrees from 0 - 360
    float normalized_target_I_degrees = reduce_negative_180_to_180(degrees);

    {
    std::ostringstream label;

    label << "Attempting to turn to " << normalized_target_I_degrees<< " degrees";
    log("Drivetrain", DEBUG, label.str());
    }
    

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
        {
        std::ostringstream label;

        label << "turn_volt @  " << I_voltage << " (volts)";
        log("Drivetrain", DEBUG, label.str());
        }

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
    {
    std::ostringstream label;

    label << "Turn Completed within " << normalized_target_I_degrees-I.heading() << " degrees";
    log("Drivetrain", STATUS, label.str());
    }

    return I.heading();

}

/* Started Drive Class by figuring out the most simple way to control the robot, and plan to build from there.
   The three levels of drive complexity is voltage controlled, driver controlled, and program controlled */