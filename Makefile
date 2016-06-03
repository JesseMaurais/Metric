CC=g++
CFLAGS=-std=c++17
OBJ=maths.so stats.so
DIR=/usr/local/lib/lua/5.3/

all: $(OBJ)

clean:
	rm $(OBJ)

install:
	mkdir -p $(DIR)
	cp $(OBJ) $(DIR)
	
uninstall:
	rm $(addprefix $(DIR), $(OBJ))

%.so: %.cpp %.hpp
	$(CC) $(CFLAGS) -shared -o $@ -fpic $< -lm

blas.so: blas.cpp cblas.hpp
	$(CC) $(CFLAGS) -shared -o $@ -fpic $< -lblas

lapack.so: lapack.cpp lapacke.hpp
	$(CC) $(CFLAGS) -shared -o $@ -fpic $< -llapacke

