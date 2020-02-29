
test.out:
	g++ -o test.out test.cpp $(wildcard A/*.cpp)

.PHONY: test.out