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
 * the standard ISO C library.
 */

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "../sys.h"

void sys_init(void)
{
        /* Nothing needs to be initialised in ISO C. */
        return;
}

void sys_prnout(char *cs, size_t n)
{
        size_t i;
        for (i = 0; i < n; i++)
                printf("%c", cs[i]);
}

void sys_prnerr(char *cs, size_t n)
{
        size_t i;
        for (i = 0; i < n; i++)
                fprintf(stderr, "%c", cs[i]);
}

size_t sys_strlen(char *s)
{
        return strlen(s);
}

int sys_streq(char *s1, char *s2)
{
        return strcmp(s1, s2) == 0;
}
