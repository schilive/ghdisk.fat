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

/* This declares everything else that needs to be declared for the string and
 * encoding system
 */

#ifndef STR_COMMON_H
#define STR_COMMON_H

#include <stddef.h>
#include "enc.h"
#include "conf.h"
#include "../common.h"

#define STR_x_ENC(x)            PASTE3(STR_, x, _ENC)

#define STR_ENC_V(x)    PASTE2(STR_ENC_V_,      STR_x_ENC(x))
#define STR_ENC(x)      PASTE2(STR_ENC_,        STR_x_ENC(x))
#define STR_SZMAX(x)    PASTE2(STR_SZMAX_,      STR_x_ENC(x))
#define STR_SZ(x)       PASTE2(str_sz_,         STR_x_ENC(x))
#define STR_UNKCH(x)    PASTE2(str_unkch_,      STR_x_ENC(x))

#define STR_CONV(x, y)  PASTE4(str_conv_, STR_x_ENC(x), _, STR_x_ENC(y))
#define STR_CONV_DEF(x, y)\
        enum str_conv_error STR_CONV(x, y)(\
                struct str s,\
                void *r,\
                size_t *off,\
                size_t *sz\
        );

enum str_conv_error {
        STR_CONV_ERR_OK,
        STR_CONV_ERR_BAD,
        STR_CONV_ERR_INCOMP,
        STR_CONV_ERR_NOEQ
};

enum str_encoding {
        STR_ENC(TRN)
#if STR_ENC_V(NRM) != STR_ENC_V(TRN)
        ,STR_ENC(NRM)
#endif
#if STR_ENC_V(FIL) != STR_ENC_V(TRN) && STR_ENC_V(FIL) != STR_ENC_V(NRM)
        ,STR_ENC(FIL)
#endif
};

struct str {
        void *string;
        enum str_encoding encoding;
        size_t size;
};

extern struct str STR_UNKCH(FIL);

size_t STR_SZ(TRN)(void *s);
struct str str_make(void *s, enum str_encoding e, size_t sz);

STR_CONV_DEF(TRN, NRM)
STR_CONV_DEF(NRM, FIL)

#endif /* STR_COMMON_H */
