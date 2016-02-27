CXX=clang++

CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-parameter -Wno-unused-private-field -g

BINARIES = prog3

all: ${BINARIES}
prog3: main.o AdjListObject.o AdjacenyList.o 
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o
