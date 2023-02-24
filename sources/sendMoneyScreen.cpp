#include <stdio.h>

#ifndef SENDMONEYSCREEN_CPP
#define SENDMONEYSCREEN_CPP

#include "../models/Account.h"
#include "../headers/globals.h"
#include "../headers/utility.h"

namespace sendMoneyScreen{

  void displayLogo(){

    const char LOGO[8 + 1][40 + 1] = {

      "  /$$$$$$                            /$$",
      " /$$__  $$                          | $$",
      "| $$  \\__/  /$$$$$$  /$$$$$$$   /$$$$$$$",
      "|  $$$$$$  /$$__  $$| $$__  $$ /$$__  $$",
      " \\____  $$| $$$$$$$$| $$  \\ $$| $$  | $$",
      " /$$  \\ $$| $$_____/| $$  | $$| $$  | $$",
      "|  $$$$$$/|  $$$$$$$| $$  | $$|  $$$$$$$",
      " \\______/  \\_______/|__/  |__/ \\_______/"

    };

    utility::setColor("FOREGROUND_BLUE");
    for (short i = 0; i < 8; i++) printf("%s\n", LOGO[i]);
    utility::setColor("FOREGROUND_WHITE");

  }

  void display(){

    displayLogo();
    puts("");

  }

  void loop(Account* currentUser){

    char input[BUFFERSIZE];
    while (true){

      utility::clear();
      display();
      getchar();

    }

  }

}

#endif