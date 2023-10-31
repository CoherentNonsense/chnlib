build/chnlib.o: src/logger.c
	gcc -c -O3 -Iinclude $^ -o $@

build/logger.test: src/logger.c test/logger.test.c
	gcc -O3 -Iinclude $^ -o $@

test: build/logger.test
