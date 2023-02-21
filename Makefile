
CXX=g++

output: main.o mainMenuScreen.o utility.o exitScreen.o loginScreen.o registerScreen.o validator.o
	$(CXX) main.o mainMenuScreen.o utility.o exitScreen.o loginScreen.o registerScreen.o validator.o -o BlocKChain

main.o: main.cpp
	$(CXX) -c main.cpp

mainMenuScreen.o: sources/mainMenuScreen.cpp headers/mainMenuScreen.h
	$(CXX) -c sources/mainMenuScreen.cpp

utility.o: sources/utility.cpp headers/utility.h
	$(CXX) -c sources/utility.cpp

exitScreen.o: sources/exitScreen.cpp headers/exitScreen.h
	$(CXX) -c sources/exitScreen.cpp

loginScreen.o: sources/loginScreen.cpp headers/loginScreen.h
	$(CXX) -c sources/loginScreen.cpp 

registerScreen.o: sources/registerScreen.cpp headers/registerScreen.h
	$(CXX) -c sources/registerScreen.cpp

validator.o: sources/validator.cpp headers/validator.h
	$(CXX) -c sources/validator.cpp
clean:
	del *.o BlocKChain.exe