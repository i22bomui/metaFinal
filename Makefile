OS := $(shell uname)

ifeq ($(OS),Darwin)
   CC = clang++
   FLAGS = -Wall  -lm -std=c++14# -I/usr/local/include/  -L /usr/local/lib/ -lgsl -lgslcblas -lm -std=c++14
else ifeq ($(OS),Linux)
   CC = g++-5
   FLAGS = -lm -std=c++14
endif

DEBUG = -g

all:
	$(CC) -o main main.cpp $(FLAGS)

automat: FLAGS := $(FLAGS) -O3
automat:
	$(CC) -o main_auto main_auto.cpp $(FLAGS)

debug: FLAGS := $(FLAGS) -g
debug: all

optimize: FLAGS := $(FLAGS) -O3
optimize: all

uco: CC = g++
uco: all

clean:
	if [ -f main ]; then rm main;fi;
	if [ -f main ]; then rm main_auto;fi;
	if [ -d main.dSYM ]; then rm -r main.dSYM; fi;

update: clean
update: all
