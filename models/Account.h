#include "../headers/globals.h"

#ifndef ACCOUNT_H
#define ACCOUNT_H

struct Account{
  char username[255];
  char password[255];
};

Account* createAccount(char username[], char password[]);

#endif
