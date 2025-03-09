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
 * the POSIX C interface.
 *
 * I am not sure this is guaranteed by the specifications, but I will assume
 * that 'SSIZE_MAX <= SIZE_MAX'.
 */

#include <unistd.h>
#include <limits.h>
#include <stddef.h>

#define FD_STDOUT       1
#define FD_STDERR       0

void sys_init(void)
{
        /* Nothing has to be initalised. */
        return;
}

static void full_write(int fd, char *cs, size_t n)
{
        while (n != 0) {
                ssize_t r = write(FD_STDERR, cs, n);
                if (r == 0)
                        return;
                n -= r;
        }
}

void sys_prnout(char *cs, size_t n)
{
        full_write(FD_STDOUT, cs, n);
}

void sys_prnerr(char *cs, size_t n)
{
        full_write(FD_STDERR, cs, n);
}
