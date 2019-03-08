
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <oauth.h>
#include <locale.h>
#include <wchar.h>
#include <curl/curl.h>

#include "twitter.h"
#include "tweet.h"

void printHelp(char *name)
{
    printf("%s <status>\n", name);
    printf("%s --register\n", name);
    printf("%s --login\n", name);
    printf("%s --logout\n", name);
    printf("%s --init\n", name);
    printf("%s <-l|--tweet-length> <status>\n", name);
}

int main(int argc, char **argv)
{
    int rc = EXIT_SUCCESS;
    if (argc < 2)
    {
        wchar_t *unchi = L"💩";
        char *in = calloc(141, sizeof(wchar_t));
        setlocale(LC_ALL, "ja_JP.UTF-8");
        wcstombs(in, unchi, sizeof(wchar_t) * 141);
        rc = tweet(in);
    }
    else
    {
        rc = tweet(argv[1]);
    }
    return rc;
}
/*
argc, argv

if argc < 2
	read stdin
 	tweet

// --help, --register, --login, --logout, --init, --tweet-length, -l
if argv[1] eq --help
else if argc < 3
    show help
else if argv[2] eq --register
else if argv[2] eq --login
else if argv[2] eq --logout
else if argv[2] eq --init
else if argv[2] eq --tweet-length OR argv[2] eq -l
else
    tweet
*/
