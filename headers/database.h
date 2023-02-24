#include <vector>

#ifndef DATABASE_H
#define DATABASE_H

#include "../models/Account.h"

namespace database{

  namespace account{

    void create(Account newAccount);

    std::vector<Account*> getAccounts();

    Account* findByUsername(const char* username);

    void update(Account* account);

  }

}

#endif