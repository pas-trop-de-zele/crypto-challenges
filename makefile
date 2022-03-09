CC=clang++
FLAG=-g -std=c++11
OBJECTIVE=main

all : main.o utils.o AES128.o KeySchedule.o Q1.o Q2.o Q3.o Q4.o Q5.o Q6.o Q7.o 
	$(CC) $(FLAG) main.cpp utils.cpp AES128.cpp KeySchedule.cpp Q1.cpp Q2.cpp Q3.cpp Q4.cpp Q5.cpp Q6.cpp Q7.cpp -o $(OBJECTIVE)

clean:
	rm *.o