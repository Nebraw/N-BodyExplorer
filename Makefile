CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++14 -I include 'sdl-config --libs'
SRC = src/*.cc
HEAD = include/*.hh
EXE = cppa

all: $(EXE)
	./$(EXE)

$(EXE): $(SRC) $(HEAD)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

debug:CXXFLAGS+=-g
debug:$(EXE)

clean:
	rm -f src/*.o
	rm -f $(EXE)
