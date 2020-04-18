
LIBNAME = visual
TESTNAME = visual

IDIR = . ../include
ODIR = obj

OBJS = $(patsubst %.cpp, $(ODIR)/%.o, $(wildcard *.cpp))
DEPS = $(wildcard $(IDIR)/*.h)

CXX = g++
CXXFLAGS = -L$(ODIR) $(patsubst %, -I%,$(IDIR)) -lGL -lGLEW -lglfw -l$(LIBNAME)

default: $(TESTNAME)
.PHONY: default

$(ODIR)/lib$(LIBNAME).a: $(OBJS)
	ar -rcs $(ODIR)/lib$(LIBNAME).a $?

obj/%.o: %.cpp $(DEPS)
	@mkdir -p $(ODIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(TESTNAME): $(ODIR)/lib$(LIBNAME).a Makefile
	$(CXX) -o $(TESTNAME) $(TESTNAME).cpp $(CXXFLAGS)
