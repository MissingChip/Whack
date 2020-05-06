
aggr := worker.make
make_worker = make -f $(aggr) -C ./$@ lib_dir=../lib flags="-std=c++17"
tile:
	@$(make_worker)
.PHONY: tile

visual: tile
	$(CXX) -o $@ tile/mod/GUI/visual.cpp $(CXXFLAGS) -Llib $(patsubst lib/lib%.a, -l%, $(wildcard lib/lib*.a)) -lglfw -lGLEW -lGL -Itile -std=c++17