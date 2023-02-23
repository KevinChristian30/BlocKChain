
CXX=g++

output: main.o indexScreen.o utility.o exitScreen.o loginScreen.o registerScreen.o validator.o database.o Account.o globals.o mainMenu.o
	$(CXX) main.o indexScreen.o utility.o exitScreen.o loginScreen.o registerScreen.o validator.o database.o Account.o globals.o mainMenu.o -o BlocKChain

main.o: main.cpp
	$(CXX) -c main.cpp

indexScreen.o: sources/indexScreen.cpp headers/indexScreen.h
	$(CXX) -c sources/indexScreen.cpp

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

database.o: sources/database.cpp headers/database.h
	$(CXX) -c sources/database.cpp

globals.o: sources/globals.cpp headers/globals.h
	$(CXX) -c sources/globals.cpp

mainMenu.o: sources/mainMenu.cpp headers/mainMenu.h
	$(CXX) -c sources/mainMenu.cpp

Account.o: models/Account.cpp models/Account.h
	$(CXX) -c models/Account.cpp

clean:
	del *.o BlocKChain.exe