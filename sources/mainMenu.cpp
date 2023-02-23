#include <stdio.h>

#include "../models/Account.h"
#include "../headers/utility.h"

#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

namespace mainMenu{

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