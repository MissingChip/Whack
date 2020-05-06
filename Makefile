
worker := worker.make
WORK = cp $(worker) ./$@/$(worker) && make -f worker.make -C ./$@ lib_dir=../lib flags="-std=c++17 $(flags)" && rm ./$@/$(worker)
GUI: tile
	$(eval flags := -I../tile -ltile -lmod)
	@$(WORK)
tile:
	@$(WORK)
.PHONY: tile

visual: GUI
	$(CXX) -o $@ GUI/visual.cpp $(CXXFLAGS) -Llib $(patsubst lib/lib%.a, -l%, $(wildcard lib/lib*.a)) -lglfw -lGLEW -lGL -Itile -std=c++17