all: clean compile run
clean:
	rm -f main Point.o Drone.o main.o
compile:
	g++ -g -O3 -Wall -Wextra -c Point.cpp -o Point.o
	g++ -g -O3 -Wall -Wextra -c Drone.cpp -o Drone.o
	g++ -g -O3 -Wall -Wextra -c main.cpp -o main.o
	g++ -g -O3 -Wall -Wextra -o main Point.o Drone.o main.o
run:
	./main demo.txt
