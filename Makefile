CC=g++

all: prog

prog: MatrixMath.out

MatrixMath_new.out : Matrix_Math_new.cpp
	$(CC) Matrix_Math_new.cpp -o MatrixMath_new.out

clean:
	rm -rf *.out