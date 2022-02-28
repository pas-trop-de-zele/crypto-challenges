CC=clang++
FLAG=-g -std=c++11
OBJECTIVE=main

all : main.o utils.o
	$(CC) $(FLAG) main.cpp utils.cpp -o $(OBJECTIVE)