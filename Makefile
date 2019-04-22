COMPILER = g++
FLAGS = -MMD -c -Wall -Werror -std=c++14 -o

.PHONY: clean run all

all: create bin/chessviz #bin/chessviz-test

-include build/src/*.d

bin/chessviz: build/src/main.o build/src/checks.o build/src/board_read.o build/src/board.o build/src/board_print_html.o build/src/board_print_plain.o
	$(COMPILER) $^ -o $@

build/src/main.o: src/main.cpp
	$(COMPILER) $(FLAGS) $@ $<

build/src/board.o: src/board.cpp
	$(COMPILER) $(FLAGS) $@  $<

build/src/checks.o: src/checks.cpp
	$(COMPILER) $(FLAGS) $@  $<

build/src/board_read.o: src/board_read.cpp
	$(COMPILER) $(FLAGS) $@  $<

build/src/board_print_html.o: src/board_print_html.cpp
	$(COMPILER) $(FLAGS) $@  $<

build/src/board_print_plain.o: src/board_print_plain.cpp
	$(COMPILER) $(FLAGS) $@  $<
	

#-include build/test/*.d

#bin/chessviz-test:
#	$(COMPILER) $(FLAGS) -o $@ $^
#...
#build/test/

create:
	mkdir -p bin/temp build/src build/test

clean:
	rm -rf build/ bin/ 