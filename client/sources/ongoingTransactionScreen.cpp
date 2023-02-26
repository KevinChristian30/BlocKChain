#include <stdio.h>
#include <iostream>
#include <vector>

#ifndef ONGOINGTRANSACTIONSCREEN_CPP
#define ONGOINGTRANSACTIONSCREEN_CPP

#include "../models/Account.h"

#include "../headers/utility.h"
#include "../headers/database.h"

namespace ongoingTransactionScreen{

  Account* currentUser;
  std::vector<Transaction*> transactions;

  void displayLogo(){

    const char LOGO[11 + 1][64 + 1] = {

      "  /$$$$$$                                /$$                    ",
      " /$$__  $$                              |__/                    ",
      "| $$  \\ $$ /$$$$$$$   /$$$$$$   /$$$$$$  /$$ /$$$$$$$   /$$$$$$ ",
      "| $$  | $$| $$__  $$ /$$__  $$ /$$__  $$| $$| $$__  $$ /$$__  $$",
      "| $$  | $$| $$  \\ $$| $$  \\ $$| $$  \\ $$| $$| $$  \\ $$| $$  \\ $$",
      "| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$| $$  | $$| $$  | $$",
      "|  $$$$$$/| $$  | $$|  $$$$$$$|  $$$$$$/| $$| $$  | $$|  $$$$$$$",
      " \\______/ |__/  |__/ \\____  $$ \\______/ |__/|__/  |__/ \\____  $$",
      "                     /$$  \\ $$                         /$$  \\ $$",
      "                    |  $$$$$$/                        |  $$$$$$/",
      "                     \\______/                          \\______/ ",

    };

    utility::setColor("FOREGROUND_BLUE");
    for (short i = 0; i < 11; i++) printf("%s\n", LOGO[i]);
    utility::setColor("FOREGROUND_WHITE");

  }

  void displayOptions(){

    puts("");
    puts("1. My Ongoing Transactions");
    puts("2. All Ongoing Transactions");
    puts("3. Search Someone's Ongoing Transactions");
    puts("4. Back");
    printf(">> ");

  }

  namespace myTransactions{

    void display(){

      bool dataAvailable = false;

      for (const auto& transaction : transactions)
        if (strncmp(transaction->sender, currentUser->username, BUFFERSIZE) == 0 ||
            strncmp(transaction->receiver, currentUser->username, BUFFERSIZE) == 0) dataAvailable = true;

      if (!dataAvailable){

        printf("\nNo Data!");
        return;

      }

      printf("\n\n");
      puts("Your Transactions");
      utility::putLine('=', 126);
      printf("| Sender                         | Receiver                       | Amount     | Hash       | Date                           |\n");
      
      utility::putLine('=', 126);

      for (const auto& transaction : transactions)
        if (strncmp(transaction->sender, currentUser->username, BUFFERSIZE) == 0 ||
            strncmp(transaction->receiver, currentUser->username, BUFFERSIZE) == 0)
              printf("| %-30s | %-30s | %-10llu | %-10s | %-30s |\n", transaction->sender,
                transaction->receiver, transaction->amount, transaction->hash, transaction->time);

      utility::putLine('=', 126);
      
    }

  }

  namespace allTransactions{

    void display(){

      if (transactions.size() <= 0) {

        printf("No Data!");
        return;

      }

      printf("\n\n");
      puts("All Transaction");
      utility::putLine('=', 126);
      printf("| Sender                         | Receiver                       | Amount     | Hash       | Date                           |\n");
      
      utility::putLine('=', 126);

      for (const auto& transaction : transactions)
        printf("| %-30s | %-30s | %-10llu | %-10s | %-30s |\n", transaction->sender,
          transaction->receiver, transaction->amount, transaction->hash, transaction->time);

      utility::putLine('=', 126);
        
    }

  }

  namespace searchTransactions{

    void display(){

      char keyword[BUFFERSIZE];
      printf("\n\nEnter Username: ");
      scanf("%[^\n]", keyword);
      getchar();

      bool dataAvailable = false;

      for (const auto& transaction : transactions)
        if (strncmp(transaction->sender, keyword, BUFFERSIZE) == 0 ||
            strncmp(transaction->receiver, keyword, BUFFERSIZE) == 0) dataAvailable = true;

      if (!dataAvailable){

        printf("\nNo Data!");
        return;

      }

      printf("\n\n");
      puts("Your Transactions");
      utility::putLine('=', 126);
      printf("| Sender                         | Receiver                       | Amount     | Hash       | Date                           |\n");
      
      utility::putLine('=', 126);

      for (const auto& transaction : transactions)
        if (strncmp(transaction->sender, keyword, BUFFERSIZE) == 0 ||
            strncmp(transaction->receiver, keyword, BUFFERSIZE) == 0)
              printf("| %-30s | %-30s | %-10llu | %-10s | %-30s |\n", transaction->sender,
                transaction->receiver, transaction->amount, transaction->hash, transaction->time);

      utility::putLine('=', 126);
        
    }

  }

  bool displayTransactions(char input[]){

    if (strncmp(input, "1", BUFFERSIZE) == 0) myTransactions::display();
    else if (strncmp(input, "3", BUFFERSIZE) == 0) {
      
      searchTransactions::display();
      strncpy(input, "2", BUFFERSIZE);
    
    } else if (strncmp(input, "4", BUFFERSIZE) == 0) return false;
    else allTransactions::display();
    
    return true;

  }

  void getInput(char storage[]){

    utility::moveCursor(3, 16);

    scanf("%[^\n]", storage);
    getchar();

  }

  void loop(Account* user){

    transactions = database::transaction::getTransactions();
    currentUser = user;

    char input[BUFFERSIZE] = "2";
    while (true){

      utility::clear();
      displayLogo();
      displayOptions();
      if (!displayTransactions(input)) break;

      getInput(input);

    }

  }

}

#endif