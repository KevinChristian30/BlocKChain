#ifndef VALIDATOR_H
#define VALIDATOR_H

namespace validator{

  bool minLength(char input[], unsigned long long int minimumLength);

  bool contains(char input[], char toCheck);

  bool isAlpha(char input[]);

  bool isNumeric(char input[]);

}

#endif