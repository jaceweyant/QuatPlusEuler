test: testAgainst.o
	g++ --std=c++11 testAgainst.o -o test

testAgainst.o: testAgainst.cpp
	g++ -c --std=c++11 testAgainst.cpp

clean:
	rn *.o test