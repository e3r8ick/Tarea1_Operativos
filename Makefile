main:
	make -f lib/Makefile
	make -f src/Makefile

.PHONY: clean
clean:
	rm lib/*.a lib/*.o bin/*