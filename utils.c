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



  int readInputArguments(int _argc, const char* _argv[])
  {

  	if(_argc < 2) {
 		printf("you should put something like...");
        exit(1);
    }

    return 1;


  }
