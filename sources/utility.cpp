#include <stdio.h>
#include <windows.h>
#include <iostream>

#include <vector>

#ifndef UTILITY_CPP
#define UTILITY_CPP

namespace utility{

  #define BUFFERSIZE 255
  const HANDLE OUTPUTHANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

  #define FOREGROUND_WHITE 0x07
  #define FOREGROUND_LIGHTBLUE 0x09
	
	void clear(){
		
		system("cls");
		
	}

  void moveCursor(short x, short y){
	
    COORD coordinate = {x, y};
    SetConsoleCursorPosition(OUTPUTHANDLE, coordinate);
    
  }
	
  void animateString(const char* toAnimate, unsigned long long int delay){

    size_t length = strlen(toAnimate);
    for (size_t i = 0; i < length; i++){
      
      printf("%c", toAnimate[i]);
      Sleep(delay);

    }

  }

  void setColor(const char* color){

    if (strcmp(color, "FOREGROUND_RED") == 0) 
      SetConsoleTextAttribute(OUTPUTHANDLE, FOREGROUND_RED);
    else if (strcmp(color, "FOREGROUND_GREEN") == 0)
      SetConsoleTextAttribute(OUTPUTHANDLE, FOREGROUND_GREEN);
    else if (strcmp(color, "FOREGROUND_BLUE") == 0)
      SetConsoleTextAttribute(OUTPUTHANDLE, FOREGROUND_LIGHTBLUE);
    else if (strcmp(color, "FOREGROUND_WHITE") == 0)
      SetConsoleTextAttribute(OUTPUTHANDLE, FOREGROUND_WHITE);

  }

}

#endif