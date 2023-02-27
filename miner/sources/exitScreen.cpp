#include <stdio.h>
#include <windows.h>

#ifndef EXITSCREEN_CPP
#define EXITSCREEN_CPP

#include "../headers/utility.h"

namespace exitScreen{

  void display(){

    utility::setColor("FOREGROUND_BLUE");
    utility::animateString("Thanks for Using BlueMiner, Happy Mining!", 20);
    utility::setColor("FOREGROUND_WHITE");

  }

  void loop(){

    utility::clear();
    display();
    getchar();
    exit(0);
    
  }

}

#endif