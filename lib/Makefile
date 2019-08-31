
librest.a: rest.o
	#Create an static library
	ar rv lib/librest.a lib/rest.o
	ranlib lib/librest.a

rest.o:
	gcc -c lib/rest.c -o lib/rest.o -Iinclude