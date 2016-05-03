CC=g++
CFLAGS=-std=c++11
OBJ=blas.so lapack.so
DIR=/usr/local/lib/lua/5.3/

all: $(OBJ)

clean:
	rm $(OBJ)

install:
	mkdir -p $(DIR)
	cp $(OBJ) $(DIR)
	
uninstall:
	rm $(addprefix $(DIR), $(OBJ))

blas.so: blas.cpp cblas.hpp
	$(CC) $(CFLAGS) -shared -o $@ -fpic $< -lblas

lapack.so: lapack.cpp lapacke.hpp
	$(CC) $(CFLAGS) -shared -o $@ -fpic $< -llapacke

