
libraries: libserver.a libconfig.a libbmp.a libimageProcessing.a

libserver.a: server.o
	#Create an static library
	ar rv lib/libserver.a lib/server.o
	ranlib lib/libserver.a

libbmp.a: bmp.o
	ar rv lib/libbmp.a lib/bmp.o
	ranlib lib/libbmp.a

libimageProcessing.a: imageProcessing.o
	ar rv lib/libimageProcessing.a lib/imageProcessing.o
	ranlib lib/libimageProcessing.a

libconfig.a: config.o
	ar rv lib/libconfig.a lib/config.o
	ranlib lib/libconfig.a

server.o: lib/server.c include/server.h
	gcc -c lib/server.c -o lib/server.o -Iinclude

config.o: lib/config.c include/config.h
	gcc -c lib/config.c -o lib/config.o -Iinclude

bmp.o: lib/bmp.c include/bmp.h
	gcc -c lib/bmp.c -o lib/bmp.o -Iinclude

imageProcessing.o: lib/imageProcessing.c include/imageProcessing.h
	gcc -c lib/imageProcessing.c -o lib/imageProcessing.o -Iinclude
