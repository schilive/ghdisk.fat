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

/* This defines the enumerator 'enum str_encoding'. */

#ifndef STR_STRENC_H
#define STR_STRENC_H

#include "macros.h"

/* We do all this because we cannot give two enumerators with the same name, so
 * we need some preprocessor trickery.
 */
enum str_encoding {
        STR_ENC(TRN)
#if STR_ID(NRM) != STR_ID(TRN)
        ,STR_ENC(NRM)
#endif
#if STR_ID(FIL) != STR_ID(TRN) && STR_ID(FIL) != STR_ID(NRM)
        ,STR_ENC(FIL)
#endif
};

#endif /* STR_STRENC_H */
