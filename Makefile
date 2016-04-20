CXX=g++
CFLAGS=-Wall -O3 -std=c++11

all: test cube_add

test: main.o cube.o
	$(CXX) $(CFLAGS) main.o cube.o -o test.x

cube_add: cube_add.o cube.o
	$(CXX) $(CFLAGS) cube_add.o cube.o -o cube_add.x

main.o: main.cpp Cube.cpp
	$(CXX) $(CFLAGS) -c main.cpp

cube_add.o: cube_add.cpp Cube.cpp
	$(CXX) $(CFLAGS) -c cube_add.cpp

cube.o: Cube.cpp
	$(CXX) $(CFLAGS) -c Cube.cpp

clean:
	rm -f *o
