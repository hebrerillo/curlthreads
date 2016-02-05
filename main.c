#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "curlthread.h"

/**
 * Saves the result of the curl request to a file
 * 
 * @param request
 */
void* saveToFile(curlRequest *request)
{
    
    FILE *file;
    if( (file = fopen("result.txt","w")) == NULL )
    {
        fprintf(stderr,"Error opening file %s\n",strerror(errno));
        return NULL;
    }
    
    fwrite(request->result,sizeof(char),strlen(request->result),file);
    fclose(file);
    
    return NULL;
}

int main(int argc, char** argv)
{
    
    curlRequest r1,r2;
    r1 = initCurlRequest("http://localhost/tests/index.php",1,"var=5",(void*)saveToFile);
    r2 = initCurlRequest("http://localhost/tests/index.php",1,"var=15",NULL);
    
    List l;
    init(&l,NULL,NULL);

    insert(&l,&r1,sizeof(r1));
    insert(&l,&r2,sizeof(r2));
    
    performCurlThreads(&l);
    
    destroyList(&l);
    freeCurlRequest(&r1);
    freeCurlRequest(&r2);
    return (EXIT_SUCCESS);
}

