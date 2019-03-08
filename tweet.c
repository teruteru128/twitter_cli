
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <oauth.h>

#include "twitter.h"

#define CONTENT_SIZE (141)
#define KEY_STATUS "status="
#define TWEET_URL "https://api.twitter.com/1.1/statuses/update.json"
#define CONSUMER_KEY "4l6eERG80O2JswFLBafrLGLTO"
#define CONSUMER_SECRET "ysvmOXylPIDUeeSxhw7p5kIxEqjMj83ZEHJdI8WnQGxehYcjVx"
#define ACCESS_TOKEN "533912006-mzY41BuYkf5l1E7CtYkHVHPirwq1ASdbnx1VmoiM"
#define TOKEN_SECRET "b0leZJDxQ3FpJLIlC96f69oFnKs5TvU1Gtjarw3E4qEGh"

static size_t post_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t r = size * nmemb;
    printf("Posted to twitter. Response size: %zu\n", r);
    printf("%s\n", ptr);
    return r;
}

int tweet(char *status)
{
    int code = 0;
    char *content = status;
    char *url_enc_args = NULL;
    char *postdata = NULL;
    int argc = 0;
    char **argv = NULL;
    struct curl_slist *header = NULL;

    /**********************************************************/
    char *string;
    size_t size = sizeof(KEY_STATUS) + CONTENT_SIZE;
    string = malloc(size);
    if (string == NULL)
    {
        return 1;
    }
    string[0] = 0;
    strncat(string, KEY_STATUS, size);
    strncat(string, content, size);
    url_enc_args = oauth_url_escape(string);
    free(string);
    string = NULL;
    if (url_enc_args == NULL)
    {
        return 2;
    }

    /**************************************************************/
    size_t ser_url_size = strlen(TWEET_URL) + strlen(url_enc_args) + 2;
    char *ser_url;
    ser_url = malloc(ser_url_size);
    if (ser_url == NULL)
    {
        return 3;
    }
    int r = snprintf(ser_url, ser_url_size, "%s?%s", TWEET_URL, url_enc_args);
    if (r < 0)
    {
        return r;
    }
    free(url_enc_args);
    url_enc_args = NULL;

    argc = oauth_split_url_parameters(ser_url, &argv);
    free(ser_url);
    ser_url = NULL;
    char *tmp_url = oauth_sign_array2(&argc, &argv, NULL, OA_HMAC, "POST", CONSUMER_KEY, CONSUMER_SECRET, ACCESS_TOKEN, TOKEN_SECRET);
    if (tmp_url == NULL)
    {
        return 4;
    }
    free(tmp_url);
    tmp_url = NULL;

    /**************************************************************/

    char *auth_params = oauth_serialize_url_sep(argc, 1, argv, ", ", 6);
    if (auth_params == NULL)
    {
        return 5;
    }
    char auth_header[4096];
    sprintf(auth_header, "Authorization: OAuth %s", auth_params);
    free(auth_params);

    header = curl_slist_append(header, auth_header);
    if(header == NULL){
        return 6;
    }

    /*****************************************************************/

    postdata = oauth_serialize_url_sep(argc, 1, argv, "&", 1);
    if(postdata == NULL){
        return 7;
    }

    /******************************************************************/

    int i;
    for(i = 0; i < argc; i++){
        free(argv[i]);
    }
    free(argv);
    argc = 0;
    argv = NULL;

    /********************************************************************/

    CURL *handle = curl_easy_init();
    if(handle == NULL){
        return 8;
    }

    /******************************************************************/

    r = 0;

    r = curl_easy_setopt(handle, CURLOPT_POSTFIELDS, postdata);
    if(r != CURLE_OK){
        return r;
    }

    r = curl_easy_setopt(handle, CURLOPT_HTTPHEADER, header);
    if(r != CURLE_OK){
        return r;
    }

    r = curl_easy_setopt(handle, CURLOPT_URL, TWEET_URL);
    if(r != CURLE_OK){
        return r;
    }

    r = curl_easy_setopt(handle, CURLOPT_POST, 1);
    if (r != CURLE_OK) {
        return r;
    }
    r = curl_easy_setopt(handle, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    if (r != CURLE_OK) {
        return r;
    }

    r = curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, post_callback);
    if (r != CURLE_OK) {
        return r;
    }
    
    r = curl_easy_perform(handle);
    if (r != CURLE_OK) {
        return r;
    }
    //Check response code
    long rc = 0;
    r = curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &rc);
    if (r != CURLE_OK) {
        return r;
    }
    if (rc / 100 != 2) {
        return (int)rc;
    }

    /*******************************************************************/

    curl_easy_cleanup(handle);

    return code;
}
