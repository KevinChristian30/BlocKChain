#include <stdio.h>

#ifndef MAINMENUSCREEN_CPP
#define MAINMENUSCREEN_CPP

#include "../models/Account.h"

#include "../headers/utility.h"
#include "../sources/globals.cpp"
#include "../headers/myAccountScreen.h"
#include "../headers/transactionScreen.h"
#include "../headers/fundScreen.h"

namespace mainMenuScreen{

  Account *currentUser;

  void displayLogo(){

    const char logo[8+ 1][86 + 1] = {
      
      " /$$      /$$           /$$                 /$$      /$$                              ",
      "| $$$    /$$$          |__/                | $$$    /$$$                              ",
      "| $$$$  /$$$$  /$$$$$$  /$$ /$$$$$$$       | $$$$  /$$$$  /$$$$$$  /$$$$$$$  /$$   /$$",
      "| $$ $$/$$ $$ |____  $$| $$| $$__  $$      | $$ $$/$$ $$ /$$__  $$| $$__  $$| $$  | $$",
      "| $$  $$$| $$  /$$$$$$$| $$| $$  \\ $$      | $$  $$$| $$| $$$$$$$$| $$  \\ $$| $$  | $$",
      "| $$\\  $ | $$ /$$__  $$| $$| $$  | $$      | $$\\  $ | $$| $$_____/| $$  | $$| $$  | $$",
      "| $$ \\/  | $$|  $$$$$$$| $$| $$  | $$      | $$ \\/  | $$|  $$$$$$$| $$  | $$|  $$$$$$/",
      "|__/     |__/ \\_______/|__/|__/  |__/      |__/     |__/ \\_______/|__/  |__/ \\______/ "
                                                                                      
    };

    utility::setColor("FOREGROUND_GREEN");
    for (short i = 0; i < 8; i++) printf("%s\n", logo[i]);
    utility::setColor("FOREGROUND_WHITE");

  }

  void display(){

    utility::clear();
    displayLogo();
    
    printf("\nWelcome,");

    utility::setColor("FOREGROUND_BLUE");
    printf(" %s\n\n", currentUser->username);
    utility::setColor("FOREGROUND_WHITE");

    puts("1. Funds");
    puts("2. Transactions");
    puts("3. My Account");
    puts("4. Log Out");
    printf(">> ");

  }

  void getInput(char storage[]){

    scanf("%[^\n]", storage);
    getchar();

  }

  bool route(char input[]){

    if (strncmp(input, "1", BUFFERSIZE) == 0) fundScreen::loop(currentUser);
    else if (strncmp(input, "2", BUFFERSIZE) == 0) transactionScreen::loop(currentUser);
    else if (strncmp(input, "3", BUFFERSIZE) == 0) myAccountScreen::loop(currentUser);
    else if (strncmp(input, "4", BUFFERSIZE) == 0) return false;
    
    return true;

  }

  void loop(Account *user){

    currentUser = user;

    char input[BUFFERSIZE];
    while (true){

      utility::clear();      
      display();
      getInput(input);
      if (!route(input)) break;

    }

  }

}

#endif