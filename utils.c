#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>

#include "utils.h"



dataSetNum_t dataSetNum;
dataSetCat_t dataSetCat;
int initialK;
int positiveClassified = 0;
int negativeClassified = 0;

unsigned long diffTime;

char testingSet[100];
char auxFile[100];




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

void readDataSetCategoric(FILE * fpDataSet){

     //allocate memory to store the dataSet in the main memory, and fill the matrix
    dataSetCat.matrix = (char***) malloc(dataSetCat.nrSamples*sizeof(char**));
    for(int i = 0; i < dataSetCat.nrSamples; i++){
        dataSetCat.matrix[i] = (char**)malloc((dataSetCat.nrFeatures+1)*sizeof(char*));

        for(int j = 0; j <= dataSetCat.nrFeatures; j++){
            dataSetCat.matrix[i][j] = (char*)malloc(MAX_SIZE*sizeof(char)); 
        }
        fscanf(fpDataSet,"%[^ ] %[^ ] %[^ ] %[^ ] %[^ ] %[^ ] %[^\n]\n", dataSetCat.matrix[i][0],dataSetCat.matrix[i][1],dataSetCat.matrix[i][2],dataSetCat.matrix[i][3],dataSetCat.matrix[i][4],dataSetCat.matrix[i][5],dataSetCat.matrix[i][6]);    


    }   
       

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

 void readDataSet(char fileName[], int _normalization, int typeOfDataSet){

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
    	dataSetNum.nrFeatures = sizeString(pal1);
    	//last one is the class classification!
    	dataSetNum.nrFeatures--;
    }

    //read the file in order to know the number of samples
    while (!feof (fpDataSet)) {
        if (fgets(pal, DIM_MAX, fpDataSet))
        	dataSetNum.nrSamples++;
    }




    //put the pointer of the file to the beginning of the 2nd line (1st sample)
    fseek(fpDataSet,strlen(pal1), SEEK_SET);

    if(typeOfDataSet == CATEGORIC){
        dataSetCat.nrFeatures = dataSetNum.nrFeatures;
        dataSetCat.nrSamples = dataSetNum.nrSamples;
        readDataSetCategoric(fpDataSet);
        fclose(fpDataSet);
        return;
    }

    if(!_normalization){
        //allocate memory to store the dataSet in the main memory, and fill the matrix
        dataSetNum.matrix = (float**) malloc((dataSetNum.nrSamples)*sizeof(float*));
        for(int i = 0; i < dataSetNum.nrSamples; i++){
        	dataSetNum.matrix[i] = (float*)malloc((dataSetNum.nrFeatures+1)*sizeof(float));

        	for(int j = 0; j <= dataSetNum.nrFeatures; j++){
        		if (!fscanf(fpDataSet, "%f", &dataSetNum.matrix[i][j])) 
               break;
        	}
        }
    }
    else{
       

        float ** aux = (float**)malloc((dataSetNum.nrFeatures)*sizeof(float*));
        for(int i= 0; i <= dataSetNum.nrFeatures; i++)
            aux[i] = (float*)malloc(2*sizeof(float));

        //allocate memory to store the dataSet in the main memory, and fill the matrix
        dataSetNum.matrix = (float**) malloc(dataSetNum.nrSamples*sizeof(float*));
        dataSetNum.matrix[0] = (float*)malloc((dataSetNum.nrFeatures+1)*sizeof(float));
        for(int j = 0; j < dataSetNum.nrFeatures; j++){
                fscanf(fpDataSet, "%f", &dataSetNum.matrix[0][j]);
                aux[j][0] = dataSetNum.matrix[0][j];
                aux[j][1] = dataSetNum.matrix[0][j];
            }
          //class classifier
         fscanf(fpDataSet, "%f", &dataSetNum.matrix[0][dataSetNum.nrFeatures]);

        for(int i = 1; i < dataSetNum.nrSamples; i++){
            dataSetNum.matrix[i] = (float*)malloc((dataSetNum.nrFeatures+1)*sizeof(float));

            for(int j = 0; j < dataSetNum.nrFeatures; j++){
                fscanf(fpDataSet, "%f", &dataSetNum.matrix[i][j]);
                if(dataSetNum.matrix[i][j] > aux[j][0])
                    aux[j][0] = dataSetNum.matrix[i][j];

                if(dataSetNum.matrix[i][j] < aux[j][1])
                    aux[j][1] = dataSetNum.matrix[i][j];
               
            }
            fscanf(fpDataSet, "%f", &dataSetNum.matrix[i][dataSetNum.nrFeatures]);
        }


        for(int i = 0; i < dataSetNum.nrSamples; i++){
            for( int j = 0; j < dataSetNum.nrFeatures; j++){
                dataSetNum.matrix[i][j] = (dataSetNum.matrix[i][j] - aux[j][1])/(aux[j][0]-aux[j][1]);

            }
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
            if(sscanf(argv[i], "%s",_fileName) != 1) {
            printf("Error decoding filename\n");
                exit(1);
            }
            flagFileName = 1;
        }
        else if(strcmp(argv[i], "-a") == 0) {
            i++;
            if(sscanf(argv[i], "%d", &auxAlg) != 1) {
                printf("Error decoding algorithm to be used \n");
                exit(1);
            }
            if(auxAlg == 0)
            	*_algorithm = KNN;
            else if(auxAlg == 1)
            	*_algorithm = KNN_PLUS;
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
    
            else if(auxClassif ==2)
                *_classification = LEAVE_ONE_OUT;
            else if(auxClassif ==3)
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
            if(*_classification == ADDITIONAL){
                i++;
                if(i < _argc){
                    if(sscanf(argv[i], "%s", testingSet) != 1) {
                        printf("Error decoding testing set \n");
                        exit(1);
                    }
                }
                else {
                    printf("you have to choose the file with testing set samples!! \n");
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



