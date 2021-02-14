all:
	cmake -H. -Bbuild

build:
	cd build/; make

run:
	./Snake

debug:
	gdb ./build/build/Snake

.PHONY: all build run debug
