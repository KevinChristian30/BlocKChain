#include <stdlib.h>
#include <time.h>

#include <stdio.h>

#ifndef TRANSACTION_CPP
#define TRANSACTION_CPP

#include "../headers/globals.h"

struct Transaction{

  char sender[255];
  char receiver[255];
  unsigned long long int amount;
  char time[255];
  char hash[255];

};

void hashTransaction(char storage[], char sender[], char receiver[], unsigned long long int amount, char time[]){

  size_t senderLength = strlen(sender);
  size_t receiverLength = strlen(receiver);
  size_t timeLength = strlen(time);

  int result = 0;
  for (size_t i = 1; i <= senderLength; i++) result += i * sender[i - 1];
  for (size_t i = 1; i <= receiverLength; i++) result += i * receiver[i - 1];
  for (size_t i = 1; i <= timeLength; i++) result += i * time[i - 1];

  itoa(result, storage, 10);

  printf("\nTransaction Created with Hash: %s\n", storage);
  getchar();

}

Transaction* createTransaction(char sender[], char receiver[], unsigned long long int amount){

  Transaction* newTransaction = (Transaction*) malloc(sizeof(Transaction));
  
  strncpy(newTransaction->sender, sender, BUFFERSIZE);
  strncpy(newTransaction->receiver, receiver, BUFFERSIZE);
  newTransaction->amount = amount;

  time_t currentTime = time(NULL);
  strncpy(newTransaction->time, ctime(&currentTime), BUFFERSIZE);

  hashTransaction(newTransaction->hash, 
                  newTransaction->sender, 
                  newTransaction->receiver, 
                  newTransaction->amount, 
                  newTransaction->time);
  
  return newTransaction;

}

#endif