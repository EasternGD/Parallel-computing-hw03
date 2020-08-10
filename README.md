# Parallel-computing-hw03
In this assignment, you are going to implement a machine learning algorithm called kNN – k nearest neighbors.According to Wikipedia, “The k-NN algorithm is among the simplest of all machine learning algorithms.” [1] kNN canbe used to do classification (e.g. a boy with height of 140cm and weight of 27kg, is he a 2th, 3th, 4th, 5th, or 6th grader?)
and regression (e.g. how much allowance a girl is likely to have with height of 150cm and weight of 42kg?).

In this assignment, you are going to write a somewhat general-purpose kNN program that allows you to specify 

1) an instance dataset 
2) a dataset in question
3) k
4) number of feature attributes
5) number of decision attributes
6) distance measure to use and 
7) classification or regression for each decision variable. 

All the information are given using command line arguments. For example: 

```sh
./kNN.exe kid.csv question.csv 3 3 2 1 CR 
```

kid.csv
```sh
0, 140, 27, 3th, 200
0, 142, 33, 4th, 150
1, 142, 25, 3th, 0
...
```
question.csv 
```sh
0, 137, 22
1, 134, 55 
```
## Dependencies
* Ubuntu
* g++
* Valgrind   -- Valgrind is a tool for detecting memory leaks.

## Setup
```sh
make         -- Produce executable file
make test    -- Test Program and predict the question dataset
```

## Example Result
Take file 02_iris_questions.csv as an example
The output should be like...
```
./kNN.exe data/02_iris.csv data/02_iris_questions.csv 5 4 1 4 C

==875== HEAP SUMMARY:
==875==     in use at exit: 0 bytes in 0 blocks
==875==   total heap usage: 164 allocs, 164 frees, 120,946 bytes allocated
==875==
==875== All heap blocks were freed -- no leaks are possible
==875==
==875== For lists of detected and suppressed errors, rerun with: -s
==875== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

5.1, 3.5, 1.4, 0.2, Iris-setosa, 
5, 3.3, 1.4, 0.2, Iris-setosa, 
7, 3.2, 4.7, 1.4, Iris-versicolor, 
5.7, 2.8, 4.1, 1.3, Iris-versicolor, 
6.3, 3.3, 6, 2.5, Iris-virginica, 
5.9, 3, 5.1, 1.8, Iris-virginica, 

```
## Folder Structure
* Data is saved into the `data` folder.
* Header files is saved into the `inc` folder.
* Code is saved into the `src` folder.

## Contact

Abbey, Chen - encoref9241@gmail.com

Project Link: [Parallel-computing-hw03](https://github.com/EasternGD/Parallel-computing-hw03.git)
