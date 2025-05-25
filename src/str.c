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

/* This implements the implementable objects which are not encoding-specific of
 * the user-level and system-level interface of the string and encoding system.
 */

#include "sysstr.h"
#include <stddef.h>
#include "str/macros.h"
#include "str/buffer.h"
#include "str/converr.h"

/* The function only implements what is strictly necessary. */
enum str_conv_error str_conv(
        struct str in,
        enum str_encoding toE,
        struct str_buffer *out,
        size_t *off
)
{
        /* assert(in.encoding != toE) */
        /* assert(in.encoding == STR_ENC(TRN) */
        /* assert(toE == STR_ENC(FIL) */
#if STR_ID(TRN) == STR_ID(FIL)
        /* We only add this so no compilation error happens. */
        /* assert(0) */
        return STR_CONV_ERR_OK;
#else
#       if STR_ID(TRN) == STR_ID(NRM) && STR_ID(NRM) != STR_ID(FIL)
        return STR_CONV(NRM, FIL)(in.buffer, out, off);
#       endif
#       if STR_ID(TRN) != STR_ID(NRM) && STR_ID(NRM) == STR_ID(FIL)
        return STR_CONV(TRN, NRM)(in.buffer, out, off);
#       endif
#       if STR_ID(TRN) != STR_ID(NRM) && STR_ID(NRM) != STR_ID(FIL)
        char nrmBuf[STR_SZMAX(NRM)];
        struct str_buffer nrm;
        enum str_conv_error err;
        size_t nrmOff;
        nrm.buffer = nrmBuf;
        err = STR_CONV(TRN, NRM)(in.buffer, &nrm, off);
        if (err != STR_CONV_ERR_OK)
                return err;
        /* assert(nrm.size <= STR_SZMAX(NRM) */
        /* assert(off <= in.buffer.size) */

        err = STR_CONV(NRM, FIL)(nrm, out, &nrmOff);
        if (err != STR_CONV_ERR_OK)
                return err;
        /* assert(out->size <= STR_SZMAX(FIL)) */
        /* assert(nrmOff == nrm.size) */
        return err;
#       endif
#endif
}
