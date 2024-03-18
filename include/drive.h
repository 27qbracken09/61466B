//I'm going to have the header files all feed into vex.h, so we need this compiler command to not go into an infinite loop
#pragma once

//Inclusion of vex.h
#include "vex.h"

//Declaration of different ways to drive - Refer to vex for control styles
enum drive_method{NO_DRIVE, TANK, SPLIT_ARCADE, COMB_ARCADE_L, COMB_ARCADE_R};

//Declaration of Drive class
//This allows me to create a "template" that can be easily modified by feeding it certain variables
//Sort of like a function on steroids
class Drive
{
    //Stuff in the public line can be accessed by other parts of my program, sort of like the front end of a service
    public:

        //Multiple class constructors so that I can "overload" them and have multiple argument amounts

        //6M Drive
        Drive(int L_Port1, int L_Port2, int L_Port3, int R_Port1, int R_Port2, int R_Port3, float wheel_size, int I_Port);
        
        //4M Drive
        Drive(int L_Port1, int L_Port2, int R_Port1, int R_Port2, float wheel_size, int I_Port);

        //2M Drive for whatever crazy reason
        Drive(int L_Port1, int R_Port1, float wheel_size, int I_Port);

        //Motors - Unused ones use the port NULL
        vex::motor L1;
        vex::motor L2;
        vex::motor L3;
        vex::motor R1;
        vex::motor R2;
        vex::motor R3;


        //Motor groups that the motors "feed" into so they can all be controlled together
        vex::motor_group L;
        vex::motor_group R;

        //Inertial to manage angle
        vex::inertial I;

        //Functions that can be used to control newly constructed Drivetrain
        
        //Drive with voltage is low level access to hardware
        void drive_with_voltage(float L_volt, float R_volt);

        //Next is driver control
        void update(enum::drive_method drive_method);

        //Finally, functions to Control the Robot Autonomously - Initial plans for development of this section start with a Drive straight command that stops at a specified motor rotation, no fancy algorithms.
        //Then add commands to turn to absolute degree value, again, no algorithms
        //Next create advanced commands that handle PID and accurate driving and turning.
        //Finally implement odometry and coordinate system.

        //Commands to Drive straight, w/o non-vex Algorithms
        void drive_for_degrees(float degree);

        //Advanced Algorithms - PID
        float drive_for(float inches);
        float turn_to(float degrees);

        

    //To start, we need an odometry class for odometry
    class odom
    {
        public:
            //Constructors
            //There are two types of odometry that I will be implementing, Compounded - It requires no tracking wheels. It is the one I can test over the summer
            // and Absolute, based off of this: https://www.youtube.com/watch?v=qqODIdvSGac
            // It requires 2 tracking wheels perpendicular to each other - This I cannot test as I do not have tracking wheels
            odom(); //This is the compounded version, and doesn't need to use anything extra
            odom(
                int Parallel_to_wheels_tracker_port, 
                int Perpendicular_to_wheels_tracker_port, 
                float Parallel_distance_from_center, 
                float Perpendicular_distance_from_center,
                float Tracking_wheel_diameter,

                //We need the location of the drivetrain object
                Drive &drivetrain
            );

            //poll_Odometry will need to run in a thread to continously update Position data
            float poll_x_odom();
            float poll_y_odom();

            //X and y positions that other functions can read from
            float Global_x_position;
            float Global_y_position;

            //Rotation Sensors
            vex::rotation parallel;
            vex::rotation perpendicular;

            //The "stuff" at the location of the drivetrain passed in the constructor
            Drive &odom_drive;

            

            

        private:
            
            //Stored constants
            float parallel_dist_from_center;
            float perpendicular_dist_from_center;
            float tracked_wheel_ratio;

            float start_x_offset;
            float start_y_offset;

            //Private chord updator
            float poll_chord();

            //Respective Vars
            float x_chord;
            float y_chord;
            float I_heading;
            
        

    };

    //Private Variables cannot be seen by other parts of the program
    private:
        float wheel_ratio;

        

    

};