
CXX=g++

output: main.o indexScreen.o utility.o exitScreen.o loginScreen.o registerScreen.o validator.o database.o Account.o globals.o mainMenuScreen.o myAccountScreen.o changePasswordScreen.o
	$(CXX) main.o indexScreen.o utility.o exitScreen.o loginScreen.o registerScreen.o validator.o database.o Account.o globals.o mainMenuScreen.o myAccountScreen.o changePasswordScreen.o -o BlocKChain

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

mainMenuScreen.o: sources/mainMenuScreen.cpp headers/mainMenuScreen.h
	$(CXX) -c sources/mainMenuScreen.cpp

myAccountScreen.o: sources/myAccountScreen.cpp headers/myAccountScreen.h
	$(CXX) -c sources/myAccountScreen.cpp

changePasswordScreen.o: sources/changePasswordScreen.cpp headers/changePasswordScreen.h
	$(CXX) -c sources/changePasswordScreen.cpp

Account.o: models/Account.cpp models/Account.h
	$(CXX) -c models/Account.cpp

clean:
	del *.o BlocKChain.exe