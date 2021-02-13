all:
	cmake -H. -Bbuild

build:
	cd build/; make

run:
	./build/build/CSCSnake

debug:
	gdb ./build/build/CSCSnake

.PHONY: all build run debug
