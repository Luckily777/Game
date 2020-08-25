FLAG=-std=c++11 -I ~/third_part/include  -lpthread -L. -lsearcher

http_server:http_server.cc
	g++ $^ -o $@ $(FLAG)

.PHONY:clean
clean:
	rm  http_server