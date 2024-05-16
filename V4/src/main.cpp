

#include "vex.h" //Include all dependencies from other files
using namespace vex;
competition Competition; //Declare competition object

/******************************************************************************/
/*                                 Main.cpp                                   */
/******************************************************************************/
/* From the lowly single file, to the largest ever, this file orchestrates it */
/* all. If it's not called here, it won't run. This is the root of the entire */
/* program, it generates, and destroys parents and children alike ;)          */
/*                                                                            */
/* This file is where the program starts, line one gets called, then line two */
/* and so on. It handles important constructors, like the compeition          */
/* constructors so that your robot will work during the competition           */
/******************************************************************************/

/////////////////////////
//Global Stuff
/////////////////////////////

//Wheel ports LF, LB, RF, RB, Gyro, Wheel Size - sets up the chassis
Drive chassis(PORT15,PORT14,PORT13,PORT12,PORT3,4.125);



//Auton Settings            
int current_auton_selection = 1;
//This is the default auton that will be selected, keeps track of auton - See Auton Selector and switch statement 
bool auto_started = false; // Just a declaration, when auton starts this will be set to true 

////////////////////////////////////////////

//Auton Selector - This is called when the auton dropdown recieves an event
void auton_selector(lv_event_t * event)
{
    //The code is what type of what type of event happened
    lv_event_code_t code = lv_event_get_code(event);

    //This is the actual event stored as an object
    lv_obj_t * obj = lv_event_get_target(event);
    
    //Now check if there was a new value (Name) selected in the Dropdown
    if(code == LV_EVENT_VALUE_CHANGED) {
        
        //Declare a buffer, used for getting text
        char buf[32];

        //Get name of what was selected
        lv_dropdown_get_selected_str(obj, buf, sizeof(buf));

        //Convert to string so it will play nice
        std::string sbuf = buf;

        //Each of these is an auton selection, this one is short because it is none
        if (sbuf == "None"){ current_auton_selection = 0; std::cout << "No Auton Selected!\n";}

        //Check if auton is a name
        else if (sbuf == "Left"){

          //Log data, so I can figure out when something goes wrong
          std::cout << "Left Auton Selected\n";

          //Do the magic, and change the selected auton
          current_auton_selection = 1;
        }

        else if (sbuf == "Right"){
          std::cout << "Right Auton Selected\n";
          current_auton_selection = 2;
        }

        else if (sbuf == "Full"){
          std::cout << "Full Auton Selected\n";
          current_auton_selection = 3;
        }
    }
}

//Callback for when the clear sensors button was pressed
void clr_snsrs_btn_cb(lv_event_t * event){

  //This will calibrate the gyro as well as clearing the sensors
  chassis.clearSensors(true);
  chassis.clearSensors(false);

  //Log Data
  std::cout << "Sensors Cleared\n";
}

//Test Auton Button Callback
void tst_atn_cb(lv_event_t * event){

  //Lets us know that button press was recognized and running auton selector
  std::cout << "Testing Auton\n";

  //Check what auton is selected
  switch(current_auton_selection){  
    case 0:
      //Run auton - this one is a more of a DONT MOVE
      no_auton();
      std::cout << "No Auton Selected!\n";
      break;
    case 1:
      std::cout << "Left Auton Started\n";
      left_auton();
      
      
      break;
    case 2:
      std::cout << "Right Auton Started\n";
      right_auton();
      
      
      break;
    case 3:
      
      break;
    case 4:
      
      break;
    
 } //Switch
  std::cout << "Auton Ended\n";

}
//Sensor Labels are here for the function below


//Label will not printf floats, so I have to make 2 labels one for float and one for name.
  //I put them in an object for easier useability

  //Note to Self: Research and fix printf label later
  static lv_style_t sensor_readout_style;


  //Rotation Value
  lv_obj_t * LF_ROT;
  lv_obj_t * LB_ROT;

  lv_obj_t * RF_ROT;
  lv_obj_t * RB_ROT;

  lv_obj_t * GYRO_ROT;

  lv_obj_t * DRV_TMP;

  //Name Label
  lv_obj_t * LF_ROT_LBL;
  lv_obj_t * LB_ROT_LBL;

  lv_obj_t * RF_ROT_LBL;
  lv_obj_t * RB_ROT_LBL;

  lv_obj_t * GYRO_ROT_LBL;

  lv_obj_t * DRV_TMP_LBL;

  //Container
  lv_obj_t * LF_ROT_CONT;
  lv_obj_t * LB_ROT_CONT;

  lv_obj_t * RF_ROT_CONT;
  lv_obj_t * RB_ROT_CONT;

  lv_obj_t * GYRO_ROT_CONT;

  lv_obj_t * DRV_TMP_CONT;

  //Yikes! Triple the amount of objects

//Update Sensors
void updateSensorText(float LF_readout, float LB_readout, float RF_readout, float RB_readout, float Gyro_readout){
  char buf[32];
  //Convert float to char and store in buf, then set text
  sprintf(buf, "%2.2f", LF_readout);
  lv_label_set_text(LF_ROT, buf);

  sprintf(buf, "%2.2f", LB_readout);
  lv_label_set_text(LB_ROT, buf);

  sprintf(buf, "%2.2f", RF_readout);
  lv_label_set_text(RF_ROT, buf);

  sprintf(buf, "%2.2f", RB_readout);
  lv_label_set_text(RB_ROT, buf);

  //Detect if Gyro is Calibrating & Update size of Container
  if(chassis.Gyro.isCalibrating()){lv_label_set_text(GYRO_ROT, "Calibrate"); lv_obj_set_size(GYRO_ROT_CONT, 225, LV_SIZE_CONTENT);}
  else{
  //Make sure container is right size (200)
  sprintf(buf, "%2.2f", Gyro_readout);
  lv_label_set_text(GYRO_ROT, buf);
  lv_obj_set_size(GYRO_ROT_CONT, 200, LV_SIZE_CONTENT);
  }

}

//This is experimental it does not work right now
void log(char msg[256]){
  if (Brain.SDcard.isInserted()){
    FILE * file = fopen("Log_V3_1.txt", "a");
    fprintf(file, "%s", msg);
    fclose(file);
  }
}



void pre_auton(){
  std::cout << "Verson 4.2 Started\n" << "Battery: " << Brain.Battery.capacity() << "%\n\n";
  
  std::cout << "Pre Auton Started\n";

  ///////////////////////
  //Initialize Stuff that needs to be initialized before comp starts
  ////////////////////////////////////////////

  //Little V Graphics Library Init
  v5_lv_init();

  //Calibrate Gyroscope
  chassis.Gyro.calibrate();

  //Declare PID constants
  chassis.SetPID(0.1, 0.1, 0.08, 0,3,5000,50000);
  std::cout << "PID Set\n";

  chassis.SetTurnPID(0.1, 0.1, 0.17, 0,0.5,10000,10000);
  std::cout << "Turn PID Set\n";




  
  /////////////////////////
  //lv Background
  ///////////////////////////////////////////////////////
  static lv_style_t scr;
  lv_obj_t * name_label;

  //Start Style
  lv_style_init(&scr);

  //Set Bacground color (purple)
  lv_style_set_bg_color(&scr, lv_color_hex(0x540053));
  lv_obj_add_style(lv_scr_act(), &scr, 0);

  //Create Name and version label
  name_label = lv_label_create(lv_scr_act());
  lv_obj_set_size(name_label, 100, 50);
  lv_obj_set_align(name_label, LV_ALIGN_TOP_RIGHT);

  lv_label_set_text(name_label, "61466B V0.3");
  //////////////////////////////////////////////////////////////////////

  ///////////////////////////
  //Auton Selector
  /////////////////////////////////////////////////////////////////////
  static lv_style_t auton_label_style;
  lv_obj_t * auton_label;

  static lv_style_t auton_selection_style;
  lv_obj_t * auton_selection;

  static lv_style_t clear_sensors_style;
  lv_obj_t * clear_sensors_btn;
  lv_obj_t * clear_sensors_btn_lbl;

  static lv_style_t test_auton_style;
  lv_obj_t * test_auton_btn;
  lv_obj_t * test_auton_btn_lbl;

  lv_obj_t * PID_Tuner_Btn;


  //Create Custom Grey Color
  lv_color_t grey = lv_palette_darken(LV_PALETTE_GREY, 3);

  //Auton Label Style
  lv_style_init(&auton_label_style);
  lv_style_set_text_font(&auton_label_style, &lv_font_montserrat_28);

  //Create Auton Label and set Position
  auton_label = lv_label_create(lv_scr_act());
  lv_obj_add_style(auton_label, &auton_label_style, 0);
  lv_label_set_text(auton_label, "Autonomous: ");
  lv_obj_align(auton_label, LV_ALIGN_TOP_LEFT, 10, 0);
  
  //Auton Selector Style
  lv_style_init(&auton_selection_style);
  lv_style_set_bg_color(&auton_selection_style,grey);

  //Create Auton Selector Dropdown
  auton_selection = lv_dropdown_create(lv_scr_act());
  lv_obj_add_style(auton_selection, &auton_selection_style, 0);
  lv_dropdown_set_options(auton_selection, "None\n" "Left\n" "Right\n" "Full");
  lv_obj_align(auton_selection,LV_ALIGN_LEFT_MID, 35, -65);
  lv_obj_add_event_cb(auton_selection, auton_selector, LV_EVENT_ALL, NULL);

  
  //Clear Sensors Style
  lv_style_init(&clear_sensors_style);
  lv_style_set_bg_color(&clear_sensors_style, grey);

  //Clear sensors button
  clear_sensors_btn = lv_btn_create(lv_scr_act());
  lv_obj_add_style(clear_sensors_btn, &clear_sensors_style, 0);
  lv_obj_align(clear_sensors_btn,LV_ALIGN_LEFT_MID, 45, -10);
  lv_obj_add_event_cb(clear_sensors_btn, clr_snsrs_btn_cb, LV_EVENT_PRESSED, NULL);

  //Clear sensors text
  clear_sensors_btn_lbl = lv_label_create(clear_sensors_btn);
  lv_label_set_text(clear_sensors_btn_lbl, "Clear Sensors");
  
  //Test auton button style
  lv_style_init(&test_auton_style);
  lv_style_set_bg_color(&test_auton_style, grey);

  //Auton Button
  test_auton_btn = lv_btn_create(lv_scr_act());
  lv_obj_add_style(test_auton_btn, &test_auton_style, 0);
  lv_obj_align(test_auton_btn, LV_ALIGN_LEFT_MID, 56, 45);
  lv_obj_add_event_cb(test_auton_btn, tst_atn_cb, LV_EVENT_PRESSED, NULL);

  //Auton Button Text
  test_auton_btn_lbl = lv_label_create(test_auton_btn);
  lv_label_set_text(test_auton_btn_lbl, "Test Auton");

  //Tuner Button (Not Working)
  /*
  PID_Tuner_Btn = lv_btn_create(lv_scr_act());
  lv_obj_add_style(PID_Tuner_Btn, &auton_selection_style, 0);
  lv_obj_align(PID_Tuner_Btn, LV_ALIGN_BOTTOM_LEFT, 0, 0); 
  */

  /////////////////////////////////////////////////////////////////////////

  //////////////////////////////
  //Sensor Readouts
  ////////////////////////////////////////////////////////////

  


  //Start Sensor Readout Style
  lv_style_init(&sensor_readout_style);
  lv_style_set_text_font(&sensor_readout_style, &lv_font_montserrat_16);

  //Make the container blend in
  lv_style_set_bg_color(&sensor_readout_style, lv_color_hex(0x540053));
  //Note to Self: Set Border color as well
  lv_style_set_border_color(&sensor_readout_style,lv_color_hex(0x540053));

  //Create Containers
  LF_ROT_CONT = lv_obj_create(lv_scr_act());
  LB_ROT_CONT = lv_obj_create(lv_scr_act());
  RF_ROT_CONT = lv_obj_create(lv_scr_act());
  RB_ROT_CONT = lv_obj_create(lv_scr_act());
  GYRO_ROT_CONT = lv_obj_create(lv_scr_act());

  //Set Main Style
  lv_obj_add_style(LF_ROT_CONT, &sensor_readout_style, 0);
  lv_obj_add_style(LB_ROT_CONT, &sensor_readout_style, 0);
  lv_obj_add_style(RF_ROT_CONT, &sensor_readout_style, 0);
  lv_obj_add_style(RB_ROT_CONT, &sensor_readout_style, 0);

  lv_obj_add_style(GYRO_ROT_CONT, &sensor_readout_style, 0);

 //Set Container Offset
 //Note to Self: Set R side offsets
 lv_obj_align(LF_ROT_CONT, LV_ALIGN_TOP_RIGHT, 0, 20);
 lv_obj_align(LB_ROT_CONT, LV_ALIGN_TOP_RIGHT, 0, 60);
 lv_obj_align(RF_ROT_CONT, LV_ALIGN_TOP_RIGHT, 0, 100);
 lv_obj_align(RB_ROT_CONT, LV_ALIGN_TOP_RIGHT, 0, 140);
 lv_obj_align(GYRO_ROT_CONT, LV_ALIGN_TOP_RIGHT, 0, 180);
 


  //Create Name Labels
  LF_ROT_LBL = lv_label_create(LF_ROT_CONT);
  LB_ROT_LBL = lv_label_create(LB_ROT_CONT);
  RF_ROT_LBL = lv_label_create(RF_ROT_CONT);
  RB_ROT_LBL = lv_label_create(RB_ROT_CONT);
  GYRO_ROT_LBL = lv_label_create(GYRO_ROT_CONT);

  //Set Label Align
  lv_obj_set_align(LF_ROT_LBL, LV_ALIGN_LEFT_MID);
  lv_obj_set_align(LB_ROT_LBL, LV_ALIGN_LEFT_MID);
  lv_obj_set_align(RF_ROT_LBL, LV_ALIGN_LEFT_MID);
  lv_obj_set_align(RB_ROT_LBL, LV_ALIGN_LEFT_MID);
  lv_obj_set_align(GYRO_ROT_LBL, LV_ALIGN_LEFT_MID);
  

  //Set Label Text
  lv_label_set_text(LF_ROT_LBL, "LF Rotation: ");
  lv_label_set_text(LB_ROT_LBL, "LB Rotation: ");
  lv_label_set_text(RF_ROT_LBL, "RF Rotation: ");
  lv_label_set_text(RB_ROT_LBL, "RB Rotation: ");

  lv_label_set_text(GYRO_ROT_LBL, "Gyro Rotate: ");

  //Create Actual Readout Label
  LF_ROT = lv_label_create(LF_ROT_CONT);
  LB_ROT = lv_label_create(LB_ROT_CONT);
  RF_ROT = lv_label_create(RF_ROT_CONT);
  RB_ROT = lv_label_create(RB_ROT_CONT);

  GYRO_ROT = lv_label_create(GYRO_ROT_CONT);

  //Set Readout Align
  lv_obj_set_align(LF_ROT, LV_ALIGN_RIGHT_MID);
  lv_obj_set_align(LB_ROT, LV_ALIGN_RIGHT_MID);
  lv_obj_set_align(RF_ROT, LV_ALIGN_RIGHT_MID);
  lv_obj_set_align(RB_ROT, LV_ALIGN_RIGHT_MID);

  lv_obj_set_align(GYRO_ROT, LV_ALIGN_RIGHT_MID);

  //Call inital text setting
  updateSensorText(chassis.LF.position(deg), chassis.LB.position(deg), chassis.RF.position(deg), chassis.RB.position(deg), chassis.Gyro.rotation(deg));

  //Due to Needing The Size of the Labels, Setting the container size is down here
  lv_obj_set_size(LF_ROT_CONT, 200, LV_SIZE_CONTENT);
  lv_obj_set_size(LB_ROT_CONT, 200, LV_SIZE_CONTENT);
  lv_obj_set_size(RF_ROT_CONT, 200, LV_SIZE_CONTENT);
  lv_obj_set_size(RB_ROT_CONT, 200, LV_SIZE_CONTENT);

  lv_obj_set_size(GYRO_ROT_CONT, 200, LV_SIZE_CONTENT);

  



  


  

  





  

  
  




  ///////////////////////////////////////////////////////////////////////
  

  
  //Update Wheel Positions
  //chassis.DriveFor(90);
  std::cout << "Pre Auton Completed!\n\n";
  while(true){
    
    updateSensorText(chassis.LF.position(deg), chassis.LB.position(deg), chassis.RF.position(deg), chassis.RB.position(deg), chassis.Gyro.rotation(deg));
    //std::cout << "\nLF Pos: " << chassis.LF.position(deg) << "\nLB Pos: " << chassis.LB.position(deg) << "\nRF Pos: " << chassis.RF.position(deg) << "\nRB Pos: " << chassis.RB.position(deg);
    wait(40,msec);
     

  }

  
  
}//Preauton
///////////////////////////////////////////////////////////
  

  




void autonomous(){
  std::cout << "Auton Started, current auton selected is: " << current_auton_selection << "\n";
  
 
  
  
  

  
  
 
  
////////////////
//Auton
////////////////////////////

  //Stop Auto Selector
  auto_started = true;

  //Run Auton Selected
  switch(current_auton_selection){  
    case 0:
      no_auton();
      break;
    case 1:
      left_auton();
      break;
    case 2:
      
      break;
    case 3:
      
      break;
    case 4:
      
      break;
    
 } //Switch
 std::cout << "Auton Ended\n\n";
//////////////////////////////////// 
} // Auton



void usercontrol(){
 std::cout << "User Control Started\n\n";
 
 
 
  
  //Update motor speeds using specified control method every 10 msec
  while(true){
  chassis.update(ARCADE_MECHANUM);
  cata.cata_motor.spin(forward, 12, volt);
  
  cata.update();
  
    wait(10,msec);
  } //While(true)
  std::cout << "User Control Ended\n\n";
} //Usercontrol





int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol); 
  pre_auton();

  while(true){wait(100,msec);}
  
  
} //Main

