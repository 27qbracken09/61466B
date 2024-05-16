#pragma once
#include "vex.h"


enum level{DEBUG, STATUS, WARNING, FATAL};

//Logging System Config
#define LOG_LEVEL DEBUG //Masks Unnessisary Logs
#define STORE_LOGS 0 //Enable Storing logs in brain memory

//Log system inspired by this post: https://www.vexforum.com/t/can-someone-do-a-code-review-on-my-code/123998
void log(std::string location, int msg_level, std::string msg);