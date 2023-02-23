#include <stdio.h>
#include <windows.h>
#include <iostream>

#include <vector>

namespace utility{

  #define BUFFERSIZE 255
  const HANDLE OUTPUTHANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
	
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

}
