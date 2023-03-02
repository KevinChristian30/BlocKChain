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

    const char LOGO[11 + 1][75 + 1] = {

      " /$$$$$$$                      /$$             /$$                         ",  
      "| $$__  $$                    |__/            | $$                        ",  
      "| $$  \\ $$  /$$$$$$   /$$$$$$  /$$  /$$$$$$$ /$$$$$$    /$$$$$$   /$$$$$$ ",
      "| $$$$$$$/ /$$__  $$ /$$__  $$| $$ /$$_____/|_  $$_/   /$$__  $$ /$$__  $$",
      "| $$__  $$| $$$$$$$$| $$  \\ $$| $$|  $$$$$$   | $$    | $$$$$$$$| $$  \\__/",
      "| $$  \\ $$| $$_____/| $$  | $$| $$ \\____  $$  | $$ /$$| $$_____/| $$      ",
      "| $$  | $$|  $$$$$$$|  $$$$$$$| $$ /$$$$$$$/  |  $$$$/|  $$$$$$$| $$      ",
      "|__/  |__/ \\_______/ \\____  $$|__/|_______/    \\___/   \\_______/|__/      ",
      "                     /$$  \\ $$                                            ",
      "                    |  $$$$$$/                                            ",
      "                     \\______/                                             ",

    };

    utility::setColor("FOREGROUND_BLUE");
    for (short i = 0; i < 11; i++) printf("%s\n", LOGO[i]);
    utility::setColor("FOREGROUND_WHITE");

    puts("");
		
	}

  void getUsername(char storage[]){

    while (true){

      utility::clear();
      displayHeader();

      printf("Enter Username >> ");
      scanf("%[^\n]", storage);
      getchar();

      // Validate Username's Length Must At Least be 8 Characters Long
      size_t len = strlen(storage);
      if (!(len >= 8 && len <= 25)){

        utility::setColor("FOREGROUND_RED");
        printf("\nUsername's Length Must be Between 8 and 25 Characters Long! Press Enter to Try Again");
        utility::setColor("FOREGROUND_WHITE");
        
        getchar();
        continue;

      }

      // Validate Username Musn't Contain Space
      if (validator::contains(storage, ' ')){

        utility::setColor("FOREGROUND_RED");
        printf("\nUsername Musn't Contain Space, Press Enter to Try Again");
        utility::setColor("FOREGROUND_WHITE");
        
        getchar();
        continue;

      }

      // Validate Username Must be Unique
      bool isUniqueUsername = true;
      std::vector<Account*> accounts = database::account::getAccounts();
      for (Account* account : accounts){

        if (strncmp(storage, account->username, BUFFERSIZE) == 0){

          isUniqueUsername = false;

          utility::setColor("FOREGROUND_RED");
          printf("\nUsername Already Taken, Press Enter to Try Again");
          utility::setColor("FOREGROUND_WHITE");
          
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
            utility::moveCursor(offset + currentIndex, 12);
            printf(" ");
            continue;
          }

          input[currentIndex - 1] = '\0';
          utility::moveCursor(offset + currentIndex - 1, 12);
          printf(" ");
          currentIndex--;
          
        } else if (c == 13) {
          
          break;
          
        } else {
          
          input[currentIndex] = c;
          utility::moveCursor(offset + currentIndex, 12);
          printf("*");
          currentIndex++;
          
        } 

      }

      puts("");
      strncpy(storage, input, BUFFERSIZE);

      // Validate Password's Length Must At Least be 10 Characters Long
      if (!validator::minLength(storage, 10)){

        utility::setColor("FOREGROUND_RED");
        printf("\nPassword Must be At Least 10 Characters Long, Press Enter to Try Again");
        utility::setColor("FOREGROUND_WHITE");
        
        getchar();
        continue;

      }

      // Validate Password Must be Alpha and Numeric
      if (!validator::isAlpha(storage) || !validator::isNumeric(storage)){

        utility::setColor("FOREGROUND_RED");
        printf("\nPassword Must Contain Alpha and Numeric Characters, Press Enter to Try Again");
        utility::setColor("FOREGROUND_WHITE");
        
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
    newAccount.fund = 0;
    database::account::create(newAccount);

    utility::setColor("FOREGROUND_GREEN");
    utility::animateString("\nAccount Created!, Press Enter to Continue", 20);
    utility::setColor("FOREGROUND_WHITE");
    getchar();

  }

}

#endif