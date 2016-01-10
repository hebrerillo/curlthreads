#ifndef CURLTHREAD_H
#define	CURLTHREAD_H
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "list.h"

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
    const char *url;
    const char *type; //Type of the request: GET or POST
    const char *params; //Request parameters (only if type is POST)
    char *result; //The result returned by the curl request
    size_t size; //The size of the result
    CURLcode resCode; //The result code of the curl request
    const char *error; //Error string just in case the request fails
  } curlRequest;

  /**
   * Initialize a curl request from a set of params
   * @param url
   * @param type
   * @param params
   * @return 
   */
  curlRequest initCurlRequest(const char *url, const char *type, const char *params);
  
  /**
   * Performs several curl calls, each one running in a separate thread. 
   * The list l contains curlRequest structs, each one defining the curl parameters for each call
   * 
   * @param l A list containing curlRequest structs
   */
  int performCurlThreads(List *l);
  
  
  
  /**
   * 
   * Handles the result of a curl request. It will save the result to s->result
   * @param ptr
   * @param size
   * @param nmemb
   * @param s A pointer to curlRequest struct
   * @return The number of bytes handled by the curl request
   */
  size_t curlCallback(char* ptr, size_t size, size_t nmemb, curlRequest *s);
  
  
  
  /**
   * Handles the execution of a thread
   * @param ptr
   * @return 
   */
  void *curl_thread_func(void *ptr);

#ifdef	__cplusplus
}
#endif

#endif	/* CURLTHREAD_H */

