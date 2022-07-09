#include <stdio.h>
#include <windows.h>
#include <fcntl.h>

/* NOTE compile with:
1. gcc -municode (might fail to find WinMain without the option)
2. clang (no extra options)
3. cl (no extra options)

Then invoke this program with some Unicode arguments (like accented letters
or any other non-latin/non-ASCII scripts and characters), to see what happens
to them with and without conversion.

For example on Windows without conversion on my system the latin based letters
with diacritics are converted to their base ASCII form, and non-latin script
characters are turned into question marks.

Defined BLA_WMAIN_FORCE_OFF to force conversion off on Windows.

Go to https://frex.github.io/unicode.html to explore Unicode more.

*/

static int mymain(int argc, char ** argv, wchar_t ** wargv);
#define BLA_WMAIN_FUNC3 mymain
#include "blawmain.h"

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

static int mymain(int argc, char ** argv, wchar_t ** wargv)
{
    int i;

    printf("BLA_WMAIN_USING_WMAIN_BOOLEAN = %d\n", BLA_WMAIN_USING_WMAIN_BOOLEAN);
    for(i = 1; i < argc; ++i)
    {
        print_binary(i, argv[i]);
        printf("%d) '%s'\n", i, argv[i]);
        if(wargv)
            printf("%d) 0x%x\n", i, wargv[i][0]);
        puts("");
    }//for

    return 0;
}
