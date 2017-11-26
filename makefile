all: matrix clean

matrix: main.o matrix.o
        g++ main.o matrix.o -o matrix

main.o: main.cpp
        g++ main.cpp -c

matrix.o: matrix.cpp
          g++ matrix.cpp -c

clean:
        rm *.o matrix
