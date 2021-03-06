CXX=g++
CFLAGS=-Wall -O3 -std=c++11 -lfftw3 -lm

BIN=bin

all: ${BIN} test cube_add cube_sub cube_mult cube_planavg cube_totavg cube_local cube_macroavg cube_shift

test: main.o cube.o average.o interpolation.o function.o
	$(CXX) $(CFLAGS) main.o cube.o average.o interpolation.o function.o -o ${BIN}/test.x

cube_add: cube_add.o cube.o
	$(CXX) $(CFLAGS) cube_add.o cube.o -o ${BIN}/cube_add.x

cube_sub: cube_sub.o cube.o
	$(CXX) $(CFLAGS) cube_sub.o cube.o -o ${BIN}/cube_sub.x

cube_mult: cube_mult.o cube.o
	$(CXX) $(CFLAGS) cube_mult.o cube.o -o ${BIN}/cube_mult.x

cube_planavg: cube_planavg.o cube.o average.o function.o interpolation.o
	$(CXX) $(CFLAGS) cube_planavg.o cube.o average.o function.o interpolation.o -o ${BIN}/cube_planavg.x

cube_totavg: cube_totavg.o cube.o average.o function.o interpolation.o
	$(CXX) $(CFLAGS) cube_totavg.o cube.o average.o function.o interpolation.o -o ${BIN}/cube_totavg.x

cube_local: cube_local.o cube.o average.o function.o interpolation.o
	$(CXX) $(CFLAGS) cube_local.o cube.o average.o function.o interpolation.o -o ${BIN}/cube_local.x

cube_macroavg: cube_macroavg.o cube.o average.o function.o interpolation.o
	$(CXX) $(CFLAGS) cube_macroavg.o cube.o average.o function.o interpolation.o -o ${BIN}/cube_macroavg.x

cube_shift: cube_shift.o cube.o
	$(CXX) $(CFLAGS) cube_shift.o cube.o -o ${BIN}/cube_shift.x

main.o: main.cpp Cube.cpp average.cpp interpolation.cpp function.cpp
	$(CXX) $(CFLAGS) -c main.cpp

cube_add.o: cube_add.cpp Cube.cpp
	$(CXX) $(CFLAGS) -c cube_add.cpp

cube_sub.o: cube_sub.cpp Cube.cpp
	$(CXX) $(CFLAGS) -c cube_sub.cpp

cube_mult.o: cube_mult.cpp Cube.cpp
	$(CXX) $(CFLAGS) -c cube_mult.cpp

cube_planavg.o: cube_planavg.cpp Cube.cpp average.cpp interpolation.cpp
	$(CXX) $(CFLAGS) -c cube_planavg.cpp

cube_totavg.o: cube_totavg.cpp Cube.cpp average.cpp interpolation.cpp
	$(CXX) $(CFLAGS) -c cube_totavg.cpp

cube_local.o: cube_local.cpp Cube.cpp average.cpp function.cpp
	$(CXX) $(CFLAGS) -c cube_local.cpp

cube_macroavg.o: cube_macroavg.cpp Cube.cpp average.cpp function.cpp interpolation.cpp
	$(CXX) $(CFLAGS) -c cube_macroavg.cpp

cube_shift.o: cube_shift.cpp Cube.cpp
	$(CXX) $(CFLAGS) -c cube_shift.cpp

cube.o: Cube.cpp
	$(CXX) $(CFLAGS) -c Cube.cpp

average.o: average.cpp
	$(CXX) $(CFLAGS) -c average.cpp

interpolation.o: interpolation.cpp
	$(CXX) $(CFLAGS) -c interpolation.cpp

function.o: function.cpp
	$(CXX) $(CFLAGS) -c function.cpp

clean:
	rm -f *.o

${BIN}:
	mkdir -p ${BIN}
