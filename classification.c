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


#include "utils.h"

float euclideanDistance(int _i,int _sampleClassified){
	double distance = 0;

	for(int j = 0; j < dataSetNum.nrFeatures; j++){
				distance  =distance + pow(dataSetNum.matrix[_sampleClassified][j] - dataSetNum.matrix[_i][j],2);
			}

			distance = sqrt(distance);

			return (float)distance;


}


float * computeDistances(int _sampleClassified, int typeOfDataSet){
	float * distances = (float*)malloc(dataSetNum.nrSamples*sizeof(float));


	if (typeOfDataSet == NUMERICAL){

		for(int i = 0; i < dataSetNum.nrSamples; i++){
			if(i != _sampleClassified){

				distances[i] = euclideanDistance(i,_sampleClassified);

			}
			else{
				distances[i] = -1;
			}
		}
    }
   
   /* else if(typeOfDataSet == CATEGORIC){
    	for(int i = 0; i < dataSetNum.nrSamples; i++){
			if(i != _sampleClassified){

				distances[i] = euclideanDistance();

			}
			else{
				distances[i] = -1;
			}
		}

    }
    */

    return distances;


}

void writeOnFile(int k, int sampleClassified, float * distances, int* neighboors, int algorithm){

	FILE *f;

	if (algorithm == KNN)
		f = fopen("Results/KNN.txt","w");

	else if(algorithm == VPTree)
		f = fopen("Results/VPTree","w");

	fprintf(f, "%d nearest Neighboors of the sample nr.: %d \n", k,sampleClassified);

	for(int i=0; i < k; i++){
		fprintf(f,"%d. Sample nr: %d, with distance: %f \n", i+1,neighboors[i],distances[neighboors[i]]);
		fprintf(f,"feature values: \n");
		for(int j = 0; j < dataSetNum.nrFeatures; j++){
			fprintf(f,"   %f    ", dataSetNum.matrix[neighboors[i]][j]);
		}
		fprintf(f,"\n \n \n");
	}


	fclose(f);
}




void quicksort(float *number, int * aux, int first,int last){
   int i, j, pivot;
   float temp;
   int  temp1;

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








void linearSearchNeighboors(int k, int sampleClassified, float * distances, int *neighboors){


	int * visits = (int*)calloc(dataSetNum.nrSamples,sizeof(int));
	float min = 999999;
	int minIdx = 0;

	visits[sampleClassified] = -1;

	for(int j = 0; j< k; j++){
		min = 999999;
		for(int i = 0 ; i <dataSetNum.nrSamples; i++ ){
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

	for (int i = 0; i < k; i++){
		printf("%d-NN = %d \n",i,neighboors[i]);
	}

	writeOnFile(k,sampleClassified,distances, neighboors, KNN);
	

}


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}



void KnnClassification(int typeOfDataSet,int classification,int sampleClassified, int normalization, int k){

	float * distances;
	distances = (float*)malloc(dataSetNum.nrSamples*sizeof(float));

	int * neighboors = (int*)malloc(k*sizeof(int));

	int * idxSort = NULL;;

	
	if(classification == ONE_SAMPLE){
		distances = computeDistances(sampleClassified, typeOfDataSet);

		if(k < log2(dataSetNum.nrSamples)){
			printf("linear search \n \n");
			linearSearchNeighboors(k,sampleClassified,distances, neighboors);
		}
		else{
			printf("QUICKSORT \n\n");

			printf("before sorting \n");
			for(int j = 0; j < dataSetNum.nrSamples; j++){
				printf("distances[%d] = %f \n",j,distances[j]);
			}

			idxSort = (int*) malloc(dataSetNum.nrSamples*sizeof(int)); 

			for(int i =0; i < dataSetNum.nrSamples; i++)
				idxSort[i] = i;

			quicksort(distances, idxSort, 0, dataSetNum.nrSamples-1);

			printf("after sorting \n");

			for(int j = 0; j < dataSetNum.nrSamples; j++){
				printf("distances[%d] = %f and indexPosition -> %d \n",j,distances[j], idxSort[j]);
			}

			for(int i =1; i<= k; i++){
				neighboors[i-1] = idxSort[i];
				printf("%d\n", neighboors[i-1]);
			}
			
			writeOnFile(k,sampleClassified,distances, neighboors, KNN);		


		}

	}

	
}
