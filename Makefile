COMPILER = g++
FLAGS = -MMD -c -Wall -Werror -o

.PHONY: clean run all

all: create bin/chessviz

-include build/*.d

bin/chessviz: build/main.o build/checks.o build/board_read.o build/board.o build/board_print_html.o build/board_print_plain.o
	$(COMPILER) $^ -o $@

build/main.o: src/main.cpp
	$(COMPILER) $(FLAGS) $@ $<

build/board.o: src/board.cpp
	$(COMPILER) $(FLAGS) $@  $<

build/checks.o: src/checks.cpp
	$(COMPILER) $(FLAGS) $@  $<

build/board_read.o: src/board_read.cpp
	$(COMPILER) $(FLAGS) $@  $<

build/board_print_html.o: src/board_print_html.cpp
	$(COMPILER) $(FLAGS) $@  $<

build/board_print_plain.o: src/board_print_plain.cpp
	$(COMPILER) $(FLAGS) $@  $<

create:
	mkdir -p build/ bin/

clean:
	rm -rf build/ bin/ build/src

run: all
	./bin/chessviz