#ifndef UTILS_H_INCLUDE
#define UTILS_H_INCLUDE

// Library for special types of Int
#include <stdint.h>

#define DIM_MAX 6000
#define MAX_SIZE 25

//type of algorithm
#define KNN 0
#define VPTree 1

//type of dataSet
#define NUMERICAL 0
#define CATEGORIC 1

//type of sample to be classified
#define ONE_SAMPLE 0
#define RANDOM 1
#define ADDITIONAL 2



typedef struct _dataSetNum {
    int nrFeatures;		
	int nrSamples;	 
	float ** matrix;
} dataSetNum_t;


typedef struct _dataSetCat {
    int nrFeatures;		
	int nrSamples;	 
	char *** matrix;
} dataSetCat_t;




//variable that store the structure of the numeric dataSet
extern dataSetNum_t dataSetNum;

extern dataSetCat_t dataSetCat;


float euclideanDistance(int _i,int _sampleClassified);

float gowerDistance(int i,int _sampleClassified);

int readInputArguments(int _argc, const char* argv[], char _fileName[], int * _algorithm, int * _normalization,int * _typeOfDataSet, int *_classification, int *_sampleClassified, int * _k);

void readDataSet(char fileName[], int _normalization,int typeOfDataSet);

#endif