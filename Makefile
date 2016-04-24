CXX=g++
CFLAGS=-Wall -O3 -std=c++11

BIN=bin

all: ${BIN} test cube_add cube_sub cube_planavg

test: main.o cube.o average.o
	$(CXX) $(CFLAGS) main.o cube.o average.o -o ${BIN}/test.x

cube_add: cube_add.o cube.o
	$(CXX) $(CFLAGS) cube_add.o cube.o -o ${BIN}/cube_add.x

cube_sub: cube_sub.o cube.o
	$(CXX) $(CFLAGS) cube_sub.o cube.o -o ${BIN}/cube_sub.x

cube_planavg: cube_planavg.o cube.o average.o
	$(CXX) $(CFLAGS) cube_planavg.o cube.o average.o -o ${BIN}/cube_planavg.x

main.o: main.cpp Cube.cpp average.cpp
	$(CXX) $(CFLAGS) -c main.cpp

cube_add.o: cube_add.cpp Cube.cpp
	$(CXX) $(CFLAGS) -c cube_add.cpp

cube_sub.o: cube_sub.cpp Cube.cpp
	$(CXX) $(CFLAGS) -c cube_sub.cpp

cube_planavg.o: cube_planavg.cpp Cube.cpp average.cpp
	$(CXX) $(CFLAGS) -c cube_planavg.cpp

cube.o: Cube.cpp
	$(CXX) $(CFLAGS) -c Cube.cpp

average.o: average.cpp
	$(CXX) $(CFLAGS) -c average.cpp

clean:
	rm -f *o
	
${BIN}:
	mkdir -p ${BIN}

