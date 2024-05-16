#include "vex.h"

//Even though class is declared in drive.h, it will be easier to work with the actual code if it is within its own file


subRotation::subRotation(int32_t Port) : rotation(Port){
    rotation::datarate(10);
}

 


    

float Drive::poll_chord(){
    //First thing to do is to retrieve the encoder positions
    float parallel_rotation = parallel.position(vex::degrees);
    float perpendicular_rotation = perpendicular.position(vex::degrees);
    
    
    //Convert to radians because that's what trig functions take
    I_heading = to_rad(I.heading());
    
    
    

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

float Drive::poll_x_odom(){

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

float Drive::poll_y_odom(){

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

void Drive::drive_to_coordinate(float x, float y){

    //Update odom
    poll_x_odom();

    //Find distances from current position
    float delta_x = x-Global_x_position;
    float delta_y = y-Global_y_position;

    float needed_angle = to_deg(atan(delta_x/delta_y));
    float needed_distance = sqrt((delta_x*delta_x)+(delta_y*delta_y));


    turn_to(needed_angle);
    drive_for(needed_distance);
    


}