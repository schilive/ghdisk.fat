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

/* This declares some helpful macros to access the encoding-specific objects
 * given a role. Helpfully, it also includes the necessary header files to
 * access these objects without further includes.
 *
 * Of course, it does not implement the objects which have to be implemented.
 */

#ifndef STR_MACROS_H
#define STR_MACROS_H

#include "../common.h"
#include "conf.h"
#include "enc.h"

/* This macro expands to the encoding internal name for the role 'x'. The input
 * must be a literal, but not a string; for example, "STR_x_ENC(TRN)".
 */
#define STR_x_ENC(x)    PASTE3(STR_, x, _ENC)

/* This macro expands to 'STR_SZMAX_y', where 'y' is the internal name of the
 * encoding of the role 'x'. The input must be a literal, but not a string; for
 * example, "STR_SZMAX(TRN)".
 */
#define STR_SZMAX(x)    PASTE2(STR_SZMAX_, STR_x_ENC(x))
/* This macro expands to 'STR_ENC_y', where 'y' is the internal name of the
 * encoding of the role 'x'. The input must be a literal, but not a string; for
 * example, "STR_ENC(TRN)".
 */
#define STR_ENC(x)      PASTE2(STR_ENC_, STR_x_ENC(x))
/* This macro expands to 'STR_ID_y', where 'y' is the internal name of the
 * encoding of the role 'x'. The input must be a literal, but not a string; for
 * example, "STR_ID(TRN)".
 */
#define STR_ID(x)       PASTE2(STR_ID_, STR_x_ENC(x))
/* This macro expands to 'str_sz_y', where 'y' is the internal name of the
 * encoding of the role 'x'. The input must be a literal, but not a string; for
 * example, "STR_SZ(TRN)".
 */
#define STR_SZ(x)       PASTE2(str_sz_, STR_x_ENC(x))
/* This macro expands to 'str_conv_z_w', where 'z' is the internal name of the
 * encoding of the role 'x', and 'w' is of the role 'y'. The inputs must be
 * literals, but not strings; for example, "STR_CONV(TRN, NRM)".
 */
#define STR_CONV(x, y)  PASTE4(str_conv_, STR_x_ENC(x), _, STR_x_ENC(y))
/* This macro expands to 'str_unkch_y', where 'y' is the internal name of the
 * encoding of the role 'x'. The input must be a literal, but not a string; for
 * example, "STR_UNKCH(TRN)".
 */
#define STR_UNKCH(x)    PASTE2(str_unkch_, STR_x_ENC(x))

/* We cheat and include it here. */
#include "strenc.h"

#endif /* STR_MACROS_H */

