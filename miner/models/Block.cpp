#include <stdlib.h>
#include <time.h>

#ifndef BLOCK_CPP
#define BLOCK_CPP

#include "../headers/globals.h"
#include "../models/Transaction.h"

#define BUFFERSIZE 255

struct Block{

  Transaction* transactions[9];
  char hash[BUFFERSIZE];
  char previousHash[BUFFERSIZE];

};

long long int djb2(char string[]){

  long long hash = 5381;
  long long int c;

  while (c = *string++) hash = (hash * 33) + c;

  return hash;

}

long long int mergeHash(Transaction* transactions[], long long int leftHash, long long int rightHash){

  return leftHash ^ rightHash;

}

long long int getBlockHash(Transaction* transactions[], short left = 0, short right = 7){

  if (left < right){

    short middle = (left + right) / 2;
    long long int leftHash = getBlockHash(transactions, left, middle);
    long long int rightHash = getBlockHash(transactions, middle + 1, right);
    return mergeHash(transactions, leftHash, rightHash);

  }

  return djb2(transactions[left]->hash);

}

Block* createBlock(Transaction* transactions[9], char previousHash[]){

  Block* newBlock = (Block*) malloc(sizeof(Block));
  
  for (short i = 0; i < 8; i++) newBlock->transactions[i] = transactions[i];
  strncpy(newBlock->previousHash, previousHash, BUFFERSIZE);

  // Get Block Hash
  char hash[BUFFERSIZE];
  itoa(getBlockHash(transactions) % 100, hash, 10);
  strncpy(newBlock->hash, hash, BUFFERSIZE);

  return newBlock;

}

#endif