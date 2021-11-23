all: clean compile run

clean:
	rm -f main Point.o main.o

compile:
	g++ -g -O3 -Wall -Wextra -c Point.cpp -o Point.o
	g++ -g -O3 -Wall -Wextra -c main.cpp -o main.o
	g++ -g -O3 -Wall -Wextra -o main Point.o main.o

run:
	./main demo.txt
