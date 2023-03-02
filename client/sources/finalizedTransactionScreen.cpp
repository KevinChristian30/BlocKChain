#include <stdio.h>
#include <vector>

#ifndef FINALIZEDTRANSACTIONSCREEN_CPP
#define FINALIZEDTRANSACTIONSCREEN_CPP

#include "../models/Account.h"
#include "../models/Block.h"

#include "../headers/utility.h"
#include "../headers/database.h"

namespace finalizedTransactionScreen{

  Account* currentUser;

  namespace hashTable{

    struct Node{

      Block* block;
      Node* left;
      Node* right;

    };

    Node* createNode(Block* toCreate){

      Node* newNode = (Node*) malloc(sizeof(Node));
      
      newNode->block = toCreate;
      newNode->left = newNode->right = NULL;

      return newNode;

    }

    Node* table[100];

    void initiateTable(){

      for (int i = 0; i < 100; i++) table[i] = NULL;

    }

    void insert(Node** root, Block* toInsert){

      unsigned long long int total = 0;
      for (int i = 0; i < 8; i++) total += toInsert->transactions[i]->amount;

      Node* newNode = createNode(toInsert);
      if (!(*root)) *root = newNode;
      else if (getAmount(toInsert) < getAmount((*root)->block)) {

        insert(&((*root)->left) , toInsert);
      
      } else {

        insert(&((*root)->right) , toInsert);

      }
    }

    void displayInOrder(Node* node){

      if (node->left) displayInOrder(node->left);

      utility::setColor("FOREGROUND_BLUE");
      printf("Hash: %s\n", node->block->hash);
      utility::setColor("FOREGROUND_GREEN");
      printf("Total Transaction Amount: %llu\n", getAmount(node->block));
      utility::setColor("FOREGROUND_WHITE");

      utility::putLine('=', 111);
      puts("| Sender                    | Receiver                  | Amount     | Hash       | Time                      |");
      utility::putLine('=', 111);
      for (int i = 0; i < 8; i++){

        printf("| %-25s | %-25s | %-10llu | %-10s | %-25s |\n", node->block->transactions[i]->sender, 
        node->block->transactions[i]->receiver, 
        node->block->transactions[i]->amount, 
        node->block->transactions[i]->hash,
        node->block->transactions[i]->time);

      }
      utility::putLine('=', 111);
      puts("");

      if (node->right) displayInOrder(node->right);

    }

    int displayBlock(int toDisplay){

      Node* node = table[toDisplay];

      if (!node){

        puts("No Data");
        return -1;

      }

      displayInOrder(node);

      puts("Press Enter to Continue");

      return atoi(node->block->previousHash);

    }

  }

  void displayLogo(){

    const char LOGO[8 + 1][72 + 1] = {

      " /$$$$$$$$ /$$                     /$$ /$$                           /$$",
      "| $$_____/|__/                    | $$|__/                          | $$",
      "| $$       /$$ /$$$$$$$   /$$$$$$ | $$ /$$ /$$$$$$$$  /$$$$$$   /$$$$$$$",
      "| $$$$$   | $$| $$__  $$ |____  $$| $$| $$|____ /$$/ /$$__  $$ /$$__  $$",
      "| $$__/   | $$| $$  \\ $$  /$$$$$$$| $$| $$   /$$$$/ | $$$$$$$$| $$  | $$",
      "| $$      | $$| $$  | $$ /$$__  $$| $$| $$  /$$__/  | $$_____/| $$  | $$",
      "| $$      | $$| $$  | $$|  $$$$$$$| $$| $$ /$$$$$$$$|  $$$$$$$|  $$$$$$$",
      "|__/      |__/|__/  |__/ \\_______/|__/|__/|________/ \\_______/ \\_______/",

    };

    utility::setColor("FOREGROUND_BLUE");
    for (short i = 0; i < 8; i++) printf("%s\n", LOGO[i]);
    utility::setColor("FOREGROUND_WHITE");
    

  }

  int display(int toDisplay){

    displayLogo();
    printf("\n\n");
    return hashTable::displayBlock(toDisplay);

  }

  void loop(Account* user){

    currentUser = user;
    hashTable::initiateTable();
    std::vector<Block*> blockchain = database::blockchain::getBlockchain();

    for (Block* block : blockchain) hashTable::insert(&hashTable::table[atoi(block->hash)], block);

    int currentIndex = atoi(blockchain.at(blockchain.size() - 1)->hash);

    while (true){

      utility::clear();
      int nextIndex = display(currentIndex);
      currentIndex = nextIndex;

      if (currentIndex == 100){

        utility::setColor("FOREGROUND_GREEN");
        printf("\n\nEnd of Blockchain!");
        utility::setColor("FOREGROUND_WHITE");
        
        getchar();
        break;

      }

      getchar();
      
    }

  }  

}

#endif