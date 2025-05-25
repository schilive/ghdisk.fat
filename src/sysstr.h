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

/* This declares the system-level interface of the string and encoding system.
 *
 * Besides the objects below, the following objects are also available, as
 * stated. Their meaning is not given here (for lack of duplication), but can be
 * easily found in the codebase.
 *      - struct str
 *      - struct str_buffer
 *      - STR_ENC(FIL)
 *      - STR_SZMAX(FIL)
 *      - STR_UNKCH(FIL)
 */

#ifndef SYSSTR_H
#define SYSSTR_H

#include <stddef.h>
#include "str/converr.h"
#include "str/str.h"
#include "str/strenc.h"
#include "str/buffer.h"

/* Converts the first character in the string 'in' to the encoding 'toE', and
 * returns it in 'out'.
 * @param       in      The string whose first character, if any, is the object
 *                      of conversion. Its encoding must be different of toE and
 *                      STR_ENC(TRN), otherwise undocumented behaviour may
 *                      happen.
 * @param       toE     The target encoding for the conversion. It must be
 *                      different of in.encoding and STR_ENC(FIL), otherwise
 *                      undocumented behaviour may happen.
 * @param       out     The output of the conversion. The buffer out.buffer is
 *                      where the product is to be stored. The size out.size is
 *                      at most STR_SZMAX(FIL). This is only output if
 *                      STR_CONV_ERR_OK is returned.
 * @param       off     The number of bytes to offset the string buffer so it
 *                      may convert the next character, if any. If none, then
 *                      i.size = off. This is always returned.
 * @return      The error status of the operation.
 * @throws      STR_CONV_ERR_BAD        The object of conversion is malformed
 *                                      for its encoding.
 * @throws      STR_CONV_ERR_INCOMP     The string is too small to form a whole
 *                                      character.
 * @throws      STR_CONV_ERR_NOEQ       The target encoding has not an
 *                                      equivalent character for the object of
 *                                      conversion.
 */
enum str_conv_error str_conv(
        struct str in,
        enum str_encoding toE,
        struct str_buffer *out,
        size_t *off
);

#endif /* SYSSTR_H */
