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

  void getReceiver(char storage[]){

    // Display List of Users Paginated for 10 Items Each Page with Circular Doubly Linked List
    std::vector<Account*> accounts = database::account::getAccounts();
    int maxPage = accounts.size() / 10;
    
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

    circularDoublyLinkedList::Node* current = circularDoublyLinkedList::HEAD;
    int pageNumber = 0;
    char input[BUFFERSIZE];

    while (true){

      utility::clear();
      circularDoublyLinkedList::display(pageNumber, current);
      puts("1. Next");
      puts("2. Prev");
      printf(">> ");
      scanf("%[^\n]", input);
      getchar();

      if (strncmp(input, "1", BUFFERSIZE) == 0) {
      
        current = current->next;
        pageNumber++;
        if (pageNumber > maxPage) pageNumber = 0;

      
      } else if (strncmp(input, "2", BUFFERSIZE) == 0){
      
        current = current->prev;
        pageNumber--;
        if (pageNumber < 0) pageNumber = maxPage;
        
      
      }

    }

  }

  void loop(Account* currentUser){

    char input[BUFFERSIZE];
    Transaction newTransaction;
    strncpy(newTransaction.sender, currentUser->username, BUFFERSIZE);

    while (true){

      utility::clear();
      displayHeader();

      getReceiver(newTransaction.receiver);

      puts("IN");
      getchar();

      // Get Destination
      // Get Amount
      // Create and Save Transaction to Transactions List

    }

  }

}

#endif