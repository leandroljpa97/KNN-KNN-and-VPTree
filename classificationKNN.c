#include <stdio.h>
#include <stdlib.h>
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
#include <sys/time.h>




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


float numericalAtrib(int x1, int x2, int range){

	float distance;
	distance =  (float)abs(x1 - x2);

	distance = 1- (distance/range);

	return distance;

}

int nominalAtrib(char * a1, char *a2){

	if(!strcmp(a1,a2))
		return 1;

	return 0;

}

float gowerDistance(int i,int _sampleClassified){
    float distance = 0;


    distance = nominalAtrib(dataSetCat.matrix[i][0],dataSetCat.matrix[_sampleClassified][0])+nominalAtrib(dataSetCat.matrix[i][1],dataSetCat.matrix[_sampleClassified][1])+numericalAtrib(atoi(dataSetCat.matrix[i][2]),atoi(dataSetCat.matrix[_sampleClassified][2]),5)+numericalAtrib(atoi(dataSetCat.matrix[i][3]),atoi(dataSetCat.matrix[_sampleClassified][3]),5)+nominalAtrib(dataSetCat.matrix[i][4],dataSetCat.matrix[_sampleClassified][4])+nominalAtrib(dataSetCat.matrix[i][5],dataSetCat.matrix[_sampleClassified][5]);
    
    distance = distance/dataSetCat.nrFeatures;

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

				distances[i] = 1- gowerDistance(i,_sampleClassified);

			}
			else{
				distances[i] = -1;
			}
		}

    }
    

    return distances;


}

void writeIt(FILE * f, int k, int sampleClassified, float * distances, int* neighboors,int typeOfDataSet,int class){
	fprintf(f, "%d-nearest Neighboors of the sample number: %d, with feature values: ", initialK,sampleClassified);

	


	if(typeOfDataSet == NUMERICAL){
		for(int j = 0; j <= dataSetNum.nrFeatures; j++){
		fprintf(f,"   %f    ", dataSetNum.matrix[sampleClassified][j]);
	}
	fprintf(f,"   \n \n    ");

		for(int i=0; i < k; i++){
			if(flagQuick)
				fprintf(f,"%d. Sample nr: %d, with distance: %f \n", i+1,neighboors[i],distances[i+1]);
			else
				fprintf(f,"%d. Sample nr: %d, with distance: %f \n", i+1,neighboors[i],distances[neighboors[i]]);
			fprintf(f,"feature values: \n");
			for(int j = 0; j <= dataSetNum.nrFeatures; j++){
				fprintf(f,"   %f    ", dataSetNum.matrix[neighboors[i]][j]);
			}
			fprintf(f,"\n \n  ");
		}

		fprintf(f,"The sample if classified as class = %d \n", class);
		fprintf(f, "\n \n\n" );
	}
	else if (typeOfDataSet == CATEGORIC){
		for(int j = 0; j <= dataSetCat.nrFeatures; j++){
		fprintf(f,"   %s    ", dataSetCat.matrix[sampleClassified][j]);
	}
	fprintf(f,"   \n \n    ");
	
		for(int i=0; i < k; i++){
			if(flagQuick)
				fprintf(f,"%d. Sample nr: %d, with distance: %f \n", i+1,neighboors[i],distances[dataSetCat.nrSamples-i-1]);
			else
				fprintf(f,"%d. Sample nr: %d, with distance: %f \n", i+1,neighboors[i],distances[neighboors[i]]);
			fprintf(f,"feature values: \n");
			for(int j = 0; j <= dataSetCat.nrFeatures; j++){
				fprintf(f,"   %s    ", dataSetCat.matrix[neighboors[i]][j]);
			}
			fprintf(f,"\n \n  ");
		}

		fprintf(f,"THe sample if classified as class =  ");
		if (class == 0){
			fprintf(f,"unacc");
			if(dataSetCat.matrix[sampleClassified][dataSetCat.nrFeatures][0] =='u' )
				positiveClassified++;
			else
				negativeClassified++;
		}
		else if(class ==1){
			fprintf(f, "acc" );
			if(dataSetCat.matrix[sampleClassified][dataSetCat.nrFeatures][0] =='a' )
				positiveClassified++;
			else
				negativeClassified++;
		}
		else if(class ==2){
			fprintf(f, "good" );
			if(dataSetCat.matrix[sampleClassified][dataSetCat.nrFeatures][0] =='g' )
				positiveClassified++;
			else
				negativeClassified++;
		}
		else if(class ==3){
			fprintf(f, "vgood" );
			if(dataSetCat.matrix[sampleClassified][dataSetCat.nrFeatures][0] =='v' )
				positiveClassified++;
			else
				negativeClassified++;
		}

		fprintf(f, "\n \n\n" );

	}
	
}

void writeOneOnFile(int k, int sampleClassified, float * distances, int* neighboors, int algorithm,int typeOfDataSet, int class){

	FILE *f = NULL;

	char auxK[5];

	sprintf(auxK, "%d", initialK);
	char str[500];
	

		strcat(str,"Results/");
	strcat(str,auxFile);

	if (algorithm == KNN)
		strcat(str,"KNN_");
	else
		strcat(str,"KNN_PLUS_");

	strcat(str,"K=");
	strcat(str, auxK); 
	strcat(str,".txt");


	f = fopen(str,"w");

	writeIt(f,k,sampleClassified,distances, neighboors,typeOfDataSet,class);


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








void linearSearchNeighboors(int * k, int sampleClassified, float * distances, int *neighboors, int nrSamples, int typeOfDataSet, int algorithm){


	int * visits = (int*)calloc(nrSamples,sizeof(int));
	float min = 999999;
	int minIdx = 0;

	float max = -0.5;
	int maxIdx = 0;

	visits[sampleClassified] = -1;


   
	for(int j = 0; j< *k; j++){
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



	if(algorithm == KNN_PLUS){

		int check = 0;
		float distanceAux = distances[neighboors[*k-1]];
		int lastPosition = *k;


		while(!check){
			check = 1;
			for(int i = 0 ; i <nrSamples; i++ ){
				if (visits[i] != -1){
					if(distances[i] == distanceAux){
						*k= *k+1;
						visits[i] = -1;
						neighboors[lastPosition] = i;
						lastPosition ++;
						check = 0;
						break;
					}
					
			   }
		    }
		}
	}



	

}




void testingSetClassification(int *k, int * neighboors, int algorithm){

	FILE * fpDataSet;
  	int nrSamples = 0;


	FILE *f = NULL;

	char auxK[5];

	sprintf(auxK, "%d", initialK);
	char str[500];
	

	strcat(str,"Results/");
	strcat(str,auxFile);

	if (algorithm == KNN)
		strcat(str,"KNN_");
	else
		strcat(str,"KNN_PLUS_");

	strcat(str,"K=");
	strcat(str, auxK); 
	strcat(str,".txt");


	f = fopen(str,"w");


  	fpDataSet = fopen(testingSet, "r");

    if(fpDataSet == NULL){
      printf("Invalid name of dataSet text file\n");
      exit(0); 
    }

    char pal1[DIM_MAX];

  

    //read the file in order to know the number of samples
    while (!feof (fpDataSet)) {
        if (fgets(pal1, DIM_MAX, fpDataSet))
        	nrSamples++;
    }

      fseek(fpDataSet,0, SEEK_SET);


    for(int i = 0; i < nrSamples; i++){

    	float * sample = (float*)malloc((dataSetNum.nrFeatures+1)*sizeof(float));

    	for(int j = 0; j <= dataSetNum.nrFeatures; j++){
        		if (!fscanf(fpDataSet, "%f", &sample[j])) 
               break;
        	}

        float * distances = (float*)malloc(dataSetNum.nrSamples*sizeof(float));

		for(int z = 0; z < dataSetNum.nrSamples; z++){

				distances[z] = 0.0;

    			for(int x = 0; x < dataSetNum.nrFeatures; x++){
                distances[z]  =distances[z] + pow(sample[x] - dataSetNum.matrix[z][x],2);
           		 }

            	distances[z] = sqrt(distances[z]);

		}

			int * visits = (int*)calloc(dataSetNum.nrSamples,sizeof(int));
			float min = 999999;
			int minIdx = 0;

			float max = -0.5;
			int maxIdx = 0;



   
			for(int j = 0; j< *k; j++){
				min = 999999;
				for(int a = 0 ; a <dataSetNum.nrSamples; a++ ){
					if (visits[a] != -1){
						if(distances[a] < min){
							min = distances[a];
							minIdx = a;
						}

					}
				}
				neighboors[j] = minIdx;
				visits[minIdx] = -1;

			}



		if(algorithm == KNN_PLUS){

			int check = 0;
			float distanceAux = distances[neighboors[*k-1]];
			int lastPosition = *k;


			while(!check){
				check = 1;
				for(int t = 0 ; t <nrSamples; t++ ){
					if (visits[t] != -1){
						if(distances[t] == distanceAux){
							*k= *k+1;
							visits[t] = -1;
							neighboors[lastPosition] = t;
							lastPosition ++;
							check = 0;
							break;
						}
					
			   		}
		    	}
			}
		}

		int class;
		int classes[MAX_SIZE] ={ 0 };
		int _max = 0;
		int _maxIdx = 0;

		for(int ij = 0; ij < *k; ij++)
			classes[(int)dataSetNum.matrix[neighboors[ij]][dataSetNum.nrFeatures]]++;
	


		for(int j = 0; j < MAX_SIZE; j++){
			if(classes[j] > _max){
				_max = classes[j];
				_maxIdx = j;
			}
		}

		class = _maxIdx;



		fprintf(f, "%d-nearest Neighboors of the sample with feature values: ", initialK);

	
		for(int j = 0; j <= dataSetNum.nrFeatures; j++){
			fprintf(f,"   %f    ", sample[j]);
	    }
			fprintf(f,"   \n \n    ");

		for(int i=0; i < *k; i++){
			
			fprintf(f,"%d. Sample nr: %d, with distance: %f \n", i+1,neighboors[i],distances[neighboors[i]]);
			fprintf(f,"feature values: \n");
			for(int j = 0; j <= dataSetNum.nrFeatures; j++){
				fprintf(f,"   %f    ", dataSetNum.matrix[neighboors[i]][j]);
			}
			fprintf(f,"\n \n  ");
		}

		fprintf(f,"The sample if classified as class = %d \n", class);
		fprintf(f, "\n \n\n" );


    }

}




int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}




void computeNeighboors(int sampleClassified, int typeOfDataSet, int * idxSort,int *neighboors, float* _distances, int * k,int algorithm){


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

	

		if(*k < log2(nrSamples)){
			//printf("linear search \n \n");
			linearSearchNeighboors(k,sampleClassified,_distances, neighboors,nrSamples, typeOfDataSet,algorithm);
		}
		else{
			//printf("QUICKSORT \n\n");

		
			idxSort = (int*) malloc(nrSamples*sizeof(int)); 

			for(int i =0; i < nrSamples; i++)
				idxSort[i] = i;

			quicksort(_distances, idxSort, 0, nrSamples-1);



			for(int i =1; i<= *k; i++){
				neighboors[i-1] = idxSort[i];

			}
			int i = *k +1;
			if(algorithm == KNN_PLUS){
				while(1){

						if(_distances[i] == _distances[i-1]){
								*k= *k+1;
								neighboors[i-1] = idxSort[i];
						}
						else 
							break;
   		
	    		   		i++;
   
			   }
			}	


		}

		


}



int computeClassCat(int *neighboors, int k){
	int classes[MAX_SIZE] ={ 0 };
	int max = 0;
	int maxIdx = 0;

	for(int i = 0; i < k; i++){
		if(dataSetCat.matrix[neighboors[i]][dataSetCat.nrFeatures][0]=='u' ){
			classes[0]++;
		}
		else if(dataSetCat.matrix[neighboors[i]][dataSetCat.nrFeatures][0]=='a'){
			classes[1]++;
		}
		else if(dataSetCat.matrix[neighboors[i]][dataSetCat.nrFeatures][0]=='g')
			classes[2]++;
		else if(dataSetCat.matrix[neighboors[i]][dataSetCat.nrFeatures][0]=='v')
			classes[3]++;
		
	}

	for(int j = 0; j < 4; j++){
		if(classes[j] > max){
			max = classes[j];
			maxIdx = j;
		}
	}

	return maxIdx;


}


int computeClassNum(int *neighboors, int k,int sampleClassified){
	int classes[MAX_SIZE] ={ 0 };
	int max = 0;
	int maxIdx = 0;

	for(int i = 0; i < k; i++)
		classes[(int)dataSetNum.matrix[neighboors[i]][dataSetNum.nrFeatures]]++;
	


	for(int j = 0; j < MAX_SIZE; j++){
		if(classes[j] > max){
			max = classes[j];
			maxIdx = j;
		}
	}

	if((int)(dataSetNum.matrix[sampleClassified][dataSetNum.nrFeatures]) == maxIdx)
		positiveClassified++;
	else
		negativeClassified++;

	return maxIdx;


}

void computeRandom(int typeOfDataSet, int * idxSort,int *neighboors, float* distances, int * k, int algorithm){
	FILE *f = NULL;

	char auxK[5];

	sprintf(auxK, "%d", initialK);
	char str[500];
	

	strcat(str,"Results/");
	strcat(str,auxFile);

	if (algorithm == KNN)
		strcat(str,"KNN_");
	else
		strcat(str,"KNN_PLUS_");

	strcat(str,"K=");
	strcat(str, auxK); 
	strcat(str,".txt");




	f = fopen(str,"w");


	


	srand(time(NULL));   // Initialization, should only be called once.
    

    for(int i = 0; i < dataSetNum.nrSamples/3; i++){
	    int sampleClassified = rand()%(dataSetNum.nrSamples-1); 
	    distances = computeDistances(sampleClassified, typeOfDataSet);
	    computeNeighboors(sampleClassified, typeOfDataSet,idxSort,neighboors, distances,k, algorithm);
	    int class;
	    if(typeOfDataSet == NUMERICAL)
	    	class = computeClassNum(neighboors,  *k, sampleClassified);
	    else 
	    	class = computeClassCat(neighboors,*k);
	    writeIt(f,*k,sampleClassified,distances, neighboors,typeOfDataSet,class);
	    *k = initialK;
    } 

} 

void leaveOneOut(int typeOfDataSet, int * idxSort,int *neighboors, float* distances, int * k, int algorithm){
	FILE *f = NULL;

	char auxK[5];

	sprintf(auxK, "%d", initialK);
	char str[500];
	


	strcat(str,"Results/");
	strcat(str,auxFile);

	if (algorithm == KNN)
		strcat(str,"KNN_");
	else
		strcat(str,"KNN_PLUS_");

	strcat(str,"K=");
	strcat(str, auxK); 
	strcat(str,".txt");


	printf("antes -> string é %s \n",str);
	f = fopen(str,"w");

	printf("a string é %s \n",str);


    struct timeval stop, start;
   


    for(int i = 0; i < dataSetNum.nrSamples; i++){
    	int sampleClassified = i;
	    distances = computeDistances(sampleClassified, typeOfDataSet);
	    computeNeighboors(sampleClassified, typeOfDataSet,idxSort,neighboors, distances,k, algorithm);
	    int class;
	    if(typeOfDataSet == NUMERICAL)
	    	class = computeClassNum(neighboors,  *k, sampleClassified);
	    else 
	    	class = computeClassCat(neighboors,*k);
	        
	gettimeofday(&start, NULL);
  
	writeIt(f,*k,sampleClassified,distances, neighboors,typeOfDataSet,class);
	gettimeofday(&stop, NULL);
	
	diffTime  =diffTime +   (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;

	    *k = initialK;
    } 

} 








void KnnClassification(int typeOfDataSet,int classification,int sampleClassified, int normalization, int * k, int algorithm){

	float * distances;
	
	if( typeOfDataSet == NUMERICAL){
		distances = (float*)malloc(dataSetNum.nrSamples*sizeof(float));
	}
	else if( typeOfDataSet == CATEGORIC){
		distances = (float*)malloc(dataSetCat.nrSamples*sizeof(float));	
	}

	
	int * idxSort = NULL;
	int  neighboors[MAX_KNN] = { 0 };

	if(classification == ONE_SAMPLE){
		distances = computeDistances(sampleClassified, typeOfDataSet);
		
		computeNeighboors(sampleClassified, typeOfDataSet,idxSort,neighboors, distances, k, algorithm);
		int class;
		if(typeOfDataSet == NUMERICAL)
			class = computeClassNum(neighboors, *k,sampleClassified);
		else 
	    	class = computeClassCat(neighboors,*k);
		writeOneOnFile(*k,sampleClassified,distances, neighboors, algorithm, typeOfDataSet,class);		


	}
	else if(classification == RANDOM){
		computeRandom(typeOfDataSet,idxSort,neighboors, distances,k, algorithm);
	}

	else if(classification == LEAVE_ONE_OUT){
		leaveOneOut(typeOfDataSet,idxSort,neighboors, distances,k, algorithm);
	}

	else if(classification == ADDITIONAL)
		testingSetClassification(k,neighboors, algorithm);
	
	

	
}
