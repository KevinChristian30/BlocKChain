#include <stdio.h>
#include <iostream>

#ifndef SENDMONEYSCREEN_CPP
#define SENDMONEYSCREEN_CPP

#include "../models/Account.h"
#include "../models/Transaction.h"

#include "../headers/globals.h"
#include "../headers/utility.h"
#include "../headers/database.h"

namespace sendMoneyScreen{

  namespace circularDoublyLinkedList{

    struct Node{

      Account* accounts[11];
      Node* next;
      Node* prev;

    };

    Node* createNode(Account* toInsert[11]){

      Node* newNode = (Node*) malloc(sizeof(Node));
      
      for (int i = 0; i < 10; i++) newNode->accounts[i] = toInsert[i];

      newNode->next = newNode->prev = NULL;
      return newNode;

    }

    Node* HEAD = NULL;

    void insert(Account* toInsert[11]){

      Node* newNode = createNode(toInsert);

      if (HEAD == NULL){

        newNode->next = newNode;
        newNode->prev = newNode;
        HEAD = newNode;

      } else {

        HEAD->prev->next = newNode;
        newNode->next = HEAD;
        newNode->prev = HEAD->prev;
        HEAD->prev = newNode;

      }

    }

    void display(int pageNumber, Node* current){

      pageNumber *= 10;

      utility::putLine('=', 41);
      printf("| Num  | Username                       |\n");
      utility::putLine('=', 41);

      for (int i = 0; i < 10; i++)
        if (current->accounts[i]) 
          printf("| %3d. | %-30s |\n", pageNumber + i + 1, 
            current->accounts[i]->username);
      
      utility::putLine('=', 41);

    }

    int createPagination(){

      std::vector<Account*> accounts = database::account::getAccounts();
      
      int i = 0;
      Account* partition[11];
      for (int i = 0; i < 10; i++) partition[i] = NULL;
      for (Account* account : accounts){
        
        if (i >= 10) {

          circularDoublyLinkedList::insert(partition);
          for (int j = 0; j < 10; j++) partition[j] = NULL;
          i = 0;

        } 

        partition[i++] = account;

      }

      circularDoublyLinkedList::insert(partition);

      return accounts.size() / 10;

    }

  }

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

  void displayHeader(){

    displayLogo();
    puts("");

  }

  namespace receiver{

    void display(int pageNumber, circularDoublyLinkedList::Node* current){

      utility::clear();
      displayHeader();
      circularDoublyLinkedList::display(pageNumber, current);

      puts("1. Prev");
      puts("2. Next");
      puts("3. Enter Username");
      puts("4. Back");
      printf(">> ");

    }

    void getInput(char storage[]){

      scanf("%[^\n]", storage);
      getchar();

    }

  }

  bool getReceiver(char storage[]){

    int maxPage = circularDoublyLinkedList::createPagination();

    circularDoublyLinkedList::Node* current = circularDoublyLinkedList::HEAD;

    int pageNumber = 0;
    char input[BUFFERSIZE];
    while (true){

      receiver::display(pageNumber, current);
      receiver::getInput(input);

      if (strncmp(input, "1", BUFFERSIZE) == 0) {
      
        current = current->prev;
        pageNumber--;
        if (pageNumber < 0) pageNumber = maxPage;

      } else if (strncmp(input, "2", BUFFERSIZE) == 0){

        current = current->next;
        pageNumber++;
        if (pageNumber > maxPage) pageNumber = 0;
        
      } else if (strncmp(input, "3", BUFFERSIZE) == 0){

        utility::clear();
        displayHeader();
        circularDoublyLinkedList::display(pageNumber, current);
        
        printf("\nEnter Username: ");
        
        // Scan For Username
        scanf("%[^\n]", storage);
        getchar();

        // Validate Must Exist
        Account* receiverAccount = database::account::findByUsername(storage);
        if (!receiverAccount) {
          
          puts("");
          utility::setColor("FOREGROUND_RED");
          printf("Username Not Found! Press Enter to Try Again");
          utility::setColor("FOREGROUND_WHITE");
          
          getchar();
          continue;
        
        }

        return true;

      } else if (strncmp(input, "4", BUFFERSIZE) == 0){

        return false;

      }

    }

  }

  void getAmount(unsigned long long int *storage, Account* currentUser){

    utility::clear();
    displayHeader();
    printf("Your Blue Tokens: %llu", currentUser->fund);
    printf("\nEnter Amount to Send: ");
    scanf("%llu", storage);
    getchar();

  }

  void loop(Account* currentUser){

    char input[BUFFERSIZE];
    Transaction newTransaction;
    strncpy(newTransaction.sender, currentUser->username, BUFFERSIZE);

    while (true){

      utility::clear();
      displayHeader();

      // Get Receiver
      if (!getReceiver(newTransaction.receiver)) break;

      // Get Amount
      while (true){

        getAmount(&newTransaction.amount, currentUser);
        if (newTransaction.amount <= 0){

          utility::setColor("FOREGROUND_RED");
          printf("\nAmount Must be Positive! Press Enter to Continue");
          utility::setColor("FOREGROUND_WHITE");

          getchar();

        } else if (newTransaction.amount > currentUser->fund){

          utility::setColor("FOREGROUND_RED");
          printf("\nYou don't Have Enough Money! Press Enter to Continue");
          utility::setColor("FOREGROUND_WHITE");
          
          getchar();

        } else break;

      }

      currentUser->fund -= newTransaction.amount;
      database::account::update(currentUser);

      // Create and Save Transaction to Transactions List
      Transaction* toCreate = createTransaction(newTransaction.sender, newTransaction.receiver, newTransaction.amount);
      
      database::transaction::create(*toCreate);
      
      utility::setColor("FOREGROUND_GREEN");
      utility::animateString("\nTransaction Inserted Succesfully", 20);
      utility::setColor("FOREGROUND_WHITE");
      getchar();

    }

  }

}

#endif