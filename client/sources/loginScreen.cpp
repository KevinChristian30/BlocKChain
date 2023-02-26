#include <stdio.h>
#include <conio.h>


#include <unistd.h>

#include <vector>

#ifndef LOGINSCREEN_CPP
#define LOGINSCREEN_CPP

#include "../headers/utility.h"
#include "../headers/database.h"
#include "../headers/mainMenuScreen.h"

namespace loginScreen{

  #define BUFFERSIZE 255

  void displayHeader(){
		
    const char LOGO[11 + 1][54 + 1] = {

      " /$$                                 /$$$$$$          ",
      "| $$                                |_  $$_/          ",
      "| $$        /$$$$$$   /$$$$$$         | $$   /$$$$$$$ ",
      "| $$       /$$__  $$ /$$__  $$        | $$  | $$__  $$",
      "| $$      | $$  \\ $$| $$  \\ $$        | $$  | $$  \\ $$",
      "| $$      | $$  | $$| $$  | $$        | $$  | $$  | $$",
      "| $$$$$$$$|  $$$$$$/|  $$$$$$$       /$$$$$$| $$  | $$",
      "|________/ \\______/  \\____  $$      |______/|__/  |__/",
      "                     /$$  \\ $$                        ",
      "                    |  $$$$$$/                        ",
      "                     \\______/                         ",
          
    };

    utility::setColor("FOREGROUND_BLUE");
    for (short i = 0; i < 11; i++) printf("%s\n", LOGO[i]);
    utility::setColor("FOREGROUND_WHITE");

    puts("");
    
	}

  void getUsername(char storage[]){

    utility::clear();
    displayHeader();
    printf("Enter Username >> ");
    scanf("%[^\n]", storage);
    getchar();

  } 
  
  void getPassword(char storage[]){

    utility::clear();
    displayHeader();
    printf("Enter Password >> ");

    int currentIndex = 0;
    const short offset = 18;
    
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

  void loop(){

    Account attempt;
    getUsername(attempt.username);
    getPassword(attempt.password);

    std::vector<Account*> accounts = database::account::getAccounts();
    for (const auto& account : accounts) printf("\n%s", account->username);

    puts("DONE");
    getchar();

    Account* user = database::account::findByUsername(attempt.username);

    if (!user) {

      utility::clear();
      displayHeader();

      utility::setColor("FOREGROUND_RED");
      printf("Username Not Found! Press Enter to Continue");
      utility::setColor("FOREGROUND_WHITE");

      getchar();
      return;

    }

    if (strncmp(attempt.password, user->password, BUFFERSIZE) != 0){
      
      utility::clear();
      displayHeader();

      utility::setColor("FOREGROUND_RED");
      printf("Incorrect Password! Press Enter to Continue");
      utility::setColor("FOREGROUND_WHITE");

      getchar();
      return;

    }

    mainMenuScreen::loop(user);

  }

}

#endif