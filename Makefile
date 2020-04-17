
CXX = g++
CXXFLAGS = -IA

ODIR = A/obj

$(ODIR)/libwhack.a:
	make -C ./A

.PHONY: $(ODIR)/libwhack.a

try: $(ODIR)/libwhack.a
	$(CXX) -o try try.cpp -L$(ODIR) -lwhack $(CXXFLAGS)

.PHONY: test