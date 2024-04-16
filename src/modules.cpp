#include "vex.h"



void log(std::string location, int msg_level, std::string msg){

    //Declare buffer to store all messages in - Improves communication speed when using serial connection
    std::ostringstream logBuffer;


    switch (msg_level){
        
        case FATAL:
            //I also liked the colors that the person in the post used - see modules.h
            //No level check, always display
            logBuffer << "\033[31;1m[FATAL] | Time: " << ("%.3f", static_cast<float>(Brain.Timer.time(vex::seconds))) << " | Location: " << location << " > " << msg;

            vex::controller(vex::primary).Screen.clearScreen(); vex::controller(vex::primary).Screen.setCursor(1,1);
            vex::controller(vex::primary).Screen.print("FATAL ERROR");
            vex::controller(vex::primary).Screen.newLine();
            vex::controller(vex::primary).Screen.print(msg);

            wait(10, vex::seconds); //Allow time to read Error Message
            vexSystemExitRequest(); // Exit program
			wait(2, vex::seconds);

            break;
        
        case WARNING:
            //Check log level
            if (LOG_LEVEL <= WARNING) logBuffer << "\033[38;5;216m[WARNING] | Time: " << ("%.3f", static_cast<float>(Brain.Timer.time(vex::seconds))) << " | Location: " << location << " > " << msg;

            vex::controller(vex::primary).Screen.clearScreen(); vex::controller(vex::primary).Screen.setCursor(1,1);
            vex::controller(vex::primary).Screen.print("[WARNING]");
            vex::controller(vex::primary).Screen.newLine();
            vex::controller(vex::primary).Screen.print(msg);
           
            break;
        
        case STATUS:
            if (LOG_LEVEL <= STATUS) logBuffer << "\e[0;32m[STATUS] | Time: " << ("%0.3f", static_cast<float>(Brain.Timer.time(vex::seconds)))  << " | Location: " << location << " > " << msg;
            break;

        case DEBUG:
            if (LOG_LEVEL <= DEBUG)  logBuffer << "\033[93m[DEBUG] | Time: " << ("%.3f", static_cast<float>(Brain.Timer.time(vex::seconds))) << " | Location: " << location << " > " << msg;
            break;
        
        default: 
            logBuffer << "\033[38;5;216m[WARNING] | Time: " << ("%.3f", static_cast<float>(Brain.Timer.time(vex::seconds))) << " | Location: " << location << " > " << msg;
            break;
        
        
    }
    //Output log string to terminal
    std::cout << logBuffer.str() << "\033[0m\n";
}