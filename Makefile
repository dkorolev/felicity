CPP=g++
CPP11=${CPP} -std=c++11

all: binary

binary: test.cc
	${CPP11} -o $@ $< -lpthread

clean:
	rm -rf binary
