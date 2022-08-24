CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

LIBS := $(wildcard lib/*) 

all: bin/main

run: clean all
	clear
	./bin/main

bin/main: src/*
	$(CXX) $(CXX_FLAGS) $^ -I include -o bin/main -L lib $(LIBS) -lopengl32 -lgdi32

clean:
	-rm bin/main		