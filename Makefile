
CXX = g++
CXXFLAGS = -IA

ODIR = A/obj

$(ODIR)/libwhack.a:
	make -C ./tile

.PHONY: $(ODIR)/libwhack.a

try: $(ODIR)/libwhack.a
	$(CXX) -o try try.cpp -L$(ODIR) -lwhack $(CXXFLAGS)

visual: $(ODIR)/libwhack.a
	make -C ./GUI

.PHONY: visual

.PHONY: test