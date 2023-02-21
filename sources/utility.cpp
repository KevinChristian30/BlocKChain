#include <stdio.h>
#include <windows.h>
#include <iostream>

#include <vector>

#include "./globals.cpp"

namespace utility{
	
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

  namespace hash{

    void toBinaryString(int value, char *result, int *index){

      char baseRange[] = "01";
      if (value >= 2) toBinaryString(value / 2, result, index);
      result[(*index)++] = baseRange[value % 2];

    }

    char* decimalToBinary(int value){

      char* result = (char*) malloc(sizeof(char) * 16);
      int index = 0;

      toBinaryString(value, result, &index);
      result[index] = '\0';

      return result;

    }

    char* padZeros(char input[], short outputLength){

      char* result = (char*) malloc(sizeof(char) * (outputLength + 1));
      for (short i = 0; i < outputLength; i++) result[i] = '0';
      result[outputLength] = '\0';

      size_t length = strlen(input);
      for (int i = outputLength - length, j = 0; i < outputLength; i++, j++) 
        result[i] = input[j];

      return result;

    }

    void SHA1(char input[]){

      size_t length = strlen(input);

      std::vector<short> asciiArray;
      for (size_t i = 0; i < length; i++) asciiArray.push_back(input[i]);

      char* joinedBinary = (char*) malloc(sizeof(char) * length * (8 + 1));
      int index = 0;
      for (size_t i = 0; i < length; i++) {

        char* result = padZeros(decimalToBinary(asciiArray.at(i)), 8);
        for (int i = 0; i < 8; i++) joinedBinary[index++] = result[i];

      }
      joinedBinary[index] = '1';

      std::string result448 = joinedBinary;
      while (result448.length() % 512 != 418) result448 += "0";

      std::string result64 = padZeros(decimalToBinary(asciiArray.size() * 8), 64);
      
      std::string result512 = result448 + result64;
      std::cout << result512;

    }

  }

}
