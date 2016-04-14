CXX=g++
CFLAGS=-Wall -O3 -std=c++11

all: test

test: main.o cube.o 
	$(CXX) $(CFLAGS) main.o cube.o -o test.x

main.o: main.cpp Cube.cpp
	$(CXX) $(CFLAGS) -c main.cpp

cube.o: Cube.cpp
	$(CXX) $(CFLAGS) -c Cube.cpp

clean:
	rm -f *o
