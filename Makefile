CPP=g++
CPP11=${CPP} -std=c++11

all: binary

binary: test.cc *.h with_gflags/*.h
	${CPP11} -o $@ $< -lpthread -lgflags

clean:
	rm -rf binary
