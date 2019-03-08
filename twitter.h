
#ifndef TWITTER_H
#define TWITTER_H

#include <stdio.h>

typedef struct consumer_t
{
    char *consumer_key;
    char *consumer_secret;
} Consumer;

typedef struct access_token_t
{
    char *access_token;
    char *token_secret;
} AccessToken;

typedef struct twitter_t {
    Consumer consumer;
    AccessToken token;
} Twitter;

extern Twitter *initTwitter(Twitter *);

#endif
