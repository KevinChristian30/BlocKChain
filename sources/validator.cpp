#include <string.h>

#ifndef VALIDATOR_H
#define VALIDATOR_H

namespace validator{

  bool minLength(char input[], unsigned long long int minimumLength){

    return strlen(input) >= minimumLength;

  }

  bool contains(char input[], char toCheck){

    bool containsToCheck = false;

    size_t length = strlen(input);
    for (size_t i = 0; i < length; i++){

      if (input[i] == toCheck){

        containsToCheck = true;
        break;

      }

    }

    return containsToCheck;

  }

  bool isAlpha(char input[]){

    size_t length = strlen(input);
    for (size_t i = 0; i < length; i++){

      if (input[i] >= 'A' && input[i] <= 'Z' || input[i] >= 'a' && input[i] <= 'z')
        return true;

    }

    return false;

  }

  bool isNumeric(char input[]){

    size_t length = strlen(input);
    for (size_t i = 0; i < length; i++){

      if (input[i] >= '0' && input[i] <= '9') return true;
        
    }

    return false;

  }

}

#endif