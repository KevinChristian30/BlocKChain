#include <stdio.h>
#include <iostream>
#include <vector>
#include <conio.h> 

#ifndef MININGSCREEN_CPP
#define MININGSCREEN_CPP

#include "../models/Account.h"
#include "../models/Transaction.h"
#include "../models/Block.h"

#include "../headers/utility.h"
#include "../headers/database.h"

namespace miningScreen{

  Account* currentUser;

  void displayLogo(){

    const char LOGO[6 + 1][44 + 1] = {

      "   _____   .__         .__            ____  ", 
      "  /     \\  |__|  ____  |__|  ____    / ___\\ ", 
      " /  \\ /  \\ |  | /    \\ |  | /    \\  / /_/  >", 
      "/    Y    \\|  ||   |  \\|  ||   |  \\ \\___  / ", 
      "\\____|__  /|__||___|  /|__||___|  //_____/  ", 
      "        \\/          \\/          \\/          ", 

    };

    utility::setColor("FOREGROUND_BLUE");
    for (short i = 0; i < 6; i++) printf("%s\n", LOGO[i]);
    utility::setColor("FOREGROUND_WHITE");

  }

  bool mine(){

    puts("Fetching Transactions");
    Sleep(1000);

    std::vector<Transaction*> transactions = database::transaction::getTransactions();
    std::vector<Block*> blockchain = database::blockchain::getBlockchain();
  
    if (transactions.size() < 8) {
      
      utility::setColor("FOREGROUND_RED");
      printf("Not Enough Transactions to Mine!");
      utility::setColor("FOREGROUND_WHITE");

      return false;
    
    }

    Transaction* toMine[9];
    for (short i = 0; i < 8; i++) {
    
      toMine[i] = transactions.at(i);
      database::transaction::deleteTransaction(*(transactions.at(i)));
    
    }

    utility::setColor("FOREGROUND_BLUE");
    puts("Creating Block");
    utility::setColor("FOREGROUND_WHITE");
    Sleep(2000);

    Block* newBlock;
    if (blockchain.size() == 0) newBlock = createBlock(toMine, (char*) "100");
    else newBlock = createBlock(toMine, blockchain.at(blockchain.size() - 1)->hash);

    unsigned long long int totalProcessed = 0;
    for (int i = 0; i < 8; i++){

      Account* toUpdate = database::account::findByUsername(newBlock->transactions[i]->receiver);

      if (toUpdate){

        totalProcessed += newBlock->transactions[i]->amount;
        toUpdate->fund += newBlock->transactions[i]->amount;
        database::account::update(toUpdate);
        printf("Transaction %s Stored\n", newBlock->transactions[i]->hash);
        Sleep(500);

      }

    }

    utility::setColor("FOREGROUND_BLUE");
    printf("Block Created with Hash: %s\n", newBlock->hash);
    utility::setColor("FOREGROUND_WHITE");
    Sleep(1000);

    // Insert to Database
    puts("Storing Block to the BlocKChain");
    database::blockchain::create(*newBlock);
    Sleep(2000);

    utility::setColor("FOREGROUND_GREEN");
    printf("Block Stored in the BlocKChain\n");
    utility::setColor("FOREGROUND_WHITE");
    Sleep(1000);

    unsigned long long int reward = totalProcessed * 0.1;
    currentUser = database::account::findByUsername(currentUser->username);
    currentUser->fund += reward;
    database::account::update(currentUser);

    utility::setColor("FOREGROUND_BLUE");
    printf("You are Rewarded %llu BlueTokens\n", reward);
    utility::setColor("FOREGROUND_WHITE");
    Sleep(1000);
    
    puts("");

    return true;

  }

  void loop(Account* user){

    currentUser = user;

    utility::clear();
    displayLogo();
    puts("Press Enter to Start Mining");
    getchar();

    utility::clear();
    displayLogo();
    printf("Mining Log:\n\n");

    while (true){
      
      char input[BUFFERSIZE];

      if (!mine()) break;
      printf("\nContinue Mining [n to stop]: ");
      scanf("%[^\n]", input);
      getchar();

      if (strncmp(input, "n", BUFFERSIZE) == 0) break;

    }

    fflush(stdin);

    utility::animateString("\n\nMining Session Finished! Press Enter to Continue", 20);
    getchar();

  }

}

#endif