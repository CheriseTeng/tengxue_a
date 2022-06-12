all:
	gcc -c test.c tranfunc.c
	gcc test.o tranfunc.o -o ./bin/test
	gcc -c tcp_server.c -lpthread 
	gcc -c tcp_client.c 
	gcc tcp_server.o -o ./bin/tcp_server -lpthread 
	gcc tcp_client.o -o ./bin/tcp_client

clean:
	rm ./bin/test ./bin/tcp_server ./bin/tcp_client
	rm test.o tranfunc.o tcp_server.o tcp_client.o
