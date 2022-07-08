#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
#define BLA_WMAIN_USE_WMAIN
#endif

#if defined(BLA_WMAIN_FUNC3) && defined(BLA_WMAIN_FUNC)
#error "both BLA_WMAIN_FUNC3 and BLA_WMAIN_FUNC defined"
#endif

#if !(defined(BLA_WMAIN_FUNC3) || defined(BLA_WMAIN_FUNC))
#error "BLA_WMAIN_FUNC or BLA_WMAIN_FUNC3 must be defined"
#endif

/*

BLA_WMAIN_FUNC - same as normal int main(int argc, char ** argv);
BLA_WMAIN_FUNC3 - like normal main but with extra argument for original argv
int main(int argc, char ** argv, wchar_t ** wargv), NULL outside windows

TO USE:
1. define BLA_WMAIN_FUNC or BLA_WMAIN_FUNC3 - whichever you need, but only one of them (this is enforced by the preprocessor)
2. include this header in some .c or .cpp file, usually (but its not mandatory) the one with your main
3. allow the main or wmain from this file to be the entry point, and it will convert (if needed) and call your main

NOTE: the order of 1. and 2. matters, you must define your macro before including this file, so it can use it
NOTE: in case of error "undefined reference to `WinMain'" with GCC on Windows make sure you pass -municode

*/

#ifdef BLA_WMAIN_USE_WMAIN

#define BLA_WMAIN_USING_WMAIN_BOOLEAN 1

/* for WideCharToMultiByte and malloc */
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdlib.h>

int wmain(int argc, wchar_t ** argv)
{
    int i, retcode, bytesneeded;
    char ** utf8argv;
    char * utf8ptrout;
    char * endptr;

    bytesneeded = sizeof(char*) * (argc + 1);
    for(i = 0; i < argc; ++i)
        bytesneeded += WideCharToMultiByte(CP_UTF8, 0, argv[i], -1, NULL, 0, NULL, NULL);

    utf8argv  = (char **)malloc(bytesneeded);

    if(!utf8argv)
    {
        fputs("Error: malloc error in wmain\n", stderr);
        return 111;
    }

    utf8argv[argc] = NULL;
    endptr = ((char*)utf8argv) + bytesneeded;
    utf8ptrout = (char*)(utf8argv + (argc + 1));
    for(i = 0; i < argc; ++i)
    {
        const int out = WideCharToMultiByte(CP_UTF8, 0, argv[i], -1, utf8ptrout, endptr - utf8ptrout, NULL, NULL);
        utf8argv[i] = utf8ptrout;
        utf8ptrout += out;
    } /* for */

#ifdef BLA_WMAIN_FUNC3
    retcode = BLA_WMAIN_FUNC3(argc, utf8argv, argv);
#else
    retcode = BLA_WMAIN_FUNC(argc, utf8argv);
#endif

    free(utf8argv);
    return retcode;
}

#else

#define BLA_WMAIN_USING_WMAIN_BOOLEAN 0

int main(int argc, char ** argv)
{
#ifdef BLA_WMAIN_FUNC3
    retcode = BLA_WMAIN_FUNC3(argc, argv, NULL);
#else
    retcode = BLA_WMAIN_FUNC(argc, argv);
#endif
}

#endif
