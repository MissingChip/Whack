
CXX = g++
CXXFLAGS = -IA

ODIR = A/obj

$(ODIR)/libwhack.a:
	make -C ./A

.PHONY: $(ODIR)/libwhack.a

try: $(ODIR)/libwhack.a
	$(CXX) -o try try.cpp -L$(ODIR) -lwhack $(CXXFLAGS)

visual: $(ODIR)/libwhack.a
	$(CXX) -o visual GUI/visual.cpp GUI/shader.cpp GUI/vertex_group.cpp -L$(ODIR) -lwhack $(CXXFLAGS) -lGL -lGLEW -lglfw

.PHONY: test