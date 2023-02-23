#include <stdio.h>

#include "../models/Account.h"
#include "../headers/utility.h"

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
