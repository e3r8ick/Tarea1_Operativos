
libraries: libserver.a libconfig.a
	
libserver.a: server.o
	#Create an static library
	ar rv lib/libserver.a lib/server.o
	ranlib lib/libserver.a

libconfig.a: config.o
	ar rv lib/libconfig.a lib/config.o
	ranlib lib/libconfig.a

server.o: lib/server.c include/server.h
	gcc -c lib/server.c -o lib/server.o -Iinclude

config.o: lib/config.c include/config.h
	gcc -c lib/config.c -o lib/config.o -Iinclude