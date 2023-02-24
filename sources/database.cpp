#include <stdio.h>
#include <string.h>

#include <vector>

#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "../models/Account.h"

namespace database{

  #define BUFFERSIZE 255

  namespace account{

    // Create
    void create(Account newAccount){

      FILE* file = fopen("./database/accounts.txt", "a");
      fprintf(file, "%s#%s#%llu\n", newAccount.username, newAccount.password, newAccount.fund);
      fclose(file);

    }

    // Read
    std::vector<Account*> getAccounts(){

      std::vector<Account*> accounts;

      FILE* file = fopen("./database/accounts.txt", "r");

      Account account;
      while (fscanf(file, "%[^#]#%[^#]#%llu\n", account.username, account.password, &account.fund) != EOF)
        accounts.push_back(createAccount(account.username, account.password, account.fund));

      fclose(file);

      return accounts;

    }

    // Update
    void update(Account* toUpdate){

      std::vector<Account*> accounts = getAccounts();
      for (Account* account : accounts){

        if (strncmp(account->username, toUpdate->username, BUFFERSIZE) == 0){

          strncpy(account->password, toUpdate->password, BUFFERSIZE);
          break;

        } 

      }

      FILE* file = fopen("./database/accounts.txt", "w");

      for (const auto& account : accounts)
        fprintf(file, "%s#%s#%llu\n", account->username, account->password, account->fund);

      fclose(file);

    }

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