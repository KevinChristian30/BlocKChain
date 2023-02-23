#include <stdio.h>
#include <conio.h>
#include <vector>

#ifndef REGISTERSCREEN_CPP
#define REGISTERSCREEN_CPP

#include "../headers/utility.h"
#include "../headers/validator.h"
#include "../headers/database.h"

namespace registerScreen{

  #define BUFFERSIZE 255

  void displayHeader(){
		
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
      for (Account* account : accounts){

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

    const short offset = 18;
    while (true){

      utility::clear();
      displayHeader();
      printf("Enter Password >> ");

      char input[BUFFERSIZE] = "";
      int currentIndex = 0;
      
      while (true){
        
        char c = getch();
        
        if (c == 8){
          
          if (currentIndex == 0) {
            utility::moveCursor(offset + currentIndex, 2);
            printf(" ");
            continue;
          }

          input[currentIndex] = '\0';
          utility::moveCursor(offset + currentIndex, 2);
          printf(" ");
          currentIndex--;
          
        } else if (c == 13) {
          
          break;
          
        } else {
          
          input[currentIndex] = c;
          utility::moveCursor(offset + currentIndex, 2);
          printf("*");
          currentIndex++;
          
        } 

      }

      puts("");
      strncpy(storage, input, BUFFERSIZE);

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

#endif