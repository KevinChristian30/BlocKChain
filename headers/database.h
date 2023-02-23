#include <vector>
#include "../models/Account.h"

namespace database{

  namespace account{

    void create(Account newAccount);

    std::vector<Account*> getAccounts();

    Account* findByUsername(const char* username);

  }

}
