FLAG=-std=c++11 -lboost_filesystem -lboost_system

parser:parser.cc
	g++ $^ -o $@ $(FLAG)

.PHONY:clean
clean:
	rm parser