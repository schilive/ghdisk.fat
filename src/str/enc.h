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

/* This declares manually the preprocessor objects needed for all supported
 * encodings.
 */

#ifndef STR_ENC_H
#define STR_ENC_H

#include <stddef.h>

/* The following preprocessor macros have a unique number, used to identify if
 * two string encodings are equal, when handling encoding roles.
 */
#define STR_ENC_V_c             0
#define STR_ENC_V_usascii       1
#define STR_ENC_V_w             2

/* The following macros expand to the maximum size, in bytes, of a character in
 * the given encoding.
 */
#define STR_SZMAX_c             sizeof(char)
#define STR_SZMAX_usascii       1
#define STR_SZMAX_w             sizeof(wchar_t)

#endif /* STR_ENC_H */
