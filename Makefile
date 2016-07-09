CC=g++
CFLAGS=-std=c++14 -Wall
SRC=arithmetic.hpp numeric.hpp statistics.hpp
OBJ=arithmetic.so numeric.so statistics.so
DIR=/usr/local/lib/lua/5.3/

all: $(OBJ)

clean:
	rm $(OBJ)

install:
	mkdir -p $(DIR)
	cp $(OBJ) $(DIR)
	
uninstall:
	rm $(addprefix $(DIR), $(OBJ))

%.so: %.cpp $(SRC)
	$(CC) $(CFLAGS) -shared -o $@ -fpic $< -lm

