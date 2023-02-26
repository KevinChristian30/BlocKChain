#include <stdio.h>

#ifndef MYACCOUNTSCREEN_CPP
#define MYACCOUNTSCREEN_CPP

#include "../models/Account.h"
#include "../headers/utility.h"
#include "../headers/changePasswordScreen.h"

namespace myAccountScreen{

  Account* currentUser;

  const char LOGO[10 + 1][99 + 1] = {

    " /$$      /$$                  /$$$$$$                                                      /$$    ",
    "| $$$    /$$$                 /$$__  $$                                                    | $$    ",
    "| $$$$  /$$$$ /$$   /$$      | $$  \\ $$  /$$$$$$$  /$$$$$$$  /$$$$$$  /$$   /$$ /$$$$$$$  /$$$$$$  ",
    "| $$ $$/$$ $$| $$  | $$      | $$$$$$$$ /$$_____/ /$$_____/ /$$__  $$| $$  | $$| $$__  $$|_  $$_/  ",
    "| $$  $$$| $$| $$  | $$      | $$__  $$| $$      | $$      | $$  \\ $$| $$  | $$| $$  \\ $$  | $$    ",
    "| $$\\  $ | $$| $$  | $$      | $$  | $$| $$      | $$      | $$  | $$| $$  | $$| $$  | $$  | $$ /$$",
    "| $$ \\/  | $$|  $$$$$$$      | $$  | $$|  $$$$$$$|  $$$$$$$|  $$$$$$/|  $$$$$$/| $$  | $$  |  $$$$/",
    "|__/     |__/ \\____  $$      |__/  |__/ \\_______/ \\_______/ \\______/  \\______/ |__/  |__/   \\___/  ",
    "              /$$  | $$                                                                            ",
    "             |  $$$$$$/                                                                            ",
    "              \\______/                                                                             "

  };

  void displayLogo(){

    utility::setColor("FOREGROUND_BLUE");
    for (short i = 0; i < 10; i++) printf("%s\n", LOGO[i]);
    utility::setColor("FOREGROUND_WHITE");

  }

  void display(){

    displayLogo();
    puts("");
    puts("1. Change Password");
    puts("2. Back");
    printf(">> ");

  }

  void getInput(char storage[]){

    scanf("%[^\n]", storage);
    getchar();                                                    

  }

  bool route(char input[]){

    if (strncmp(input, "1", BUFFERSIZE) == 0) changePasswordScreen::loop(currentUser);
    else if (strncmp(input, "2", BUFFERSIZE) == 0) return false;

    return true;

  }

  void loop(Account* user){

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