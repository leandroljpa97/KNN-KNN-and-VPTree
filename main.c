/**********************************************************************
Data Mining Project
Authors:  Leandro Almeida, K-5600


File name: main.c
COMMENTS
**********************************************************************/

#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


#include "utils.h"
#include "classification.h"

#include <math.h>


int main(int argc, char const *argv[]) {
	//user has to inform in the input if he wants KNN or KNN+.
	int algorithm = -1;
	//default is without normalization
	int normalization = 0;
	//default is NUMERICAL dataSet
	int typeOfDataSet = NUMERICAL;

	//default classification type is 1/3 of the dataSet.
	int classification = RANDOM;

	int sampleClassified;

	int k = -1;

    char fileName[100] = "";



    int readSignal = readInputArguments(argc, argv,fileName, &algorithm,&normalization,&typeOfDataSet, &classification, &sampleClassified, &k);

    strcpy(auxFile,fileName);


    if(k==-1)
        k = log2(dataSetNum.nrSamples);

    initialK = k;


    if(!readSignal){
    	printf("error in input parameters \n");
    	printf("PUT INSTRUCTIONS \n");
    }

    printf("algorithm is: %d \n", algorithm);
    printf("normalization is: %d \n", normalization);
    printf("typeOfDataSet is: %d \n", typeOfDataSet);
    printf("classification is: %d \n", classification);
    printf("name of the file is %s \n",fileName);


    readDataSet(fileName,normalization,typeOfDataSet);


    positiveClassified = 0;
    negativeClassified = 0;

    diffTime = 0;

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    KnnClassification(typeOfDataSet,classification,sampleClassified,normalization,&k,algorithm);

    gettimeofday(&stop, NULL);
    printf("overall time took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
    printf(" time without write on file took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec - diffTime);



    float accuracy ;

    printf("number of positiveClassified = %d \n",positiveClassified );
        printf("number negClassified = %d \n",negativeClassified );


    accuracy = positiveClassified/((float)positiveClassified+negativeClassified);

    printf("the accuracy is %f \n",accuracy);


	return 0;
}
