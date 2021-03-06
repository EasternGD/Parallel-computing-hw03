#pragma once

#include <string>
using namespace std;
// This is the general data struct that stores all needed data from instances or questions
// You need to define what you need in pass around in this struct
struct myDataFormat
{
    //for all
    double *vector;
    size_t column = 0;
    size_t row = 0;
    //for data
    string *remain;
    //for decisions
    double *distance;
    string *result;
    size_t resultNum = 0;
};

// This function read the data stored in the specified file in CSV format
void readCSV(myDataFormat &output, const char *filename, size_t noAttributes, const std::string &decisions = "");

// This function saves the data stored in the output to the specified file with filename outputFilename
void saveCSV(const myDataFormat &output, const char *outputFilename);

// This function calculates the distance matrix (stored in the decision data struct)
void calculateDistanceMatrix(const myDataFormat &instances, myDataFormat &questions, size_t distanceMeasureToUse);

// This function does the kNN algorithm with specified constant k.  Results are stored in questions data struct.
void doKNN(const size_t k, const myDataFormat &instances, myDataFormat &questions, const std::string &decisionString);

// This function frees all memory allocation (most likely pointer variables) in your struct
void freeAllocation(myDataFormat &);
