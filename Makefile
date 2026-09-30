all: create

create:
	g++ -std=c++17 main.cpp hash.cpp tests.cpp -o main

run: create
	./main

clean:
	rm -f main