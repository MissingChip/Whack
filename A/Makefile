
OBJS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

all: ../libwhack.a
	@echo $(OBJS)
.PHONY: all

../libwhack.a: $(OBJS)
	ar -rcs $@ $?

%.o: %.cpp %.h Makefile
	g++ -c -o $@ $<