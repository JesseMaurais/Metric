CC=g++
CFLAGS=-std=c++11
OBJ=blas.so lapack.so

all: $(OBJ)

clean:
	rm $(OBJ)

blas.so: blas.cpp cblas.hpp
	$(CC) $(CFLAGS) -shared -o $@ -fpic $< -lblas

lapack.so: lapack.cpp lapacke.hpp
	$(CC) $(CFLAGS) -shared -o $@ -fpic $< -llapacke

