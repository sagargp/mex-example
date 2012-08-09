all:
	mex CFLAGS="-fPIC -std=c99 -O3" -g test.cpp

clean:
	rm -f *.mexa64
