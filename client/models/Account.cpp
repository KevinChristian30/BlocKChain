#include <string.h>
#include <malloc.h>

#ifndef ACCOUNT_CPP
#define ACCOUNT_CPP

struct Account{

  char username[255];
  char password[255];
  unsigned long long int fund;

};

Account* createAccount(char username[], char password[], unsigned long long int fund){

  Account* newAccount = (Account*) malloc(sizeof(Account));
  strncpy(newAccount->username, username, 255);
  strncpy(newAccount->password, password, 255);
  newAccount->fund = fund;
  return newAccount;

}

#endif