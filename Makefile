
worker := worker.make
WORK = cp $(worker) ./$@/$(worker) && make -f worker.make -C ./$@ lib_dir=../lib flags="-std=c++17 $(flags)"
GUI: tile
	$(eval flags := -I../tile)
	@$(WORK) lib_deps=mod
	rm ./$@/$(worker)
tile:
	@$(WORK)
	rm ./$@/$(worker)
.PHONY: tile

visual: GUI
	$(CXX) -o $@ GUI/visual.cpp $(CXXFLAGS) -Llib $(patsubst lib/lib%.a, -l%, $(wildcard lib/lib*.a)) -lglfw -lGLEW -lGL -Itile -std=c++17