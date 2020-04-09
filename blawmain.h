#ifndef _MSC_VER

int main(int argc, char ** argv)
{
    return BLA_WMAIN_FUNC(argc, argv);
}

#else

/* for WideCharToMultiByte and malloc */
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
    utf8argv[argc] = NULL;
    endptr = ((char*)utf8argv) + bytesneeded;

    if(!utf8argv)
    {
        fputs("Error: malloc error in wmain\n", stderr);
        return 111;
    }

    utf8ptrout = (char*)(utf8argv + (argc + 1));
    for(i = 0; i < argc; ++i)
    {
        const int out = WideCharToMultiByte(CP_UTF8, 0, argv[i], -1, utf8ptrout, endptr - utf8ptrout, NULL, NULL);
        utf8argv[i] = utf8ptrout;
        utf8ptrout += out;
    } /* for */

    retcode = BLA_WMAIN_FUNC(argc, utf8argv);
    free(utf8argv);
    return retcode;
}

#endif
