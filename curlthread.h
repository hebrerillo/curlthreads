#ifndef CURLTHREAD_H
#define	CURLTHREAD_H
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

#ifdef	__cplusplus
extern "C"
{
#endif

  /**
   * This struct saves all the information required
   * to perform a curl request
   */
  typedef struct
  {
    char *url;
    char *type; //Type of the request: GET or POST
    char *params; //Request parameters (only if type is POST)
    char *result; //The result returned by the curl request
    CURLcode res; //The result code of the curl request
    char *error; //Error string just in case the request fails
  } curlRequest;

  

#ifdef	__cplusplus
}
#endif

#endif	/* CURLTHREAD_H */

