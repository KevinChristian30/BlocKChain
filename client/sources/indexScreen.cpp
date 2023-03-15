#include <stdio.h>
#include <string.h>

#ifndef INDEXSCREEN_CPP
#define INDEXSCREEN_CPP

#include "../headers/utility.h"
#include "../headers/loginScreen.h"
#include "../headers/registerScreen.h"
#include "../headers/exitScreen.h"

namespace indexScreen{

  #define BUFFERSIZE 255

  const char LOGO[8 + 1][88 + 1] = {

		" /$$$$$$$  /$$                     /$$   /$$  /$$$$$$  /$$                 /$$          ",
		"| $$__  $$| $$                    | $$  /$$/ /$$__  $$| $$                |__/          ",
		"| $$  \\ $$| $$  /$$$$$$   /$$$$$$$| $$ /$$/ | $$  \\__/| $$$$$$$   /$$$$$$  /$$ /$$$$$$$ ",
		"| $$$$$$$ | $$ /$$__  $$ /$$_____/| $$$$$/  | $$      | $$__  $$ |____  $$| $$| $$__  $$",
		"| $$__  $$| $$| $$  \\ $$| $$      | $$  $$  | $$      | $$  \\ $$  /$$$$$$$| $$| $$  \\ $$",
		"| $$  \\ $$| $$| $$  | $$| $$      | $$\\  $$ | $$    $$| $$  | $$ /$$__  $$| $$| $$  | $$",
		"| $$$$$$$/| $$|  $$$$$$/|  $$$$$$$| $$ \\  $$|  $$$$$$/| $$  | $$|  $$$$$$$| $$| $$  | $$",
		"|_______/ |__/ \\______/  \\_______/|__/  \\__/ \\______/ |__/  |__/ \\_______/|__/|__/  |__/",
	
	};

  void displayLogo(){
		
    utility::setColor("FOREGROUND_GREEN");
		for (int i = 0; i < 8; i++) printf("%s\n", LOGO[i]);
    utility::setColor("FOREGROUND_WHITE");
		
	}
	
	void displayOptions(){
		
		puts("1. Log In");
		puts("2. Register");
		puts("3. Exit");
		printf(">> ");
		
	}

  void display(){

    displayLogo();
    displayOptions();

  }

  void getInput(char storage[]){

    scanf("%s", storage);
    getchar();

  }

  void route(char input[]){

    if (strncmp(input, "1", BUFFERSIZE) == 0){ // Login Screen

      loginScreen::loop();

    } else if (strncmp(input, "2", BUFFERSIZE) == 0){ // Register Screen

      registerScreen::loop();

    } else if (strncmp(input, "3", BUFFERSIZE) == 0){ // ExitScreen

      exitScreen::loop();

    }

  }

  void loop(){

    while (true){

      char input[BUFFERSIZE];
		  while (true){
			
        utility::clear();
        display();
        getInput(input);
        route(input);
        
      }

    }

    while (true) getchar();
 
  }

}

#endif