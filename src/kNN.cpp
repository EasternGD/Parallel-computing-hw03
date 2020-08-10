#include "../inc/kNN.h"
#include "../inc/distance.h"
#include <omp.h>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

void readCSV(myDataFormat &output, const char *filename, size_t noAttributes, const string &decisions)
{
    cout << "\nDO MODIFY readCSV " << __LINE__ << "@" << __FILE__;
    ifstream inp(filename);
    if (!inp)
    {
        cerr << "\nError opening file: " << filename;
    }

    // let's count # lines first.
    size_t noLines = 0;
    char buf[1024];
    while (inp.good())
    {
        inp.getline(buf, 1024);
        if (inp.gcount() > 0)
            noLines++;
    }

    // now you should allocate memory for storing data
    output.vector = new double[noLines * noAttributes];
    output.column = noAttributes;
    output.row = noLines;

    if (decisions.size() > 0)
    {
        output.remain = new string[noLines * decisions.size()];
    }
    // re-read the file and this time read the actual data into allocated memory
    inp.clear();
    inp.seekg(0, inp.beg);

    for (size_t i = 0; i < noLines; ++i)
    {
        inp.getline(buf, 1024);
        size_t head = 0;
        string tmp(buf);
        // now we are reading attributes one by one that are separated by comma ','
        // cout << endl;
        for (size_t j = 0; j < noAttributes; ++j)
        {
            auto tail = tmp.find(',', head);
            auto attribute = atof(tmp.c_str() + head);
            // now I read a attribute in real number, what should you do with it?
            output.vector[i * noAttributes + j] = attribute;
            head = tail + 1;
            //  cout << output.vector[i * noAttributes + j] << "\t";
        }
        // now we are reading decision variables one by one that are separated by comma ','
        for (size_t j = 0; j < decisions.size(); ++j)
        {
            auto tail = tmp.find(',', head);
            auto variable = tmp.substr(head, tail - head);

            // now I read a decision variable in string, what should you do with it?
            output.remain[i * decisions.size() + j] = variable;
            head = tail + 1;
            // cout << output.remain[i * decisions.size() + j] << "\t";
        }
    }

    inp.close();
}

void saveCSV(const myDataFormat &output, const char *filename)
{
    cout << "\nDO IMPLEMENT saveCSV " << __LINE__ << "@" << __FILE__;
    ofstream fileOutput(filename, ios::out);
    if (!fileOutput)
    {
        cerr << "\nError opening file: " << filename;
    }
    else
    {
        for (size_t i = 0; i < output.row; i++)
        {
            for (size_t j = 0; j < (output.resultNum + output.column); j++)
            {

                if (j < output.column)
                {
                    fileOutput << output.vector[i * output.column + j] << ", ";
                }
                else
                {
                    fileOutput << output.result[i * output.resultNum + j - output.column] << ", ";
                }
            }
            fileOutput << endl;
        }
        fileOutput.close();
    }

    // ifstream fileInput(filename, ios::in);
    // if (!fileInput)
    // {
    //     cerr << "\nError opening file: " << filename;
    // }
    // else
    // {
    //     string line;
    //     while (fileInput.good())
    //     {
    //         getline(fileInput, line);
    //         cout << "\n"
    //              << line << endl;
    //     }
    // }
    // fileInput.close();
}

void calculateDistanceMatrix(const myDataFormat &data, myDataFormat &decisions, size_t distanceMeasureToUse)
{
    // double t1;
    // double sum = 0;
    // double count = 0;
    // t1 = omp_get_wtime();
    // cout << "\nDO IMPLEMENT calculateDistanceMatrix " << __LINE__ << "@" << __FILE__;

    decisions.distance = new double[decisions.row * data.row];
    // cout << endl;
    switch (distanceMeasureToUse)
    {
    case 0:
        // do
        // {
        //     t1 = omp_get_wtime();
        // #pragma omp parallel for
        for (size_t i = 0; i < decisions.row * data.row; ++i)
        {

            decisions.distance[i] =
                euclidean((decisions.vector + (i / data.row * decisions.column)),
                          (data.vector + (i * decisions.column) % (data.row * data.column)),
                          decisions.column);
        }
        // t1 = omp_get_wtime() - t1;
        // sum += t1;
        // count++;
        // } while (sum < 0.2);
        // cout << sum / count << " s" << endl;
        break;
    case 1:
        // do
        // {
        // t1 = omp_get_wtime();
        // #pragma omp parallel for
        for (size_t i = 0; i < decisions.row * data.row; ++i)
        {

            decisions.distance[i] =
                manhattan((decisions.vector + (i / data.row * decisions.column)),
                          (data.vector + (i * decisions.column) % (data.row * data.column)),
                          decisions.column);
        }
        // t1 = omp_get_wtime() - t1;
        // sum += t1;
        // count++;
        // } while (sum < 0.2);
        // cout << sum / count << " s" << endl;
        break;

    case 2:

        // do
        // {
        // t1 = omp_get_wtime();
        // #pragma omp parallel for
        for (size_t i = 0; i < decisions.row * data.row; ++i)
        {

            decisions.distance[i] =
                chebyshev((decisions.vector + (i / data.row * decisions.column)),
                          (data.vector + (i * decisions.column) % (data.row * data.column)),
                          decisions.column);
        }
        // t1 = omp_get_wtime() - t1;
        // sum += t1;
        // count++;
        // } while (sum < 0.2);
        // cout << sum / count << " s" << endl;
        break;
    case 3:

        // do
        // {
        // t1 = omp_get_wtime();
        // #pragma omp parallel for
        for (size_t i = 0; i < decisions.row * data.row; ++i)
        {

            decisions.distance[i] =
                minkowski((decisions.vector + (i / data.row * decisions.column)),
                          (data.vector + (i * decisions.column) % (data.row * data.column)),
                          decisions.column);
        }
        // t1 = omp_get_wtime() - t1;
        // sum += t1;
        // count++;
        // } while (sum < 0.2);
        // cout << sum / count << " s" << endl;
        break;

    case 4:

        // do
        // {
        // t1 = omp_get_wtime();
        // #pragma omp parallel for
        for (size_t i = 0; i < decisions.row * data.row; ++i)
        {

            decisions.distance[i] =
                cosineSimilarity((decisions.vector + (i / data.row * decisions.column)),
                                 (data.vector + (i * decisions.column) % (data.row * data.column)),
                                 decisions.column);
        }
        // t1 = omp_get_wtime() - t1;
        // sum += t1;
        // count++;
        // } while (sum < 0.2);
        // cout << sum / count << " s" << endl;
        // break;0v
    }
    // t1 = omp_get_wtime() - t1;
    // cout << t1 << " s" << endl;
}

void doKNN(const size_t k, const myDataFormat &instances, myDataFormat &decisions, const string &decisionString)
{
    cout << "\nDO IMPLEMENT doKNN " << __LINE__ << "@" << __FILE__;

    decisions.resultNum = decisionString.size();
    decisions.result = new string[decisions.resultNum * decisions.row];
    int *index = new int[k * decisions.row];

    //for Q1
    //Find k smallest distances and their corresponding instances.

    for (size_t e = 0; e < decisions.row; e++)
    {
        for (size_t i = 0; i < k; i++)
        {
            index[e * k + i] = e * instances.row;
            for (size_t j = 0; j < instances.row; j++)
            {
                if (decisions.distance[e * instances.row + j] <= decisions.distance[index[e * k + i]])
                {
                    index[e * k + i] = e * instances.row + j;
                }
            }
            decisions.distance[index[e * k + i]] = INT64_MAX;
            // cout << index[e * k + i] << " ";
        }
        // cout << endl;

        size_t maxCount = 0;
        double sum = 0;
        for (size_t i = 0; i < k; i++)
        {
            size_t count = 0;

            for (size_t j = 0; j < decisionString.size(); j++)
            {
                // cout << instances.remain[(index[e * k + i] % instances.row) * decisionString.size() + j];

                //do classification
                if (decisionString[j] == 'C')
                {
                    for (size_t x = 0; x < k; x++)
                    {
                        if (instances.remain[(index[e * k + i] % instances.row) * decisionString.size() + j] == instances.remain[(index[e * k + i] % instances.row) * decisionString.size() + j])
                        {
                            count++;
                        }

                        if (count > maxCount)
                        {
                            maxCount = count;
                        }

                        if (maxCount >= k / 2)
                        {
                            decisions.result[e * decisions.resultNum + j] = instances.remain[(index[e * k + i] % instances.row) * decisionString.size() + j];
                        }
                    }
                }
                //do regression
                if (decisionString[j] == 'R')
                {
                    sum += stod(instances.remain[(index[e * k + i] % instances.row) * decisionString.size() + j]) / k;
                    decisions.result[e * decisions.resultNum + j] = to_string(sum);
                }
            }
            // cout << endl;
        }
    }
    // cout << endl;
    // for (size_t i = 0; i < decisionString.size() * decisions.row; i++)
    // {
    //     cout << decisions.result[i] << "\t";
    //     // cout << endl;
    // }
    delete[] index;
}

void freeAllocation(myDataFormat &data)
{
    cout << "\nDO IMPLEMENT freeAllocation " << __LINE__ << "@" << __FILE__;
    //for all
    delete[] data.vector;

    if (data.resultNum > 0)
    {
        delete[] data.distance;
        delete[] data.result;
    }
    else
    {
        delete[] data.remain;
    }
}
