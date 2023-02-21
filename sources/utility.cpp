#include <windows.h>

#include "./globals.cpp"

namespace utility{
	
	void clear(){
		
		system("cls");
		
	}

  void moveCursor(short x, short y){
	
    COORD coordinate = {x, y};
    SetConsoleCursorPosition(OUTPUTHANDLE, coordinate);
    
  }
	
}
