#include <stdio.h>

static void print_binary(int idx, const char * str)
{
    printf("%d)", idx);
    while(*str)
    {
        const unsigned char c = *str;
        printf(" %c%c%c%c%c%c%c%c",
            '0' + ((c >> 7) & 1),
            '0' + ((c >> 6) & 1),
            '0' + ((c >> 5) & 1),
            '0' + ((c >> 4) & 1),
            '0' + ((c >> 3) & 1),
            '0' + ((c >> 2) & 1),
            '0' + ((c >> 1) & 1),
            '0' + ((c >> 0) & 1)
        );
        ++str;
    }

    printf("\n");
}

static int mymain(int argc, char ** argv)
{
    int i;

    for(i = 1; i < argc; ++i)
        print_binary(i, argv[i]);

    return 0;
}

#define BLA_WMAIN_FUNC mymain
#include "blawmain.h"
