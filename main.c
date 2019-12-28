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


int main(int argc, char const *argv[]) {

    int readSignal = readInputArguments(argc, argv);

    printf("%d\n",readSignal);

    printf("oola \n");

    

	return 0;
}