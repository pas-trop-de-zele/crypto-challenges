CC=clang++
FLAG=-g -std=c++11
OBJECTIVE=main

all : main.o utils.o Q1.o Q2.o Q3.o Q4.o Q5.o
	$(CC) $(FLAG) main.cpp utils.cpp Q1.cpp Q2.cpp Q3.cpp Q4.cpp Q5.cpp -o $(OBJECTIVE)