

OBJS = $(patsubst %.cpp, obj/%.o, $(wildcard *.cpp))
OBJS += $(wildcard mod/bin/*.o)

bin/libwhack.a: $(OBJS)
	ar -rcs bin/libwhack.a $?

try:
	g++ -o try try.cpp group.cpp mod/stretchmod.cpp