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
#include <math.h>
#include <time.h>



#include "utils.h"

int flagQuick = 0;

float euclideanDistance(int _i,int _sampleClassified){
	double distance = 0;

	for(int j = 0; j < dataSetNum.nrFeatures; j++){
				distance  =distance + pow(dataSetNum.matrix[_sampleClassified][j] - dataSetNum.matrix[_i][j],2);
			}

			distance = sqrt(distance);

			return (float)distance;


}
float gowerDistance(int i,int _sampleClassified){
	float distance = 0;

 	int x1 = atoi(dataSetCat.matrix[i][0]);
 	int x2 = atoi(dataSetCat.matrix[_sampleClassified][0]);

	distance =  (float)abs(x1 - x2);
	printf("distance : %f \n", distance);
	
	distance = 1-(distance/100);
	for(int j = 1; j < dataSetNum.nrFeatures; j++){
		if(!strcmp(dataSetCat.matrix[i][j],dataSetCat.matrix[_sampleClassified][j]))
			distance = distance + 1;
	}
		printf("distance after: %f\n",distance);
	distance = distance/dataSetCat.nrFeatures;
			printf("distance last: %f\n",distance);

	return (float)distance;


}


float * computeDistances(int _sampleClassified, int typeOfDataSet){
		
	float * distances;

	if (typeOfDataSet == NUMERICAL){
		distances = (float*)malloc(dataSetNum.nrSamples*sizeof(float));

		for(int i = 0; i < dataSetNum.nrSamples; i++){
			if(i != _sampleClassified){

				distances[i] = euclideanDistance(i,_sampleClassified);

			}
			else{
				distances[i] = -1;
			}
		}
    }
   
    else if(typeOfDataSet == CATEGORIC){
    	 distances = (float*)malloc(dataSetCat.nrSamples*sizeof(float));

    	for(int i = 0; i < dataSetNum.nrSamples; i++){
			if(i != _sampleClassified){

				distances[i] = gowerDistance(i,_sampleClassified);

			}
			else{
				distances[i] = -1;
			}
		}

    }
    

    return distances;


}

void writeIt(FILE * f, int k, int sampleClassified, float * distances, int* neighboors,int typeOfDataSet){
	fprintf(f, "%d-nearest Neighboors of the sample nr.: %d \n", k,sampleClassified);

	if(typeOfDataSet == NUMERICAL){
		for(int i=0; i < k; i++){
			if(flagQuick)
				fprintf(f,"%d. Sample nr: %d, with distance: %f \n", i+1,neighboors[i],distances[i+1]);
			else
				fprintf(f,"%d. Sample nr: %d, with distance: %f \n", i+1,neighboors[i],distances[neighboors[i]]);
			fprintf(f,"feature values: \n");
			for(int j = 0; j < dataSetNum.nrFeatures; j++){
				fprintf(f,"   %f    ", dataSetNum.matrix[neighboors[i]][j]);
			}
			fprintf(f,"\n \n \n ");
		}
	}
	else if (typeOfDataSet == CATEGORIC){
		for(int i=0; i < k; i++){
			if(flagQuick)
				fprintf(f,"%d. Sample nr: %d, with distance: %f \n", i+1,neighboors[i],distances[dataSetCat.nrSamples-i-1]);
			else
				fprintf(f,"%d. Sample nr: %d, with distance: %f \n", i+1,neighboors[i],distances[neighboors[i]]);
			fprintf(f,"feature values: \n");
			for(int j = 0; j < dataSetCat.nrFeatures; j++){
				fprintf(f,"   %s    ", dataSetCat.matrix[neighboors[i]][j]);
			}
			fprintf(f,"\n \n \n ");
		}
	}
	fprintf(f, "\n \n\n" );
}

void writeOneOnFile(int k, int sampleClassified, float * distances, int* neighboors, int algorithm,int typeOfDataSet){

	FILE *f = NULL;

	if (algorithm == KNN)
		f = fopen("Results/KNN.txt","w");

	else if(algorithm == VPTree)
		f = fopen("Results/VPTree","w");

	writeIt(f,k,sampleClassified,distances, neighboors,typeOfDataSet);


	fclose(f);
}

void quicksort(float *number, int * aux, int first,int last){
   int i, j, pivot;
   float temp;
   int  temp1;
   flagQuick = 1;

   if(first<last){
      pivot=first;
      i=first;
      j=last;

      while(i<j){
         while(number[i]<=number[pivot]&&i<last)
            i++;
         while(number[j]>number[pivot])
            j--;
         if(i<j){
            temp=number[i];
            number[i]=number[j];
            number[j]=temp;

            temp1=aux[i];
            aux[i]=aux[j];
            aux[j]=temp1;
         }
      }

      temp=number[pivot];
      number[pivot]=number[j];
      number[j]=temp;


      temp1=aux[pivot];
      aux[pivot]=aux[j];
      aux[j]=temp1;

      quicksort(number,aux, first,j-1);
      quicksort(number,aux, j+1,last);

   }
}








void linearSearchNeighboors(int k, int sampleClassified, float * distances, int *neighboors, int nrSamples, int typeOfDataSet){


	int * visits = (int*)calloc(nrSamples,sizeof(int));
	float min = 999999;
	int minIdx = 0;

	float max = -0.5;
	int maxIdx = 0;

	visits[sampleClassified] = -1;


	if(typeOfDataSet == NUMERICAL){    
		for(int j = 0; j< k; j++){
			min = 999999;
			for(int i = 0 ; i <nrSamples; i++ ){
				if (visits[i] != -1){
					if(distances[i] < min){
						min = distances[i];
						minIdx = i;
					}

				}
			}
			neighboors[j] = minIdx;
		    visits[minIdx] = -1;

		}
	}
	else if(typeOfDataSet == CATEGORIC){
		for(int j = 0; j< k; j++){
				max = -0.5;
				for(int i = 0 ; i <nrSamples; i++ ){
					if (visits[i] != -1){
						if(distances[i] > max){
							max = distances[i];
							maxIdx = i;
						}

					}
				}
				neighboors[j] = maxIdx;
			    visits[maxIdx] = -1;

		}

	}

	for (int i = 0; i < k; i++){
		printf("%d-NN = %d \n",i,neighboors[i]);
	}




	

}


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}




void computeNeighboors(int sampleClassified, int typeOfDataSet, int * idxSort,int *neighboors, float* _distances, int k){


	int nrSamples = 0;
	int nrFeatures = 0;
	if(typeOfDataSet == NUMERICAL){
		nrSamples = dataSetNum.nrSamples;
		nrFeatures = dataSetNum.nrFeatures;
	}
	else if(typeOfDataSet == CATEGORIC){
		nrSamples = dataSetCat.nrSamples;
		nrFeatures = dataSetCat.nrFeatures;
	}


		if(k < log2(nrSamples)){
			printf("linear search \n \n");
			linearSearchNeighboors(k,sampleClassified,_distances, neighboors,nrSamples, typeOfDataSet);
		}
		else{
			printf("QUICKSORT \n\n");

			printf("before sorting \n");
			for(int j = 0; j < nrSamples; j++){
				printf("distances[%d] = %f \n",j,_distances[j]);
			}

			idxSort = (int*) malloc(nrSamples*sizeof(int)); 

			for(int i =0; i < nrSamples; i++)
				idxSort[i] = i;

			quicksort(_distances, idxSort, 0, nrSamples-1);

			printf("after sorting \n");

			for(int j = 0; j < nrSamples; j++){
				printf("distances[%d] = %f and indexPosition -> %d \n",j,_distances[j], idxSort[j]);
			}

			if(typeOfDataSet == NUMERICAL){
				for(int i =1; i<= k; i++){
					neighboors[i-1] = idxSort[i];
					printf("%d\n", neighboors[i-1]);
				}
			}
			else if(typeOfDataSet == CATEGORIC){
				for(int i =0; i< k; i++){
						neighboors[i] = idxSort[dataSetCat.nrSamples-i-1];
					}	
			}
			


		}

			printf("caralhoo \n");
		for(int i =0; i <dataSetCat.nrSamples; i++)
			printf("%f\n",_distances[i]);

		for(int i =0; i <k; i++)
			printf("%d\n",neighboors[i]);


}

void computeRandom(int typeOfDataSet, int * idxSort,int *neighboors, float* distances, int k, int algorithm){
	FILE *f = NULL;

	if (algorithm == KNN)
		f = fopen("Results/KNN.txt","w");

	else if(algorithm == VPTree)
		f = fopen("Results/VPTree","w");


	srand(time(NULL));   // Initialization, should only be called once.
    

    for(int i = 0; i < dataSetNum.nrSamples/3; i++){
	    int sampleClassified = rand()%(dataSetNum.nrSamples-1); 
	    distances = computeDistances(sampleClassified, typeOfDataSet);
	    computeNeighboors(sampleClassified, typeOfDataSet,idxSort,neighboors, distances,k);
	    writeIt(f,k,sampleClassified,distances, neighboors,typeOfDataSet);
    } 

} 







void KnnClassification(int typeOfDataSet,int classification,int sampleClassified, int normalization, int k){

	float * distances;
	
	if( typeOfDataSet == NUMERICAL){
		distances = (float*)malloc(dataSetNum.nrSamples*sizeof(float));
	}
	else if( typeOfDataSet == CATEGORIC){
		distances = (float*)malloc(dataSetCat.nrSamples*sizeof(float));	
	}

	int * neighboors = (int*)malloc(k*sizeof(int));

	int * idxSort = NULL;;

	
	if(classification == ONE_SAMPLE){
		printf("txiiiga \n");
		distances = computeDistances(sampleClassified, typeOfDataSet);
		printf("xxxxxxxxxxx \n");
		for(int i =0; i <dataSetNum.nrSamples; i++)
			printf("%f\n",distances[i]);

		computeNeighboors(sampleClassified, typeOfDataSet,idxSort,neighboors, distances,k);

			printf("putaaaaaaass \n");
		for(int i =0; i <dataSetNum.nrSamples; i++)
			printf("%f\n",distances[i]);
		for(int i =0; i <k; i++)
			printf("%d\n",neighboors[i]);
		writeOneOnFile(k,sampleClassified,distances, neighboors, KNN, typeOfDataSet);		


	}
	else if(classification == RANDOM){
		computeRandom(typeOfDataSet,idxSort,neighboors, distances,k,KNN);
	}

	
}
