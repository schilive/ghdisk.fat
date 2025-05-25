/*
MIT License

Copyright (c) 2025 Gabriel Silva Schilive <schilive100@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/* This implements 'print.h'. */

#include <stdio.h>
#include <stddef.h>
#include <limits.h>
#include "print.h"
#include "sysstr.h"

static void print_sizet(char *buf, size_t n)
{
        /* This is guaranteed to work by the ISO C89 standard. Believe it. */
        if (n <= INT_MAX) {
                printf("%.*s", (int)n, buf);
                return;
        }
        while (n != 0) {
                int toW = n > INT_MAX ? INT_MAX : (int)n;
                printf("%.*s", toW, buf);
                n -= toW;
                buf += toW;
        }
}

void print(struct str s)
{
        if (s.encoding == STR_ENC(FIL)) {
                print_sizet(s.buffer.buffer, s.buffer.size);
                return;
        }

        while (s.buffer.size != 0) {
                char bufArr[STR_SZMAX(FIL)];
                enum str_conv_error err;
                struct str_buffer buf;
                size_t off;
                buf.buffer = bufArr;
                err = str_conv(s, STR_ENC(FIL), &buf, &off);
                /* assert(buf.size <= STR_SZMAX(FIL)) */
                /* assert(off <= buf.size) */
                if (err != STR_CONV_ERR_OK) {
                        struct str_buffer unk = STR_UNKCH(FIL);
                        print_sizet(unk.buffer, unk.size);
                } else {
                        print_sizet(buf.buffer, buf.size);
                }
                s.buffer.buffer = (char*)(s.buffer.buffer) + off;
                s.buffer.size -= off;
        }
}
