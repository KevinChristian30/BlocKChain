#include <stdio.h>
#include <string.h>

#include <vector>

#include "../headers/utility.h"
#include "../models/Account.h"

#ifndef DATABASE_H
#define DATABASE_H

namespace database{

  #define BUFFERSIZE 255

  namespace account{

    // Create
    void create(Account newAccount){

      FILE* file = fopen("./database/accounts.txt", "a");
      fprintf(file, "%s#%s\n", newAccount.username, newAccount.password);
      fclose(file);

    }

    // Read
    std::vector<Account*> getAccounts(){

      std::vector<Account*> accounts;

      FILE* file = fopen("./database/accounts.txt", "r");

      Account account;
      while (fscanf(file, "%[^#]#%[^\n]\n", account.username, account.password) != EOF)
        accounts.push_back(createAccount(account.username, account.password));

      fclose(file);

      return accounts;

    }

    // Update
    // Delete

    // Find
    Account* findByUsername(const char* username){

      std::vector<Account*> accounts = getAccounts();

      for (const auto& account : accounts){

        if (strncmp(account->username, username, BUFFERSIZE) == 0) return account; 

      }

      return NULL;

    }

  }

}

#endif