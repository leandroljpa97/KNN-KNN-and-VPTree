#ifndef UTILS_H_INCLUDE
#define UTILS_H_INCLUDE

// Library for special types of Int
#include <stdint.h>

#define DIM_MAX 6000
#define MAX_SIZE 50
#define MAX_KNN 1000

//type of algorithm
#define KNN_PLUS 1
#define KNN 0


//type of dataSet
#define NUMERICAL 0
#define CATEGORIC 1

//type of sample to be classified
#define ONE_SAMPLE 0
#define RANDOM 1
#define LEAVE_ONE_OUT 2
#define ADDITIONAL 3



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

extern int initialK;

extern int positiveClassified;
extern int negativeClassified;
extern 	char testingSet[100];
extern unsigned long diffTime;

extern char auxFile[100];



int readInputArguments(int _argc, const char* argv[], char _fileName[], int * _algorithm, int * _normalization,int * _typeOfDataSet, int *_classification, int *_sampleClassified, int * _k);

void readDataSet(char fileName[], int _normalization,int typeOfDataSet);

#endif