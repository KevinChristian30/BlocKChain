#include <stdio.h>
#include <conio.h>

#ifndef CHANGEPASSWORDSCREEN_CPP
#define CHANGEPASSWORDSCREEN_CPP

#include "../models/Account.h"
#include "../headers/utility.h"
#include "../headers/database.h"
#include "../headers/validator.h"

namespace changePasswordScreen{

  const char LOGO[11 + 1][148 + 1] = {

    "  /$$$$$$  /$$                                                     /$$$$$$$                                                                      /$$",
    " /$$__  $$| $$                                                    | $$__  $$                                                                    | $$",
    "| $$  \\__/| $$$$$$$   /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$       | $$  \\ $$ /$$$$$$   /$$$$$$$ /$$$$$$$ /$$  /$$  /$$  /$$$$$$   /$$$$$$   /$$$$$$$",
    "| $$      | $$__  $$ |____  $$| $$__  $$ /$$__  $$ /$$__  $$      | $$$$$$$/|____  $$ /$$_____//$$_____/| $$ | $$ | $$ /$$__  $$ /$$__  $$ /$$__  $$",
    "| $$      | $$  \\ $$  /$$$$$$$| $$  \\ $$| $$  \\ $$| $$$$$$$$      | $$____/  /$$$$$$$|  $$$$$$|  $$$$$$ | $$ | $$ | $$| $$  \\ $$| $$  \\__/| $$  | $$",
    "| $$    $$| $$  | $$ /$$__  $$| $$  | $$| $$  | $$| $$_____/      | $$      /$$__  $$ \\____  $$\\____  $$| $$ | $$ | $$| $$  | $$| $$      | $$  | $$",
    "|  $$$$$$/| $$  | $$|  $$$$$$$| $$  | $$|  $$$$$$$|  $$$$$$$      | $$     |  $$$$$$$ /$$$$$$$//$$$$$$$/|  $$$$$/$$$$/|  $$$$$$/| $$      |  $$$$$$$",
    " \\______/ |__/  |__/ \\_______/|__/  |__/ \\____  $$ \\_______/      |__/      \\_______/|_______/|_______/  \\_____/\\___/  \\______/ |__/       \\_______/",
    "                                         /$$  \\ $$                                                                                                  ",
    "                                        |  $$$$$$/                                                                                                  ",
    "                                         \\______/                                                                                                   ",

  };

  void displayLogo(){

    utility::setColor("FOREGROUND_BLUE");
    for (short i = 0; i < 11; i++) printf("%s\n", LOGO[i]);
    utility::setColor("FOREGROUND_WHITE");

  }

  void getPassword(char storage[]){

    int currentIndex = 0;
    const short offset = 25;
    
    while (true){
      
      char c = getch();
      
      if (c == 8){
        
        if (currentIndex == 0) {
          utility::moveCursor(offset + currentIndex, 12);
          printf(" ");
          continue;
        }

        storage[currentIndex - 1] = '\0';
        utility::moveCursor(offset + currentIndex - 1, 12);
        printf(" ");
        currentIndex--;
        
      } else if (c == 13) {
        
        storage[currentIndex] = '\0';
        break;
        
      } else {
        
        storage[currentIndex] = c;
        utility::moveCursor(offset + currentIndex, 12);
        printf("*");
        currentIndex++;
        
      } 

    }

  }

  void loop(Account* currentUser){

    utility::clear();
    displayLogo();
    printf("\nEnter your Old Password: ");

    char oldPassword[BUFFERSIZE];
    getPassword(oldPassword);
   
    if (strncmp(currentUser->password, oldPassword, BUFFERSIZE) != 0){

      printf("\nIncorrect Password! Press Enter to Continue");
      getchar();
      return;

    } 
    
    char newPassword1[BUFFERSIZE], newPassword2[BUFFERSIZE];

    while (true){

      utility::clear();
      displayLogo();
      printf("\nEnter your New Password: ");
      getPassword(newPassword1);

      if (!validator::minLength(newPassword1, 10)){

        printf("\nPassword Must be At Least 10 Characters Long, Press Enter to Try Again");
        getchar();
        continue;

      }

      // Validate Password Must be Alpha and Numeric
      if (!validator::isAlpha(newPassword1) || !validator::isNumeric(newPassword1)){

        printf("\nPassword Must Contain Alpha and Numeric Characters, Press Enter to Try Again");
        getchar();
        continue;

      }

      break;

    }
    
    utility::clear();
    displayLogo();
    printf("\nRepeat the New Password: ");
    getPassword(newPassword2);

    if (strncmp(newPassword1, newPassword2, BUFFERSIZE) != 0){

      printf("\nPasswords Doesn't Match! Press Enter to Continue");
      getchar();
      return;

    }

    // Update User
    strncpy(currentUser->password, newPassword1, BUFFERSIZE);
    database::account::update(currentUser);

    puts("");
    utility::setColor("FOREGROUND_GREEN");
    utility::animateString("Password Updated!", 20);
    utility::setColor("FOREGROUND_WHITE");

    getchar();

  }

}

#endif