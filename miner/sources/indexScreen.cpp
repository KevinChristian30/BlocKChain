#include <stdio.h>

#ifndef INDEXSCREEN_CPP
#define INDEXSCREEN_CPP

#include "../headers/utility.h"
#include "../headers/globals.h"
#include "../headers/loginScreen.h"
#include "../headers/exitScreen.h"

namespace indexScreen{

  #define BUFFERSIZE 255

  void displayLogo(){
    
    const char LOGO[6 + 1][74 + 1] = {

      "__________ .__                         _____   .__                        ", 
      "\\______   \\|  |   __ __   ____        /     \\  |__|  ____    ____ _______ ", 
      " |    |  _/|  |  |  |  \\_/ __ \\      /  \\ /  \\ |  | /    \\ _/ __ \\_  __ \\", 
      " |    |   \\|  |__|  |  /\\  ___/     /    Y    \\|  ||   |  \\  ___/ |  | \\/", 
      " |______  /|____/|____/  \\___  >    \\____|__  /|__||___|  / \\___  >|__|   ", 
      "        \\/                   \\/             \\/          \\/      \\/        ", 
    
    };

    utility::setColor("FOREGROUND_BLUE");
    for (short i = 0; i < 6; i++) printf("%s\n", LOGO[i]);
    utility::setColor("FOREGROUND_WHITE");

  }

  void display(){
    
    displayLogo();
    puts("1. Log In");
    puts("2. Exit");
    printf(">> ");

  }

  void getInput(char storage[]){

    scanf("%[^\n]", storage);
    getchar();

  }

  void route(char input[]){

    if (strncmp(input, "1", BUFFERSIZE) == 0) loginScreen::loop();
    else if (strncmp(input, "2", BUFFERSIZE) == 0) exitScreen::loop();

  }

  void loop(){

    char input[BUFFERSIZE];
    while (true){

      utility::clear();
      display();
      getInput(input);
      route(input);
      
    }

  }

}

#endif