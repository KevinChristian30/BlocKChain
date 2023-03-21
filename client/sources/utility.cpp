#include <stdio.h>
#include <windows.h>
#include <iostream>

#include <vector>

#ifndef UTILITY_CPP
#define UTILITY_CPP

#include "../models/Transaction.h"

namespace utility{

  #define BUFFERSIZE 255
  const HANDLE OUTPUTHANDLE = GetStdHandle(STD_OUTPUT_HANDLE);

  #define FOREGROUND_WHITE 0xF7
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

    if (strcmp(color, "FOREGROUND_RED") == 0) {}
      // SetConsoleTextAttribute(OUTPUTHANDLE, FOREGROUND_RED);
      // SetConsoleTextAttribute(OUTPUTHANDLE, 0xF4);
      // SetConsoleTextAttribute(OUTPUTHANDLE, 0xF0);
    else if (strcmp(color, "FOREGROUND_GREEN") == 0) {}
      // SetConsoleTextAttribute(OUTPUTHANDLE, FOREGROUND_GREEN);
      // SetConsoleTextAttribute(OUTPUTHANDLE, 0xF2);
      // SetConsoleTextAttribute(OUTPUTHANDLE, 0xF0);
    else if (strcmp(color, "FOREGROUND_BLUE") == 0) {}
      // SetConsoleTextAttribute(OUTPUTHANDLE, FOREGROUND_LIGHTBLUE);
      // SetConsoleTextAttribute(OUTPUTHANDLE, 0xF9);
      // SetConsoleTextAttribute(OUTPUTHANDLE, 0xF0);
    else if (strcmp(color, "FOREGROUND_WHITE") == 0) {}
      // SetConsoleTextAttribute(OUTPUTHANDLE, FOREGROUND_WHITE);
    else if (strcmp(color, "BACKGROUND_WHITE") == 0) {}
      // SetConsoleTextAttribute(OUTPUTHANDLE, FOREGROUND_WHITE);

  }

  void putLine(const char character, int numberOfTimes){

    for (int i = 0; i < numberOfTimes; i++) printf("%c", character);
    puts("");

  }

  Transaction* parseTransaction(char input[]){

    Transaction* transaction = (Transaction*) malloc(sizeof(Transaction));

    // Sender
    strncpy(transaction->sender, "", BUFFERSIZE);
    int startIndex = 0, endIndex = 0;
    while (input[endIndex] != '#') endIndex++;

    while (startIndex < endIndex) {
      transaction->sender[startIndex] = input[startIndex];
      startIndex++;
    }

    // Receiver
    strncpy(transaction->receiver, "", BUFFERSIZE);
    startIndex = endIndex + 1;

    endIndex++;
    while (input[endIndex] != '#') endIndex++;

    int currentIndex = 0;
    while (startIndex < endIndex) {
      transaction->receiver[currentIndex++] = input[startIndex];
      startIndex++;
    }

    // Amount
    char amountBuffer[255] = "";
    startIndex = endIndex + 1;
    endIndex++;
    while (input[endIndex] != '#') endIndex++;

    currentIndex = 0;
    while (startIndex < endIndex) {
      amountBuffer[currentIndex++] = input[startIndex];
      startIndex++;
    }

    transaction->amount = atoi(amountBuffer);

    // Hash
    strncpy(transaction->hash, "", BUFFERSIZE);
    startIndex = endIndex + 1;

    endIndex++;
    while (input[endIndex] != '#') endIndex++;

    currentIndex = 0;
    while (startIndex < endIndex) {
      transaction->hash[currentIndex++] = input[startIndex];
      startIndex++;
    }

    strncpy(transaction->time, "", BUFFERSIZE);
    startIndex = endIndex + 1;

    endIndex++;
    while (input[endIndex] != '\0') endIndex++;

    currentIndex = 0;
    while (startIndex < endIndex) {
      transaction->time[currentIndex++] = input[startIndex];
      startIndex++;
    }
    
    return transaction;

  }

}

#endif