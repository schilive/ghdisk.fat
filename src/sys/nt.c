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

/* This file implemenst 'sys_prnout()', 'sys_prnerr()' and 'sys_init()', with
 * the Win32 API, in a MSVC/MinGW-compatible form.
 */

#include <windows.h>
#include <stddef.h>
#include "../sys.h"

#define DWORD_MAX ((DWORD)(0xFFFFFFFF))

static HANDLE g_handle_out = INVALID_HANDLE_VALUE;
static HANDLE g_handle_error = INVALID_HANDLE_VALUE;

void sys_init_console(void)
{
        g_handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
        g_handle_error = GetStdHandle(STD_ERROR_HANDLE);
}

/* It tries to write everything. If successful, returns 0, otherwise a non-zero
 * value.
 */
static int full_write(HANDLE out, char *cs, size_t n)
{
        while (n != 0) {
                DWORD wrt;
                DWORD r = WriteFile(out, cs, n, &wrt, NULL);
                if (r == FALSE || wrt == 0)
                        return 1;
                n -= wrt;
        }
        return 0;
}

/* Prints the character array of length 'n' to the standard device specified in
 * 'out'.
 */
static void prn(HANDLE out, char *cs, size_t n)
{
        /* The function 'WriteFile()' also works with console handles, but the
         * function 'WriteConsole()' does not work with file handles. Using
         * 'WriteFile()' instead of 'WriteConsole()' is problematic when writing
         * Double-Byte Character Set (DBCS), like Windows UNICODE. However, we
         * are only using ANSI, where the first 127 values are always
         * ASCII-compatible. So, we are safe.
         */
        if (sizeof(DWORD) >= sizeof(size_t)) {
                (void)full_write(out, cs, (DWORD)n);
                return;
        }

        while (n != 0) {
                DWORD w;
                int r;
                w = n <= DWORD_MAX ? (DWORD)n : DWORD_MAX;
                r = full_write(out, cs, (DWORD)w);
                if (r != 0)
                        return;
                n -= w;
                cs += w;
        }
}

void sys_prnout(char *cs, size_t n)
{
        if (g_handle_out == INVALID_HANDLE_VALUE)
                return;
        prn(g_handle_out, cs, n);
}

void sys_prnerr(char *cs, size_t n)
{
        if (g_handle_error == INVALID_HANDLE_VALUE)
                return;
        prn(g_handle_error, cs, n);
}

size_t sys_strlen(char *s)
{
        return lstrlenA((LPSTR)s);
}

int sys_streq(char *s1, char *s2)
{
        return lstrcmpA(s1, s2) == 0;
}
