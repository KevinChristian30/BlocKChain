#include <stdio.h>

#include "../headers/utility.h"
#include "../headers/validator.h" 

#include "../database.cpp"

namespace registerScreen{

  void displayHeader(){
		
		utility::clear();
		puts("Register");
		puts("========");
		
	}

  void getUsername(char storage[]){

    while (true){

      utility::clear();
      displayHeader();

      printf("Enter Username >> ");
      scanf("%[^\n]", storage);
      getchar();

      // Validate Username's Length Must At Least be 8 Characters Long
      if (!validator::minLength(storage, 8)){

        printf("Username Must be At Least 8 Characters Long, Press Enter to Try Again");
        getchar();
        continue;

      }

      // Validate Username Musn't Contain Space
      if (validator::contains(storage, ' ')){

        printf("Username Musn't Contain Space, Press Enter to Try Again");
        getchar();
        continue;

      }

      // Validate Username Must be Unique
      bool isUniqueUsername = true;

      std::vector<Account*> accounts = database::account::getAccounts();
      for (const auto& account : accounts){

        if (strncmp(storage, account->username, BUFFERSIZE) == 0){

          isUniqueUsername = false;
          printf("Username Already Taken, Press Enter to Try Again");
          getchar();
          break;

        }

      }

      if (!isUniqueUsername) continue;

      break;

    }

  }

  void getPassword(char storage[]){

    while (true){

      utility::clear();
      displayHeader();

      printf("Enter Password >> ");
      scanf("%[^\n]", storage);
      getchar();

      // Validate Password's Length Must At Least be 10 Characters Long
      if (!validator::minLength(storage, 10)){

        printf("Password Must be At Least 10 Characters Long, Press Enter to Try Again");
        getchar();
        continue;

      }

      // Validate Password Must be Alpha and Numeric
      if (!validator::isAlpha(storage) || !validator::isNumeric(storage)){

        printf("Password Must Contain Alpha and Numeric Characters, Press Enter to Try Again");
        getchar();
        continue;

      }

      break;

    }

  }

  void loop(){

    Account newAccount;

    getUsername(newAccount.username);
    getPassword(newAccount.password);
    database::account::create(newAccount);

    utility::clear();
    puts("Account Created!, Press Enter to Continue");
    getchar();

  }

}