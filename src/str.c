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

/* This implements the user-level and system-level interface. */

#include "str.h"
#include "sysstr.h"
#include "str/common.h"

struct str str_make(void *s, enum str_encoding e, size_t sz)
{
        struct str r;
        r.string = s;
        r.encoding = e;
        r.size = sz;
        return r;
}

enum str_conv_error str_conv(
        struct str s,
        enum str_encoding toE,
        void *r,
        size_t *off,
        size_t *sz
)
{
        /* assert(s.encoding != toE) */
        /* assert(s.encoding == STR_ENC(TRN)) */
        /* assert(toE == STR_ENC(FIL)) */
#if STR_ENC_V(TRN) == STR_ENC_V(FIL)
        /* assert(0) */
        return 0;
#else
#if STR_ENC_V(TRN) == STR_ENC_V(NRM) && STR_ENC_V(NRM) != STR_ENC_V(FIL)
        return STR_CONV(TRN, FIL)(s, r, off, sz);
#endif
#if STR_ENC_V(TRN) != STR_ENC_V(NRM) && STR_ENC_V(NRM) == STR_ENC_V(FIL)
        return STR_CONV(TRN, NRM)(s, r, off, sz);
#endif
#if STR_ENC_V(TRN) != STR_ENC_V(NRM) && STR_ENC_V(NRM) != STR_ENC_V(FIL)
        struct str nrm;
        char nrmBuf[STR_SZMAX(NRM)];
        enum str_conv_error err;
        size_t nrmOff;
        nrm.string = nrmBuf;
        err = STR_CONV(TRN, NRM)(s, nrm.string, off, &(nrm.size));
        if (err != STR_CONV_ERR_OK)
                return err;
        /* assert(nrm.size <= STR_SZMAX(NRM) */

        nrm.encoding = STR_ENC(NRM);
        err = STR_CONV(NRM, FIL)(nrm, r, &nrmOff, sz);
        if (err != STR_CONV_ERR_OK)
                return err;
        /* assert(nrmOff == nrm.size) */
        /* assert(sz <= STR_SZMAX(FIL)) */
        return err;
#endif
#endif
}
