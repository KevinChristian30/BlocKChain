#include <stdio.h>

#ifndef MAINMENUSCREEN_CPP
#define MAINMENUSCREEN_CPP

#include "../models/Account.h"
#include "../headers/utility.h"

namespace mainMenuScreen{

  Account *currentUser;

  void display(){

    puts("Main Menu");

  }

  void loop(Account *currentUser){

    while (true){

      utility::clear();
      
      display();
      
      getchar();

    }

  }

}

#endif