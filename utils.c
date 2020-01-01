#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>

#include "utils.h"



dataSetNum_t dataSetNum;


/******************************************************************************
 * sizeString()
 *
 * Arguments: sentence - string
 * Return: nr of words that the string contains
 *
 * Description: function to count how many 'words' exists in the string 'sentence'
*              used in order to check how many features the dataSet has got.
 *
 *****************************************************************************/

int sizeString(const char *sentence)
{
    int count=0,i,len;
    char lastC;
    len=strlen(sentence);
    if(len > 0)
    {
        lastC = sentence[0];
    }
    for(i=0; i<=len; i++)
    {
        if((sentence[i]==' ' || sentence[i]=='\0') && lastC != ' ')
        {
            count++;
        }
        lastC = sentence[i];
    }
    return count;
}


/******************************************************************************
 * readDataSet()
 *
 * Arguments: name of the dataSet
 * Return: void
 *
 * Description: fill the structure of the dataSet - get the nr of features, samples, and create the matrix of the dataSet.
 *
 *****************************************************************************/

 void readDataSet(char fileName[]){

  	FILE * fpDataSet;
  	char pal[DIM_MAX];
  	
  	dataSetNum.nrFeatures = 0;
  	dataSetNum.nrSamples = 0;


  	fpDataSet = fopen(fileName, "r");

    if(fpDataSet == NULL){
      printf("Invalid name of dataSet text file\n");
      exit(0); 
    }

    char pal1[DIM_MAX];
    //read the first line of the file in order to know the number of features
     if (fgets(pal1, DIM_MAX, fpDataSet)){
    	printf("a palavra é %s \n",pal1);
    	dataSetNum.nrFeatures = sizeString(pal1);
    	printf("nr of features is %d \n",dataSetNum.nrFeatures);
    }

    //read the file in order to know the number of samples
    while (!feof (fpDataSet)) {
        if (fgets(pal, DIM_MAX, fpDataSet))
        	dataSetNum.nrSamples++;
    }
    printf("nr of samples is %d \n",dataSetNum.nrSamples);




    //put the pointer of the file to the beginning of the 2nd line (1st sample)
    fseek(fpDataSet,strlen(pal1)-1, SEEK_SET);

    //allocate memory to store the dataSet in the main memory, and fill the matrix
    dataSetNum.matrix = (float**) malloc(dataSetNum.nrSamples*sizeof(float*));
    for(int i = 0; i < dataSetNum.nrSamples; i++){
    	dataSetNum.matrix[i] = (float*)malloc(dataSetNum.nrFeatures*sizeof(float));

    	for(int j = 0; j < dataSetNum.nrFeatures; j++){
    		if (!fscanf(fpDataSet, "%f", &dataSetNum.matrix[i][j])) 
           break;
    	}
    }



    //close the file
    fclose(fpDataSet);

  }

  


  /******************************************************************************
 * readInputArguments()
 *
 * Arguments: sentence - string
 * Return: nr of words that the string contains
 *
 * Description: function to count how many 'words' exists in the string 'sentence'
*              used in order to check how many features the dataSet has got.
 *
 *****************************************************************************/

  int readInputArguments(int _argc, const char* argv[], char _fileName[], int * _algorithm, int * _normalization,int * _typeOfDataSet, int *_classification, int *_sampleClassified, int * _k)
  {
  	int auxAlg = -1 ;
  	int auxTypeDS = -1;
  	int auxClassif = -1;
  	int flagFileName = -1;


  	if(_argc < 2) {
 		printf("you should put something like...");
        exit(1);
    } 

    for (int i = 1; i < _argc; ++i) {

    	if(strcmp(argv[i], "-k") == 0) {
            i++;
            if(sscanf(argv[i], "%d", _k) != 1) {
                printf("Error decoding number of neighboors\n");
                exit(1);
            }
        }


        else if(strcmp(argv[i], "-f") == 0) {
            i++;
            printf("%s \n",argv[i]);
            if(sscanf(argv[i], "%s",_fileName) != 1) {
            printf("Error decoding filename\n");
                exit(1);
            }
            flagFileName = 1;
        }
        else if(strcmp(argv[i], "-a") == 0) {
            i++;
            printf("ola \n");
            if(sscanf(argv[i], "%d", &auxAlg) != 1) {
                printf("Error decoding algorithm to be used \n");
                exit(1);
            }
            if(auxAlg == 0)
            	*_algorithm = KNN;
            else if(auxAlg == 1)
            	*_algorithm = VPTree;
            else
            	auxAlg = -1;

        }

        else if(strcmp(argv[i], "-t") == 0) {
            i++;
            if(sscanf(argv[i], "%d", &auxTypeDS) != 1) {
                printf("Error decoding type of dataSet to be used \n");
                exit(1);
            }
            if(auxTypeDS == 0)
            	*_typeOfDataSet = NUMERICAL;
            else if(auxTypeDS == 1)
            	*_typeOfDataSet = CATEGORIC;
            

        }

        else if(strcmp(argv[i], "-n") == 0)
        	*_normalization = 1;

        else if(strcmp(argv[i], "-c") == 0){
        	i++;
            if(sscanf(argv[i], "%d", &auxClassif) != 1) {
                printf("Error decoding type of classification intended by user \n");
                exit(1);
            }

            if(auxClassif == 0)
            	*_classification = ONE_SAMPLE;
            else if(auxClassif == 1)
            	*_classification = RANDOM;
            else if(auxClassif == 2)
            	*_classification = ADDITIONAL;

            if(*_classification == ONE_SAMPLE){
            	i++;
                if(i < _argc){
                	if(sscanf(argv[i], "%d", _sampleClassified) != 1) {
                        printf("Error decoding type of classification intended by user \n");
                        exit(1);
                    }
                }
                else {
                    printf("you have to choose the sample!! \n");
                    exit(1);
                }
            }



        }

   }

   //mandatory parameters are the algorithm and one textFile.
   if(auxAlg == -1 || flagFileName == -1)
   		return 0;

    return 1;


  }



