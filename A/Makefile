
OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: ../libwhack.a
.PHONY: all

../libwhack.a: $(OBJS)
	ar -rcs $@ $?

%.o: %.cpp %.h Makefile
	g++ -c -o $@ $<

tile.o: tile.cpp tile.hpp tile.h
	g++ -c -o $@ $<
.PHONY: