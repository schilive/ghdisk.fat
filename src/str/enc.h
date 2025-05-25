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

/* This declares the preprocessor macros and objects for each supported
 * encoding. This file is manually edited.
 *
 * Note that the preprocessor macros are defined here, and so may be used as
 * long as this file is included. However, the other objects are simply
 * declared, and so their implementation must be compiled. This is because
 * preprocessor macros and declarations do not increase the space in the end,
 * but implementations do.
 */

#ifndef STR_ENC_H
#define STR_ENC_H

#include <stddef.h>
#include "../common.h"
#include "buffer.h"
#include "converr.h"

/* This macro expands to the declaration of a conversion function, from encoding
 * of internal name 'x' to the encoding of internal name 'y'.
 *
 * It is a bit odd to declare this macro here, considering 'macros.h', but
 * whatever.
 */
#define STR_CONV_DEC(x, y)\
        enum str_conv_error PASTE4(str_conv_, x, _, y)(\
                struct str_buffer in,\
                struct str_buffer *out,\
                size_t *off\
        );

/* The preprocessor macro STR_ID_x, where 'x' is the internal name of the
 * encoding, expands to a number unique between all encodings, which uniquely
 * identifies the encoding 'x'.
 */
#define STR_ID_c        0
#define STR_ID_w        1
#define STR_ID_usascii  2

/* The preprocessor macro STR_SZMAX_x, where 'x' is the internal name of the
 * encoding, expands to the maximum size of a character in the encoding 'x'.
 *
 * The macros must expands to a literal, so that array may be defined with the
 * size. This is in accordance to ISO C89, which does not allow VLAs.
 */
#define STR_SZMAX_c             sizeof(char)
#define STR_SZMAX_w             sizeof(wchar_t)
#define STR_SZMAX_usascii       1

/* The object str_unkch_x, where 'x' is the internal name of the encoding, is
 * the unknown character defined for the encoding 'x'. Some encodings support a
 * character which means "unknown character", like UNICODE.
 *
 * We use 'extern' because, by default, definitions of structures are static
 * (local). This is in opposition to functions, whose definitions are extern
 * (global) by default.
 */
extern struct str_buffer str_unkch_c;
extern struct str_buffer str_unkch_w;
extern struct str_buffer str_unkch_usascii;

/* The function str_sz_x, where 'x' is the internal name of the encoding, is the
 * function that returns the size of the NUL-terminated string (in bytes). This
 * is because different encodings encode the NUL character differently.
 */
size_t str_sz_c(void *s);
size_t str_sz_w(void *s);
size_t str_sz_usascii(void *s);

/* Here, we declare the available conversion functions. They all assume that the
 * output buffer (out.buffer) has the size of at least STR_SZMAX_x, where 'x' is
 * the target encoding.
 */
STR_CONV_DEC(c, usascii)
STR_CONV_DEC(usascii, c)
STR_CONV_DEC(w, usascii)
STR_CONV_DEC(usascii, w)

#endif /* STR_ENC_H */
