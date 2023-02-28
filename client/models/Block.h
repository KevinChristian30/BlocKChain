#include <stdlib.h>
#include <time.h>

#ifndef BLOCK_H
#define BLOCK_H

#include "../models/Transaction.h"
#include "../headers/globals.h"

#define BUFFERSIZE 255

struct Block{

  Transaction* transactions[9];
  char hash[BUFFERSIZE];
  char previousHash[BUFFERSIZE];

};

Block* createBlock(Transaction* transactions[9], char previousHash[]);

unsigned long long int getAmount(Block* block);

#endif