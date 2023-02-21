#include <stdio.h>

#include <vector>

#include "./models/Account.cpp"

namespace database{

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
      while (fscanf(file, "%[^#]#[^\n]\n", account.username, account.password) != EOF)
        accounts.push_back(createAccount(account.username, account.password));

      fclose(file);

      return accounts;

    }

    // Update
    // Delete
    // Find

  }

}