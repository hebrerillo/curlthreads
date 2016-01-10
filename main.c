#include <stdio.h>
#include <stdlib.h>
#include "curlthread.h"

int main(int argc, char** argv)
{
    
    curlRequest r1 = {
        .url = "http://localhost/tests/index.php",
        .type = "POST",
        .params = "var=5",
        .result = NULL
    };
    
    curlRequest r2 = {
        .url = "http://localhost/tests/index.php?var=4",
        .type = "POST",
        .params = "var=5",
        .result = NULL
    };
    
    List l;
    init(&l,NULL,NULL);

    insert(&l,&r1,sizeof(r1));
    insert(&l,&r2,sizeof(r2));
    
    performCurlThreads(&l);
    
    printf("result 1 = %s\n",r1.result);
    printf("result 2 = %s\n",r2.result);
    free(r1.result);
    free(r2.result);
    
    return (EXIT_SUCCESS);
}

