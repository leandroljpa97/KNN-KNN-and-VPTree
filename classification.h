#ifndef CLASSIFICATION_H_INCLUDE
#define CLASSIFICATION_H_INCLUDE

// Library for special types of Int
#include <stdint.h>

float euclideanDistance(int i, int _sampleClassified);
float * computeDistances(int _sampleClassified, int typeOfDataSet);
void linearSearchNeighboors(int *k, int sampleClassified, float * distances,int *neighboors,int nrSamples, int typeOfDataSet, int algorithm);
void quicksort(float *number, int * aux, int first,int last);
void writeOneOnFile(int k, int sampleClassified, float * distances, int* neighboors, int algorithm,int typeOfDataSet,int class);
void KnnClassification(int typeOfDataSet,int classification,int sampleClassified, int normalization, int * k, int algorithm);
void computeNeighboors(int sampleClassified, int typeOfDataSet, int * idxSort,int *neighboors, float* _distances, int * k, int algorithm);

#endif