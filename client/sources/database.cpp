#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <vector>

#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "../models/Account.h"
#include "../models/Transaction.h"
#include "../models/Block.h"

#include "../headers/utility.h"

namespace database{

  #define BUFFERSIZE 255

  namespace account{

    void create(Account newAccount){

      FILE* file = fopen("../database/accounts.txt", "a");
      // FILE* file = fopen("../../database/accounts.txt", "a");

      fprintf(file, "%s#%s#%llu\n", newAccount.username, newAccount.password, newAccount.fund);
      fclose(file);

    }

    std::vector<Account*> getAccounts(){

      std::vector<Account*> accounts;

      FILE* file = fopen("../database/accounts.txt", "r");
      // FILE* file = fopen("../../database/accounts.txt", "r");

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

      FILE* file = fopen("../database/accounts.txt", "w");
      // FILE* file = fopen("../../database/accounts.txt", "w");

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

      FILE* file = fopen("../database/transactions.txt", "a");
      // FILE* file = fopen("../../database/transactions.txt", "a");

      fprintf(file, "%s#%s#%llu#%s#%s", newTransaction.sender, newTransaction.receiver, newTransaction.amount, newTransaction.hash, newTransaction.time);
      fclose(file);

    }

    std::vector<Transaction*> getTransactions(){

      std::vector<Transaction*> transactions;

      FILE* file = fopen("../database/transactions.txt", "r");
      // FILE* file = fopen("../../database/transactions.txt", "r");

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

  namespace blockchain{

    void create(Block newBlock){

      FILE* file = fopen("../database/blockchain.txt", "a");
      // FILE* file = fopen("../../database/blockchain.txt", "a");

      fprintf(file, "%s\n", newBlock.hash);
      fprintf(file, "%s\n", newBlock.previousHash);
      
      for (short i = 0; i < 8; i++){

        fprintf(file, "%s#%s#%llu#%s#%s\n", newBlock.transactions[i]->sender, newBlock.transactions[i]->receiver, newBlock.transactions[i]->amount, newBlock.transactions[i]->hash, newBlock.transactions[i]->time);

      }

      fprintf(file, "\n");

      fclose(file);

    }

    std::vector<Block*> getBlockchain(){

      FILE* file = fopen("../database/blockchain.txt", "r");

      std::vector<Block*> blockchain;

      Block* buffer;
      char hashBuffer[BUFFERSIZE], previousHashBuffer[BUFFERSIZE];
      while (fscanf(file, "%[^\n]\n%[^\n]\n", hashBuffer, previousHashBuffer) != EOF){

        buffer = (Block*) malloc(sizeof(Block));
        strncpy(buffer->hash, hashBuffer, BUFFERSIZE);
        strncpy(buffer->previousHash, previousHashBuffer, BUFFERSIZE);

        for (short i = 0; i < 8; i++){

          char temp[BUFFERSIZE];
          fscanf(file, "%[^\n]\n", temp);
          buffer->transactions[i] = utility::parseTransaction(temp);
          
        }

        fscanf(file, "\n");

        blockchain.push_back(buffer);

      }
      
      fclose(file);

      return blockchain;

    }

  }

}

#endif