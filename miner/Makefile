
CXX=g++

output: main.o globals.o database.o utility.o indexScreen.o loginScreen.o exitScreen.o Account.o Transaction.o
	$(CXX) main.o globals.o database.o utility.o indexScreen.o loginScreen.o exitScreen.o Account.o Transaction.o -o BlueMiner

main.o: main.cpp
	$(CXX) -c main.cpp

database.o: sources/database.cpp headers/database.h
	$(CXX) -c sources/database.cpp

globals.o: sources/globals.cpp headers/globals.h
	$(CXX) -c sources/globals.cpp

utility.o: sources/utility.cpp headers/utility.h
	$(CXX) -c sources/utility.cpp

indexScreen.o: sources/indexScreen.cpp headers/indexScreen.h
	$(CXX) -c sources/indexScreen.cpp

loginScreen.o: sources/loginScreen.cpp headers/loginScreen.h
	$(CXX) -c sources/loginScreen.cpp

exitScreen.o: sources/exitScreen.cpp headers/exitScreen.h
	$(CXX) -c sources/exitScreen.cpp

Account.o: models/Account.cpp models/Account.h
	$(CXX) -c models/Account.cpp

Transaction.o: models/Transaction.cpp models/Transaction.h
	$(CXX) -c models/Transaction.cpp

clean:
	del *.o BlueMiner.exe