#include <stdio.h>
#include <conio.h>

#include <vector>

#include "../headers/utility.h"
#include "../headers/database.h"
#include "../headers/mainMenu.h"

namespace loginScreen{

  #define BUFFERSIZE 255

  void displayHeader(){
		
		puts("Log In");
		puts("======");
		
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
          utility::moveCursor(offset + currentIndex, 2);
          printf(" ");
          continue;
        }

        storage[currentIndex] = '\0';
        utility::moveCursor(offset + currentIndex, 2);
        printf(" ");
        currentIndex--;
        
      } else if (c == 13) {
        
        storage[currentIndex] = '\0';
        break;
        
      } else {
        
        storage[currentIndex] = c;
        utility::moveCursor(offset + currentIndex, 2);
        printf("*");
        currentIndex++;
        
      } 

    }

  }

  void loop(){

    Account attempt;
    getUsername(attempt.username);
    getPassword(attempt.password);

    Account* user = database::account::findByUsername(attempt.username);
    if (!user) {

      utility::clear();
      displayHeader();
      printf("Username Not Found! Press Enter to Continue");
      getchar();
      return;

    }

    if (strncmp(attempt.password, user->password, BUFFERSIZE) != 0){
      
      utility::clear();
      displayHeader();
      printf("Incorrect Password! Press Enter to Continue");
      getchar();
      return;

    }

    mainMenu::loop(user);

  }

}