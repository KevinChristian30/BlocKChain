#ifndef UTILITY_H
#define UTILITY_H

namespace utility{

  void clear();

  void moveCursor(short x, short y);

  void animateString(const char* toAnimate, unsigned long long int delay);

  void setColor(const char* color);

  void putLine(const char character, int numberOfTimes);

}

#endif