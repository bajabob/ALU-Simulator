all: Test.o
	g++-4.7 -std=c++11 Test.o -o test

Test.o: Test.cpp
	g++-4.7 -std=c++11 -c Test.cpp
	
clean:
	rm *.o test
