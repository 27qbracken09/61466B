#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "v5.h"
#include "v5_vcs.h"

//Custom Includes
#include <iostream>
#include <sstream>

//Custom Headers

//Allows this to be accessed by the rest of the program files
#include "drive.h"
#include "pid.h"
#include "util.h"
#include "modules.h"

//Graphics Library files
#include "v5lvgl.h"

#define PROG_NAME "Rewrite"

#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)

extern vex::brain Brain;