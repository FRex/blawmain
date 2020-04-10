# blawmain

`blawmain.h` is a single C header that makes it easier to write command line
program thats can take Unicode command line arguments.

To use it: name your UTF-8 entry point function something else than `main`,
don't create your own `wmain`, define `BLA_WMAIN_FUNC` to be the name of your
main function and include the header (once, in a single .c or .cpp file only).

If macro `_MSC_VER` or `BLA_WMAIN_USE_WMAIN` is defined it will create an
`int wmain(int argc, wchar_t ** argv)` function that allocates space using a
single malloc and converts from UTF-16 to UTF-8 using `WideCharToMultiByte`
then passes the resulting argv to your main function. Otherwise it will create
an `int main(int argc, char ** argv)` function that simply passes the arguments
to your main function untouched.

In either case `BLA_WMAIN_USING_WMAIN_BOOLEAN` is defined, to 1 if `wmain` is
used and 0 otherwise. The return from your main function is returned from that
`wmain`/`main`, except in case of `wmain` if the single `malloc` fails (very
unlikely) it will `fprintf` an error to `stderr` return 111.

See `test.c` for an example usage.

I wrote it mainly to cut down on repetition and copy pasting in my small
portable pure C programs like [analyzepng](https://github.com/FRex/analyzepng),
[topng](https://github.com/FRex/topng),
[binarypic](https://github.com/FRex/binarypic)
and [pixel](https://github.com/FRex/pixelsum).

This header lets you keep most of your code using UTF-8 in `char` strings but
you will still need to convert to UTF-16 `wchar_t` yourself to (for example) open
a file with Unicode name on Windows using `_wfopen` or `CreateFileW`. So if
you're writing a Windows only CLI program you might want to use own `wmain`
instead of this file and use UTF-16 throughout your program. This header also
doesn't create a `WinMain` function for you (that you'll need when creating a
`subsystem:windows` GUI program on Windows).

If you're looking for a more comprehensive library to do similar things you can try
[Boost.Nowide](https://www.boost.org/doc/libs/develop/libs/nowide/doc/html/index.html).
