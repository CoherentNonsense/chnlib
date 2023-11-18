HFILES = $(wildcard include/*.h include/*/*.c)

CFILES = $(wildcard src/*.c src/*/*.c)
OFILES = $(patsubst src/%.c, build/%.o, $(CFILES))

TESTFILES = $(wildcard test/*.test.c)
TESTEXES = $(patsubst test/%.c, build/%, $(TESTFILES))


CC = gcc
AR = ar
FLAGS = -std=c11 -O3 -Wall -Wextra
INCLUDES = -Iinclude

ifeq ($(PREFIX),)
	PREFIX := /usr/local
endif


# =============
# build targets
# =============
default: build/libchn.a

# testing
test: $(TESTEXES)

build/%.test: $(CFILES) test/%.test.c
	mkdir -p $(@D)
	$(CC) $(FLAGS) -Iinclude $^ -o $@


# building
install: build/libchn.a
	install -d $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $< $(DESTDIR)$(PREFIX)/lib/
	install -d $(DESTDIR)$(PREFIX)/include/chnlib/
	install -m 644 $(HFILES) $(DESTDIR)$(PREFIX)/include/chnlib/

build/libchn.a: $(OFILES)
	$(AR) -rc $@ $^

build/%.o: src/%.c
	mkdir -p $(@D)
	gcc -c $(FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -r build
