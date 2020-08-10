all: kNN.exe try

CC=g++
CFLAGS=-Wall -O2 
MCFLAGS=$(CFLAGS) -fopenmp
OBJS=kNN.o distance.o

%.o: src/%.cpp inc/%.h
	$(CC) $(MCFLAGS) -c $< -o $@

kNN.exe: main.cpp $(OBJS)
	$(CC) $(MCFLAGS)  $< -o $@ $(OBJS)

test: kNN.exe
	valgrind ./kNN.exe data/01_kid.csv data/01_questions.csv 3 3 2 0 CR 
	valgrind ./kNN.exe data/01_kid.csv data/01_questions.csv 3 3 2 1 CR 
	valgrind ./kNN.exe data/01_kid.csv data/01_questions.csv 3 3 2 2 CR 
	valgrind ./kNN.exe data/01_kid.csv data/01_questions.csv 3 3 2 3 CR 1.5
	valgrind ./kNN.exe data/01_kid.csv data/01_questions.csv 3 3 2 4 CR 
	valgrind ./kNN.exe data/02_iris.csv data/02_iris_questions.csv 5 4 1 0 C 
	valgrind ./kNN.exe data/02_iris.csv data/02_iris_questions.csv 5 4 1 1 C 
	valgrind ./kNN.exe data/02_iris.csv data/02_iris_questions.csv 5 4 1 2 C 
	valgrind ./kNN.exe data/02_iris.csv data/02_iris_questions.csv 5 4 1 3 C 1.75
	valgrind ./kNN.exe data/02_iris.csv data/02_iris_questions.csv 5 4 1 4 C 

try:
	./kNN.exe data/01_kid.csv data/01_questions.csv 3 3 2 0 CR 

clean:
	rm *.exe *.o
