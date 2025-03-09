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

/* This implements the formatted print functions, using the OS-specific
 * implementation of the print function.
 */

#include <stdio.h>
#include <string.h>
#include "sys.h"

static char g_lower_alphabet[] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'z', 0
};

enum specifier_type {
        SPECIFIER_STRING,
        SPECIFIER_CHAR
};

enum sys_output {
        SYS_OUT_STDOUT,
        SYS_OUT_STDERR
};

struct specifier {
        void *addr;
        enum specifier_type type;
};

static void sys_prn(enum sys_output out, char *cs, size_t n)
{
        if (out == SYS_OUT_STDOUT)
                sys_prnout(cs, n);
        else
                sys_prnerr(cs, n);
}

static void sys_prns(enum sys_output out, char *cs)
{
        sys_prn(out, cs, strlen(cs));
}


/* If 'c' is not a lower-case letter (a-z), then -1 is returned. Otherwise its
 * position minus 1 is returned.
 */
static int get_lower_letter_position(char c)
{
        int i;
        for (i = 0; g_lower_alphabet[i] != 0; i++) {
                if (c == g_lower_alphabet[i])
                        return i;
        }
        return -1;
}

static void print_specifier(enum sys_output out, struct specifier *s)
{
        if (s->type == SPECIFIER_CHAR) {
                sys_prn(out, (char*)s->addr, 1);
                return;
        }
        if (s->type == SPECIFIER_STRING) {
                if (s->addr == NULL) {
                        /* The string "(?null?)" is used instead of "(null)"
                         * because the second can be an actual file on Windows.
                         */
                        sys_prns(out, "(?null?)");
                }
                else {
                        sys_prns(out, (char*)s->addr);
                }
        }
}

static void print_format_string(
        enum sys_output out,
        char *fmt, 
        struct specifier *ss
)
{
        int ssLen = 0;
        struct specifier *s;
        char *c;
        for (s = ss; s->addr != NULL; s++) {
                ssLen++;
        }

        for (c = fmt; *c != 0; c++) {
                int alphPos;

                if (*c != '%') {
                        sys_prn(out, c, 1);
                        continue;
                }
                alphPos = get_lower_letter_position(*(c + 1));
                /* This includes "%%" */
                if (alphPos == -1) {
                        sys_prns(out, "%");
                        continue;
                }

                c++;
                if (alphPos >= ssLen) {
                        sys_prns(out, " ");
                        continue;
                }
                print_specifier(out, ss + alphPos);
        }
}

void sys_prnfout(char *fmt)
{
        struct specifier ss[1];
        ss[0].addr = NULL;
        print_format_string(SYS_OUT_STDOUT, fmt, ss);
}

void sys_prnferr(char *fmt)
{
        struct specifier ss[1];
        ss[0].addr = NULL;
        print_format_string(SYS_OUT_STDERR, fmt, ss);
}

void sys_prnferr_c(char *fmt, char c1)
{
        struct specifier ss[2];
        ss[0].addr = &c1;
        ss[0].type = SPECIFIER_CHAR;
        ss[1].addr = NULL;
        print_format_string(SYS_OUT_STDERR, fmt, ss);
}

void sys_prnferr_s(char *fmt, char *s1)
{
        struct specifier ss[2];
        ss[0].addr = s1;
        ss[0].type = SPECIFIER_STRING;
        ss[1].addr = NULL;
        print_format_string(SYS_OUT_STDERR, fmt, ss);
}

void sys_prnferr_ss(char *fmt, char *s1, char *s2)
{
        struct specifier ss[3];
        ss[0].addr = s1;
        ss[0].type = SPECIFIER_STRING;
        ss[1].addr = s2;
        ss[1].type = SPECIFIER_STRING;
        ss[2].addr = NULL;
        print_format_string(SYS_OUT_STDERR, fmt, ss);
}

void sys_prnferr_sss(char *fmt, char *s1, char *s2, char *s3)
{
        struct specifier ss[5];
        ss[0].addr = s1;
        ss[0].type = SPECIFIER_STRING;
        ss[1].addr = s2;
        ss[1].type = SPECIFIER_STRING;
        ss[2].addr = s3;
        ss[2].type = SPECIFIER_STRING;
        ss[3].addr = NULL;
        print_format_string(SYS_OUT_STDERR, fmt, ss);
}

void sys_prnfout_ssssss(
        char *fmt,
        char *s1,
        char *s2,
        char *s3,
        char *s4,
        char *s5,
        char *s6
)
{
        struct specifier ss[7];
        ss[0].addr = s1;
        ss[0].type = SPECIFIER_STRING;
        ss[1].addr = s2;
        ss[1].type = SPECIFIER_STRING;
        ss[2].addr = s3;
        ss[2].type = SPECIFIER_STRING;
        ss[3].addr = s4;
        ss[3].type = SPECIFIER_STRING;
        ss[4].addr = s5;
        ss[4].type = SPECIFIER_STRING;
        ss[5].addr = s6;
        ss[5].type = SPECIFIER_STRING;
        ss[6].addr = NULL;
        print_format_string(SYS_OUT_STDOUT, fmt, ss);
}
