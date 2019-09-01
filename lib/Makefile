
librest.a: rest.o server.o
	#Create an static library
	ar rv lib/librest.a lib/rest.o
	ranlib lib/librest.a
	ar rv lib/libserver.a lib/server.o
	ranlib lib/libserver.a

rest.o:
	gcc -c lib/rest.c -o lib/rest.o -Iinclude

server.o:
	gcc -c lib/server.c -o lib/server.o -Iinclude