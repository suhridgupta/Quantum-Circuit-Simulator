CC = g++
HOME = .
SRC = $(HOME)/src
BIN = $(HOME)/bin
H_FILES = definitions.h
CPP_FILES = utils.cpp complex.cpp main.cpp
OUTPUT_FILE = quantumcpp.out
H = $(H_FILES:%.h=$(SRC)/%.h)
CPP = $(CPP_FILES:%.cpp=$(SRC)/%.cpp)

compile:
	mkdir -p $(BIN)
	$(CC) $(H) $(CPP) -o $(BIN)/$(OUTPUT_FILE)

run:
	$(BIN)/$(OUTPUT_FILE)

clean:
	rm -rf $(BIN)/*