CXX=g++
CFLAGS=-Wall -O3 -std=c++11

all: test add_cube

test: main.o cube.o
	$(CXX) $(CFLAGS) main.o cube.o -o test.x

add_cube: add_cube.o cube.o
	$(CXX) $(CFLAGS) add_cube.o cube.o -o add_cube.x

main.o: main.cpp Cube.cpp
	$(CXX) $(CFLAGS) -c main.cpp

add_cube.o: add_cube.cpp Cube.cpp
	$(CXX) $(CFLAGS) -c add_cube.cpp

cube.o: Cube.cpp
	$(CXX) $(CFLAGS) -c Cube.cpp

clean:
	rm -f *o
