
#include "twitter.h"

Twitter *setConsumerKey(Twitter *twitter,char *consumerKey)
{
    twitter->consumer.consumer_key = consumerKey;
    return twitter;
}

Twitter *setConsumerSecret(Twitter *twitter,char *consumerSecret)
{
    twitter->consumer.consumer_secret = consumerSecret;
    return twitter;
}

Twitter *setAccessToken(Twitter *twitter,char *accessToken)
{
    twitter->token.access_token = accessToken;
    return twitter;
}

Twitter *setTokenSecret(Twitter *twitter,char *tokenSecret)
{
    twitter->token.token_secret = tokenSecret;
    return twitter;
}

/**
 * 設定ファイルから読み込み
*/
Twitter *initTwitter(Twitter *twitter)
{
    return twitter;
}
