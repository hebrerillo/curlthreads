#include <stdio.h>
#include <stdlib.h>
#include "curlthread.h"

int main(int argc, char** argv)
{
    
    curlRequest r1,r2;
    r1 = initCurlRequest("http://localhost/tests/index.php",NULL,"var=5");
    r2 = initCurlRequest("http://localhost/tests/index.php?var=4","POST","var=5");
    
    List l;
    init(&l,NULL,NULL);

    insert(&l,&r1,sizeof(r1));
    insert(&l,&r2,sizeof(r2));
    
    performCurlThreads(&l);
    
    printf("result 1 = %s\n",r1.result);
    printf("result 2 = %s\n",r2.result);
    destroyList(&l);
    freeCurlRequest(&r1);
    freeCurlRequest(&r2);
    return (EXIT_SUCCESS);
}

