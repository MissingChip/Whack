
test.out:
	make -C ./A
	g++ -o test.out test.cpp -L. -lwhack

.PHONY: test.out