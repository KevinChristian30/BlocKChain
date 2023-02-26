#include <stdio.h>

#ifndef VIEWTRANSACTIONSCREEN_CPP
#define VIEWTRANSACTIONSCREEN_CPP

#include "../models/Account.h"

#include "../headers/utility.h"
#include "../headers/globals.h"
#include "../headers/ongoingTransactionScreen.h"

namespace viewTransactionScreen{

  Account* currentUser;

  void displayLogo(){

    const char LOGO[8 + 1][110 + 1] = {

      " /$$$$$$$$                                                           /$$     /$$                              ",
      "|__  $$__/                                                          | $$    |__/                              ",
      "   | $$  /$$$$$$  /$$$$$$  /$$$$$$$   /$$$$$$$  /$$$$$$   /$$$$$$$ /$$$$$$   /$$  /$$$$$$  /$$$$$$$   /$$$$$$$",
      "   | $$ /$$__  $$|____  $$| $$__  $$ /$$_____/ |____  $$ /$$_____/|_  $$_/  | $$ /$$__  $$| $$__  $$ /$$_____/",
      "   | $$| $$  \\__/ /$$$$$$$| $$  \\ $$|  $$$$$$   /$$$$$$$| $$        | $$    | $$| $$  \\ $$| $$  \\ $$|  $$$$$$ ",
      "   | $$| $$      /$$__  $$| $$  | $$ \\____  $$ /$$__  $$| $$        | $$ /$$| $$| $$  | $$| $$  | $$ \\____  $$",
      "   | $$| $$     |  $$$$$$$| $$  | $$ /$$$$$$$/|  $$$$$$$|  $$$$$$$  |  $$$$/| $$|  $$$$$$/| $$  | $$ /$$$$$$$/",
      "   |__/|__/      \\_______/|__/  |__/|_______/  \\_______/ \\_______/   \\___/  |__/ \\______/ |__/  |__/|_______/ "

    };

    utility::setColor("FOREGROUND_BLUE");
    for (short i = 0; i < 8; i++) printf("%s\n", LOGO[i]);
    utility::setColor("FOREGROUND_WHITE");

  }

  void display(){

    displayLogo();
    puts("");
    puts("1. Ongoing Transactions");
    puts("2. Finalized Transactions");
    puts("3. Back");
    printf(">> ");

  }

  void getInput(char storage[]){

    scanf("%[^\n]", storage);
    getchar();

  }

  bool route(char input[]){

    if (strncmp(input, "1", BUFFERSIZE) == 0) ongoingTransactionScreen::loop(currentUser);
    else if (strncmp(input, "2", BUFFERSIZE) == 0) puts("Finalized Transactions");
    else if (strncmp(input, "3", BUFFERSIZE) == 0) return false; 

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