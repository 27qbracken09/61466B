#include "vex.h"

//Even though class is declared in drive.h, it will be easier to work with the actual code if it is within its own file

//Compounded constructor - Will work on after absolute
//Drive::odom::odom() : parallel(NULL), perpendicular(NULL), odom_drive(){}

//To access the Gyroscope/inertial, we needed to pass the location of the drivetrain that the user created, thats what the & is for
//Then we stored that in a "new" object
//We then could access the gyro info through that new object, though it was the original object info.

//Absolute
Drive::odom::odom(int Parallel_to_wheels_tracker_port, int Perpendicular_to_wheels_tracker_port, float Parallel_distance_from_center, float Perpendicular_distance_from_center, float Tracking_wheel_diameter, Drive &drivetrain) : 
parallel(Parallel_to_wheels_tracker_port), 
perpendicular(Perpendicular_to_wheels_tracker_port),

parallel_dist_from_center(Parallel_distance_from_center),
perpendicular_dist_from_center(Perpendicular_distance_from_center),

tracked_wheel_ratio((Tracking_wheel_diameter*M_PI)/360),
odom_drive(drivetrain)

{}
    

float Drive::odom::poll_chord(){
    //First thing to do is to retrieve the encoder positions
    float parallel_rotation = parallel.position(vex::degrees);
    float perpendicular_rotation = perpendicular.position(vex::degrees);
    
    
    //Convert to radians because that's what trig functions take
    I_heading = to_rad(odom_drive.I.heading());
    
    
    

    //Second, convert them into distances traveled by the wheel
    float parallel_distance = parallel_rotation*tracked_wheel_ratio;
    float perpendicular_distance = perpendicular_rotation*tracked_wheel_ratio;

    //Third, calculate respective radii
    //Don't forget that if the perpendicular tracker is behind the robot, the distance is negative
    float parallel_radius = (parallel_distance/I_heading)+parallel_dist_from_center;
    float perpendicular_radius = perpendicular_distance/I_heading+perpendicular_dist_from_center;


    //Finally calculate chord using the 1/2 sine law - Equation for this one is 2R * Sin(heading/2) - R is the radius of the tracking center arc
    y_chord = 2*parallel_radius*(sin(I_heading/2));
    x_chord = 2*perpendicular_radius*(sin(I_heading/2));

    return y_chord;



}

float Drive::odom::poll_x_odom(){

    //Update vars - Calculate chord
    poll_chord();

    //Convert Local Coordinate system to Global
    Global_x_position = cos(I_heading)*y_chord;
    Global_y_position = (sin(I_heading)*y_chord)+x_chord;

    //Apply starting offsets

    Global_x_position += start_x_offset;
    Global_y_position += start_y_offset;

    return Global_x_position;
}

float Drive::odom::poll_y_odom(){

    //Update vars - Calculate chord
    poll_chord();

    //Convert Local Coordinate system to Global
    Global_x_position = cos(I_heading)*y_chord;
    Global_y_position = (sin(I_heading)*y_chord)+x_chord;

    //Apply starting offsets

    Global_x_position += start_x_offset;
    Global_y_position += start_y_offset;

    return Global_y_position;
}

