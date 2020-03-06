
libwhack.a:
	make -C ./A

.PHONY: libwhack.a

test.out: libwhack.a
	make -C ./A
	g++ -o test.out test.cpp -L. -lwhack

.PHONY: test.out