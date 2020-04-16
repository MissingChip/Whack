

IDIR = .
ODIR = obj

OBJS = $(patsubst %.cpp, $(ODIR)/%.o, $(wildcard *.cpp))
DEPS = $(wildcard $(IDIR)/*.h)

CXX = g++
CXXFLAGS = -I$(IDIR)

$(ODIR)/libwhack.a: $(OBJS)
	ar -rcs $(ODIR)/libwhack.a $?

obj/%.o: %.cpp $(DEPS)
	@mkdir -p $(ODIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

try: $(OBJS)
	$(CXX) -o try try.cpp -L$(ODIR) -lwhack $(CFLAGS)