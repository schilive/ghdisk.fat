/*
MIT License

Copyright (c) 2025 Gabriel Silva Schilive <schilive100@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* This file implemenst 'sys_prnout()' and 'sys_prnerr()', with the Win32 API,
 * in a MSVC/MinGW-compatible form.
 */

#include <windows.h>
#include <stddef.h>
#include "../sys.h"

#define DWORD_MAX ((DWORD)(0xFFFFFFFF))

static void prn(HANDLE out, char *cs, size_t n)
{
        /* The function 'WriteFile()' also works with console handles, but the
         * function 'WriteConsole()' does not work with file handles. Using
         * 'WriteFile()' instead of 'WriteConsole()' is problematic when writing
         * Double-Byte Character Set (DBCS), like Windows UNICODE. However, we
         * are only using ANSI, where the first 127 values are always
         * ASCII-compatible. So, we are safe.
         */
        size_t off;
        if (sizeof(DWORD) >= sizeof(size_t)) {
                WriteFile(out, cs, (DWORD)n, NULL, NULL);
                return;
        }

        off = 0;
        while (n != 0) {
                if (n <= DWORD_MAX) {
                        WriteFile(out, cs + off, (DWORD)n, NULL, NULL);
                        break;
                }

                WriteFile(out, cs + off, DWORD_MAX, NULL, NULL);
                n -= DWORD_MAX;
                off += DWORD_MAX;
        }
}

void sys_prnout(char *cs, size_t n)
{
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        if (out == INVALID_HANDLE_VALUE)
                return;
        prn(out, cs, n);
}

void sys_prnerr(char *cs, size_t n)
{

        HANDLE out = GetStdHandle(STD_ERROR_HANDLE);
        if (out == INVALID_HANDLE_VALUE)
                return;
        prn(out, cs, n);
}
