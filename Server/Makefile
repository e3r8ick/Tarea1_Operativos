all: server

clean:
	@rm -rf *.o
	@rm -rf server

server: main.o server.o
	gcc -o server $^

main.o: main.c server.h
	gcc -c -o main.o main.c

httpd.o: server.c server.h
	gcc -c -o server.o server.c
