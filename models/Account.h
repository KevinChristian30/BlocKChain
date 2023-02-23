#include "../headers/globals.h"

struct Account{
  char username[255];
  char password[255];
};

Account* createAccount(char username[], char password[]);