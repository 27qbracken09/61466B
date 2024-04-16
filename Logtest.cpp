//#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <sstream>

#define MODULENAME "main.cpp"
#define LOG_LEVEL DEBUG

enum level{DEBUG, STATUS, WARNING, FATAL};

void log(std::string location, int msg_level, std::string msg);

using namespace std;
int main(){
    std::cout << "This is a test\n";
    log(MODULENAME, FATAL, "TESTING FATAL");
    log(MODULENAME, WARNING, "TESTING WARNING");
    log(MODULENAME, STATUS, "TESTING STATUS");
    log(MODULENAME, DEBUG, "TESTING DEBUG");
}

void log(std::string location, int msg_level, std::string msg){

    //Declare buffer to store all messages in - Improves communication speed when using serial connection
    std::ostringstream logBuffer;


    switch (msg_level){
        
        case FATAL:
            //I also liked the colors that the person in the post used - see modules.h
            //No level check, always display
            logBuffer << "\033[31;1m[FATAL] | Time: " << 10.3233 << " | Location: " << location << " > " << msg;

            break;
        
        case WARNING:
            //Check log level
            if (LOG_LEVEL <= WARNING) logBuffer << "\033[38;5;216m[WARNING] | Time: " << 10.3233 << " | Location: " << location << " > " << msg;
            
            //vexSystemExitRequest(); // Exit program
			//wait(2, vex::seconds);
            break;
        
        case STATUS:
            if (LOG_LEVEL <= STATUS) logBuffer << "\e[0;32m[STATUS] | Time: " << 10.3233  << " | Location: " << location << " > " << msg;
            break;

        case DEBUG:
            if (LOG_LEVEL <= DEBUG)  logBuffer << "\033[93m[DEBUG] | Time: " << 10.3233 << " | Location: " << location << " > " << msg;
            break;
        
        default: 
            logBuffer << "\033[38;5;216m[WARNING] | Time: " << 10.3233 << " | Location: " << location << " > " << msg;
            break;
        
        
    }
    std::cout << logBuffer.str() << "\033[0m\n";
}