/**********************************************************************
Data Mining Project
Authors:  Leandro Almeida, K-5600
          Arnim Kumar


File name: main.c
COMMENTS
**********************************************************************/

#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "classification.h"


int main(int argc, char const *argv[]) {
	//user has to inform in the input if he wants KNN or VP-Tree.
	int algorithm = -1;
	//default is without normalization
	int normalization = 0;
	//default is NUMERICAL dataSet
	int typeOfDataSet = NUMERICAL;

	//default classification type is 1/3 of the dataSet.
	int classification = RANDOM;

	int sampleClassified;

	int k = -1;

	char fileName[50] ="";

    int readSignal = readInputArguments(argc, argv,fileName, &algorithm,&normalization,&typeOfDataSet, &classification, &sampleClassified, &k);

    if(k==-1)
        k = 5;



    if(!readSignal){
    	printf("error in input parameters \n");
    	printf("PUT INSTRUCTIONS \n");
    }

    printf("algorithm is: %d \n", algorithm);
    printf("normalization is: %d \n", normalization);
    printf("typeOfDataSet is: %d \n", typeOfDataSet);
    printf("classification is: %d \n", classification);
    printf("name of the file is %s \n",fileName);

    if(algorithm == KNN){
        printf("KNN \n");
    	readDataSet(fileName,normalization,typeOfDataSet);
    	KnnClassification(typeOfDataSet,classification,sampleClassified,normalization,k);
    	
    }

     



    	

	return 0;
}