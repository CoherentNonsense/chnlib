CFILES = $(wildcard src/*.c src/*/*.c)
FLAGS = -O3 -Wall -Wextra -pedantic

all: build/logger build/dynarray

build/logger: $(CFILES) test/logger.test.c
	gcc $(FLAGS) -Iinclude $^ -o $@

build/dynarray: $(CFILES) test/dynarray.test.c
	gcc $(FLAGS) -Iinclude $^ -o $@
