#include <string.h>
#include <malloc.h>

#include "../sources/globals.cpp"

struct Account{

  char username[BUFFERSIZE];
  char password[BUFFERSIZE];

};

Account* createAccount(char username[], char password[]){

  Account* newAccount = (Account*) malloc(sizeof(Account));
  strncpy(newAccount->username, username, BUFFERSIZE);
  strncpy(newAccount->password, password, BUFFERSIZE);
  return newAccount;

}
