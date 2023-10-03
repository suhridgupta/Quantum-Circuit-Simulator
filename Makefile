CC = g++
HOME = .
SRC = $(HOME)/src
BIN = $(HOME)/bin
H_FILES = definitions.h
CPP_FILES = utils.cpp complex.cpp main.cpp
H = $(H_FILES:%.h=$(SRC)/%.h)
CPP = $(CPP_FILES:%.cpp=$(SRC)/%.cpp)

compile:
	mkdir -p $(BIN)
	$(CC) $(H) $(CPP) -o $(BIN)/quantumcpp.out

run:
	$(BIN)/quantumcpp.out

clean:
	rm -rf $(BIN)/*