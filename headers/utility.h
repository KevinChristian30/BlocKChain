#include <iostream>

namespace utility{

  void clear();

  void moveCursor(short x, short y);

  void animateString(const char* toAnimate, unsigned long long int delay);

  namespace hash{

    std::string ShaKCe(char input[]);

  }

}