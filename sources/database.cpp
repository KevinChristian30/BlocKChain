#include <stdio.h>
#include <string.h>

#include <vector>

#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "../models/Account.h"
#include "../models/Transaction.h"

namespace database{

  #define BUFFERSIZE 255

  namespace account{

    void create(Account newAccount){

      FILE* file = fopen("./database/accounts.txt", "a");
      fprintf(file, "%s#%s#%llu\n", newAccount.username, newAccount.password, newAccount.fund);
      fclose(file);

    }

    std::vector<Account*> getAccounts(){

      std::vector<Account*> accounts;

      FILE* file = fopen("./database/accounts.txt", "r");

      Account account;
      while (fscanf(file, "%[^#]#%[^#]#%llu\n", account.username, account.password, &account.fund) != EOF)
        accounts.push_back(createAccount(account.username, account.password, account.fund));

      fclose(file);

      return accounts;

    }

    void update(Account* toUpdate){

      std::vector<Account*> accounts = getAccounts();
      for (Account* account : accounts){

        if (strncmp(account->username, toUpdate->username, BUFFERSIZE) == 0){

          strncpy(account->password, toUpdate->password, BUFFERSIZE);
          account->fund = toUpdate->fund;
          break;

        } 

      }

      FILE* file = fopen("./database/accounts.txt", "w");

      for (const auto& account : accounts)
        fprintf(file, "%s#%s#%llu\n", account->username, account->password, account->fund);

      fclose(file);

    }

    Account* findByUsername(const char* username){

      std::vector<Account*> accounts = getAccounts();

      for (const auto& account : accounts){

        if (strncmp(account->username, username, BUFFERSIZE) == 0) return account; 

      }

      return NULL;

    }

  }

  namespace transaction{

    void create(Transaction newTransaction){

      FILE* file = fopen("./database/transactions.txt", "a");
      fprintf(file, "%s#%s#%llu#%s#%s", newTransaction.sender, newTransaction.receiver, newTransaction.amount, newTransaction.hash, newTransaction.time);
      fclose(file);

    }

    std::vector<Transaction*> getTransactions(){

      std::vector<Transaction*> transactions;

      FILE* file = fopen("./database/transactions.txt", "r");

      Transaction transaction;
      while (fscanf(file, "%[^#]#%[^#]#%llu#%[^#]#%[^\n]\n", transaction.sender, transaction.receiver,
       &transaction.amount, transaction.hash, transaction.time) != EOF){
        
        Transaction* newTransaction = createTransaction(transaction.sender, transaction.receiver, transaction.amount);
        strncpy(newTransaction->time, transaction.time, BUFFERSIZE);

        transactions.push_back(newTransaction);

       }
        

      fclose(file);

      return transactions;

    }

  }

}

#endif