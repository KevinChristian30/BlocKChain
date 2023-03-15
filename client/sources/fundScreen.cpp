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
    puts("3. Back");
    printf(">> ");

  }

  void getInput(char input[]){

    scanf("%[^\n]", input);
    getchar();

  }

  namespace deposit{

    void loop(){

      char buffer[BUFFERSIZE];
      unsigned long long int amount;
      while (true){

        utility::clear();
        displayLogo();    

        printf("\nEnter Deposit Amount [0 to Cancel]: ");
        scanf("%[^\n]", buffer);
        getchar();

        // Validasi Numeric Only
        size_t length = strlen(buffer);
        bool isNumericOnly = true;
        for (size_t i = 0; i < length; i++) {

          if (buffer[i] < '0' || buffer[i] > '9') {

            utility::setColor("FOREGROUND_RED");
            printf("\nYou Must Input a Positive Number");
            utility::setColor("FOREGROUND_WHITE");
            getchar();

            isNumericOnly = false;
            break;

          }

        }

        if (!isNumericOnly) continue;

        amount = atoi(buffer);
        if (amount < 0){

          utility::setColor("FOREGROUND_RED");
          printf("\nAmount Must be Positive");
          utility::setColor("FOREGROUND_WHITE");

          getchar();

        } else if (amount == 0) {

          utility::setColor("FOREGROUND_BLUE");
          utility::animateString("\nDeposit Cancelled", 20);
          utility::setColor("FOREGROUND_WHITE");

          getchar();
          return;

        } else break;

      }

      Transaction* toCreate = createTransaction((char*) "DP", currentUser->username, (unsigned long long int) amount);
      database::transaction::create(*toCreate);

      utility::setColor("FOREGROUND_GREEN");
      utility::animateString("\nBlue Token(s) Added to Transactions!", 20);
      utility::setColor("FOREGROUND_WHITE");
      getchar();

    }

  }

  namespace withdraw{

    void loop(){

      char buffer[BUFFERSIZE];
      unsigned long long int amount;
      while (true){

        utility::clear();
        displayLogo();    

        printf("\nEnter Withdraw Amount [0 to cancel]: ");
        scanf("%[^\n]", &buffer);
        getchar();

        // Validasi Numeric Only
        size_t length = strlen(buffer);
        bool isNumericOnly = true;
        for (size_t i = 0; i < length; i++) {

          if (buffer[i] < '0' || buffer[i] > '9') {

            utility::setColor("FOREGROUND_RED");
            printf("\nYou Must Input a Positive Number");
            utility::setColor("FOREGROUND_WHITE");
            getchar();

            isNumericOnly = false;
            break;

          }

        }

        if (!isNumericOnly) continue;

        amount = atoi(buffer);

        if (amount < 0){

          utility::setColor("FOREGROUND_RED");
          printf("\nAmount Must be Positive");
          utility::setColor("FOREGROUND_WHITE");

          getchar();

        } else if (amount == 0) {

          utility::setColor("FOREGROUND_BLUE");
          utility::animateString("\nWithdrawal Cancelled", 20);
          utility::setColor("FOREGROUND_WHITE");

          getchar();
          return;

        } else if (amount > currentUser->fund){

          utility::setColor("FOREGROUND_RED");
          printf("\nYou don't Have Enough Money");
          utility::setColor("FOREGROUND_WHITE");

          getchar();

        } else break;

      }

      Transaction* toCreate = createTransaction(currentUser->username,
      (char*) "WD", (unsigned long long int) amount);
      database::transaction::create(*toCreate);

      currentUser->fund -= amount;
      database::account::update(currentUser);

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

    currentUser = database::account::findByUsername(user->username);

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