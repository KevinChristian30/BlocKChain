#include <stdio.h>

#ifndef FUNDSCREEN_CPP
#define FUNDSCREEN_CPP

#include "../models/Account.h"
#include "../models/Transaction.h"

#include "../headers/utility.h"
#include "../headers/globals.h"
#include "../headers/database.h"

namespace fundScreen{

  Account* currentUser;

  void displayLogo(){

    const char LOGO[8 + 1][47 + 1] = {
      
      " /$$$$$$$$                        /$$          ",
      "| $$_____/                       | $$          ",
      "| $$    /$$   /$$ /$$$$$$$   /$$$$$$$  /$$$$$$$",
      "| $$$$$| $$  | $$| $$__  $$ /$$__  $$ /$$_____/",
      "| $$__/| $$  | $$| $$  \\ $$| $$  | $$|  $$$$$$ ",
      "| $$   | $$  | $$| $$  | $$| $$  | $$ \\____  $$",
      "| $$   |  $$$$$$/| $$  | $$|  $$$$$$$ /$$$$$$$/",
      "|__/    \\______/ |__/  |__/ \\_______/|_______/ ",
      
    };

    utility::setColor("FOREGROUND_BLUE");
    for (short i = 0; i < 8; i++) printf("%s\n", LOGO[i]);
    utility::setColor("FOREGROUND_WHITE");

  }

  void display(){

    displayLogo();
    puts("");

    utility::setColor("FOREGROUND_BLUE");
    printf("Blue Tokens: %llu\n", currentUser->fund);
    utility::setColor("FOREGROUND_WHITE");
    
    puts("1. Deposit");
    puts("2. Withdraw");
    puts("3. Exit");
    printf(">> ");

  }

  void getInput(char input[]){

    scanf("%[^\n]", input);
    getchar();

  }

  namespace deposit{

    void loop(){

      long long int buffer;
      while (true){

        utility::clear();
        displayLogo();    

        printf("\nEnter Deposit Amount: ");
        scanf("%lld", &buffer);
        getchar();

        if (buffer <= 0){

          utility::setColor("FOREGROUND_RED");
          printf("\nAmount Must be Positive");
          utility::setColor("FOREGROUND_WHITE");

          getchar();

        } else break;

      }

      Transaction* toCreate = createTransaction((char*) "DP", currentUser->username, (unsigned long long int) buffer);
      database::transaction::create(*toCreate);

      utility::setColor("FOREGROUND_GREEN");
      utility::animateString("\nBlue Token(s) Added to Transactions!", 20);
      utility::setColor("FOREGROUND_WHITE");
      getchar();

    }

  }

  namespace withdraw{

    void loop(){

      long long int buffer;
      while (true){

        utility::clear();
        displayLogo();    

        printf("\nEnter Withdraw Amount: ");
        scanf("%lld", &buffer);
        getchar();

        if (buffer <= 0){

          utility::setColor("FOREGROUND_RED");
          printf("\nAmount Must be Positive");
          utility::setColor("FOREGROUND_WHITE");

          getchar();

        } else break;

      }

      Transaction* toCreate = createTransaction((char*) "WD", currentUser->username, (unsigned long long int) buffer);
      database::transaction::create(*toCreate);

      utility::setColor("FOREGROUND_GREEN");
      utility::animateString("\nBlue Token(s) Withdrawal Added to Transactions!", 20);
      utility::setColor("FOREGROUND_WHITE");
      getchar();

    }

  }

  bool route(char input[]){

    if (strncmp(input, "1", BUFFERSIZE) == 0) deposit::loop();
    else if (strncmp(input, "2", BUFFERSIZE) == 0) withdraw::loop();
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