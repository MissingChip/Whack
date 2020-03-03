
OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: ../libwhack.a
.PHONY: all

../libwhack.a: $(OBJS)
	ar -rcs $@ $?

%.o: %.cpp %.h Makefile
	g++ -c -o $@ $<

widget.o: widget.cpp widget.hpp widget.h