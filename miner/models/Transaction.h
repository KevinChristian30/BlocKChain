#ifndef TRANSACTION_H
#define TRANSACTION_H

struct Transaction{

  char sender[255];
  char receiver[255];
  unsigned long long int amount;
  char time[255];
  char hash[255];

};

void hashTransaction(char storage[], char sender[], char receiver[], unsigned long long int amount, char time[]);

Transaction* createTransaction(char sender[], char receiver[], unsigned long long int amount);

#endif