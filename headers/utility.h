namespace utility{

  void clear();

  void moveCursor(short x, short y);

  void animateString(const char* toAnimate, unsigned long long int delay);

  namespace hash{

    void SHA1(char input[]);

  }

}