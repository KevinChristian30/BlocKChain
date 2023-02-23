#include <string.h>
#include <malloc.h>

struct Account{

  char username[255];
  char password[255];

};

Account* createAccount(char username[], char password[]){

  Account* newAccount = (Account*) malloc(sizeof(Account));
  strncpy(newAccount->username, username, 255);
  strncpy(newAccount->password, password, 255);
  return newAccount;

}
