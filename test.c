#include <stdio.h>

static void print_bytes(const char * str)
{
    while(*str)
    {
        printf("0x%02x, ", (unsigned char)*str);
        ++str;
    }

    printf("\n");
}

static int mymain(int argc, char ** argv)
{
    int i;

    for(i = 1; i < argc; ++i)
        print_bytes(argv[i]);

    return 0;
}

#define BLA_WMAIN_FUNC mymain
#include "blawmain.h"
