#include "vex.h"


//Declare buffer to store all messages in - Improves communication speed when using serial connection
std::ostringstream logBuffer;

void log(std::string location, int msg_level, std::string msg){

    
    


    switch (msg_level){
        
        case FATAL:
            //I also liked the colors that the person in the post used - see modules.h
            //No level check, always display
            std::cout << "\033[31;1m[FATAL] | Time: " << Brain.Timer.value() << " | Location: " << location << " > " << msg << "\n";

             

            vex::controller(vex::primary).Screen.clearScreen(); vex::controller(vex::primary).Screen.setCursor(1,1);
            vex::controller(vex::primary).Screen.print("[FATAL ERROR]");
            vex::controller(vex::primary).Screen.newLine();
            vex::controller(vex::primary).Screen.print(msg.c_str());
            vex::controller(vex::primary).rumble("- -");

            wait(10, vex::seconds); //Allow time to read Error Message
            vexSystemExitRequest(); // Exit program
			wait(2, vex::seconds);

            break;
        
        case WARNING:
            //Check log level
            if (LOG_LEVEL <= WARNING) {logBuffer << "\033[38;5;216m[WARNING] | Time: " << Brain.Timer.value() << " | Location: " << location << " > " << msg << "\n";}

            vex::controller(vex::primary).Screen.clearScreen(); vex::controller(vex::primary).Screen.setCursor(1,1);
            vex::controller(vex::primary).Screen.print("[WARNING]");
            vex::controller(vex::primary).Screen.newLine();
            vex::controller(vex::primary).Screen.print(msg.c_str());
            
            break;
        
        case STATUS:
            if (LOG_LEVEL <= STATUS) logBuffer << "\e[0;32m[STATUS] | Time: " << Brain.Timer.value() << " | Location: " << location << " > " << msg << "\n";
            break;

        case DEBUG:
            if (LOG_LEVEL <= DEBUG)  logBuffer << "\033[93m[DEBUG] | Time: " << Brain.Timer.value() << " | Location: " << location << " > " << msg << "\n";
            break;
        
        default: 
            logBuffer << "\033[38;5;216m[WARNING] | Time: " << Brain.Timer.value() << " | Location: " << location << " > " << msg << "\n";
            break;
        
        
    }
    //Output log string to terminal
    
    
    if (!STORE_LOGS){
        std::cout << logBuffer.str() << "\033[0m";
        logBuffer.str("");

        
    }
    else std::cout << logBuffer.str() << "\033[0m";


}

void storeLogs(){
    if (Brain.SDcard.isInserted()){
        log("modules.storeLogs", DEBUG, "Storing Logs");
        std::ostringstream LogFileName;
        srand(43);
        LogFileName << "Log_File_" << rand() << ".html";
        std::string LogString = LogFileName.str();
         
        FILE * LogFile = fopen(LogString.c_str(), "w");


        std::string LogData = logBuffer.str();
        const char * cLogData = LogData.c_str();
        fputs(cLogData, LogFile);
        fclose(LogFile);
        log("modules.storeLogs", DEBUG, "Logs Stored");

        
        

        
        
    }
}