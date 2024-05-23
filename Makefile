all: build/mine_sweeper

build/mine_sweeper: build/field.o build/main.o
	g++ -std=c++17 build/main.o build/field.o -obuild/mine_sweeper

build/main.o : tools/main.cpp
	g++ -std=c++17 -c tools/main.cpp -obuild/main.o

build/field.o: src/field.cpp
	g++ -std=c++17 -c src/field.cpp -obuild/field.o

clean:
	rm -rf built/*.o
	rm -rf build/mine_sweeper

