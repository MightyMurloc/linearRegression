all: pf162a01

pf162a01: commonLib.o main.o linearRegression.o
	g++ main.o commonLib.o linearRegression.o -std=c++11 -o pf162a01

main.o: main.cpp commonLib.h
	g++ -c main.cpp -std=c++11
commonLib.o: commonLib.cpp commonLib.h
	g++ -c commonLib.cpp -std=c++11
linearRegression.o: linearRegression.cpp linearRegression.h commonLib.h
	g++ -c linearRegression.cpp -std=c++11

clean:
	rm *.o pf162a01
