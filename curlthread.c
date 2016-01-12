#include "curlthread.h"


curlRequest initCurlRequest(const char *url, const char *type, const char *params)
{
    curlRequest ret =
    {
      .url = url,
      .type = type,
      .params = params,
      .size = 0,
      .result = NULL
    };
    return ret;
}

int performCurlThreads(List *l)
{
    int i;

    if (l == NULL || l->head == NULL || l->size == 0)//check empty list
    {
        return 0;
    }
    curl_global_init(CURL_GLOBAL_ALL);
    pthread_t *threads = (pthread_t*) malloc(sizeof (pthread_t) * l->size);
    ListElement *current = l->head;

    i = 0;
    while (current != NULL && i < l->size)
    {
        //for each element of the list, create a thread to handle the curl request
        pthread_create(&threads[i], NULL, curl_thread_func, current->data);
        current = current->next;
        i++;
    }

    i = 0;
    while (i < l->size)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    free(threads);
    curl_global_cleanup();
    return 1;
}

void *curl_thread_func(void *ptr)
{
    curlRequest *s = (curlRequest*) ptr;

    CURL* curl;
    CURLcode res;
    
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, s->url);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &curlCallback);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, s);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        s->error = curl_easy_strerror(res);
        s->resCode = res;
    }
    curl_easy_cleanup(curl);

    return NULL;
}


size_t curlCallback(char* ptr, size_t size, size_t nmemb, curlRequest *s)
{
    size_t ssize = nmemb * size;

    s->result = (char*)malloc(ssize + 1);
    s->size = ssize;
    if (s->result == NULL)
    {
        fprintf(stderr, "malloc() failed to allocate memory to s->result\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->result, ptr, ssize);
    s->result[ssize] = '\0';
    
    return ssize;
}

void freeCurlRequest(curlRequest *s)
{
    if (s != NULL && s->size > 0 && s->result != NULL)
    {
        free(s->result);
    }
}

