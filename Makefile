CC=g++

all: prog

prog: MatrixMath.out

MatrixMath_new.out : MatrixMath_new.cpp
	$(CC) MatrixMath_new.cpp -o MatrixMath_new.out

clean:
	rm -rf *.out