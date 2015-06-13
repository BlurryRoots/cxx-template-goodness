
default: build

build:
	mkdir -p bin
	$(CXX) --std=c++11 src/main.cpp -o bin/tg

run: build
	bin/./tg
