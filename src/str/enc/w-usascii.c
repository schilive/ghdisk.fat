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

/* This declares the objects to convert from the encoding Wide String (w) to the
 * encoding US-ASCII.
 */

#include "../common.h"
#include <stddef.h>

enum str_conv_error str_conv_w_usascii(
        struct str s,
        void *r,
        size_t *off,
        size_t *size
)
{
        wchar_t in;
        unsigned char out;
        int fnd;
        if (s.size < sizeof(wchar_t))
                return STR_CONV_ERR_INCOMP;
        in = ((wchar_t*)(s.string))[0];
        *off = sizeof(wchar_t);

        fnd = 1;
        switch (in) {
                case L'A': {out = 65; break;}
                case L'B': {out = 66; break;}
                case L'C': {out = 67; break;}
                case L'D': {out = 68; break;}
                case L'E': {out = 69; break;}
                case L'F': {out = 70; break;}
                case L'G': {out = 71; break;}
                case L'H': {out = 72; break;}
                case L'I': {out = 73; break;}
                case L'J': {out = 74; break;}
                case L'K': {out = 75; break;}
                case L'L': {out = 76; break;}
                case L'M': {out = 77; break;}
                case L'N': {out = 78; break;}
                case L'O': {out = 79; break;}
                case L'P': {out = 80; break;}
                case L'Q': {out = 81; break;}
                case L'R': {out = 82; break;}
                case L'S': {out = 83; break;}
                case L'T': {out = 84; break;}
                case L'U': {out = 85; break;}
                case L'V': {out = 86; break;}
                case L'W': {out = 87; break;}
                case L'X': {out = 88; break;}
                case L'Y': {out = 89; break;}
                case L'Z': {out = 90; break;}
                case L'a': {out = 97; break;}
                case L'b': {out = 98; break;}
                case L'c': {out = 99; break;}
                case L'd': {out = 100; break;}
                case L'e': {out = 101; break;}
                case L'f': {out = 102; break;}
                case L'g': {out = 103; break;}
                case L'h': {out = 104; break;}
                case L'i': {out = 105; break;}
                case L'j': {out = 106; break;}
                case L'k': {out = 107; break;}
                case L'l': {out = 108; break;}
                case L'm': {out = 109; break;}
                case L'n': {out = 110; break;}
                case L'o': {out = 111; break;}
                case L'p': {out = 112; break;}
                case L'q': {out = 113; break;}
                case L'r': {out = 114; break;}
                case L's': {out = 115; break;}
                case L't': {out = 116; break;}
                case L'u': {out = 117; break;}
                case L'v': {out = 118; break;}
                case L'w': {out = 119; break;}
                case L'x': {out = 120; break;}
                case L'y': {out = 121; break;}
                case L'z': {out = 122; break;}
                case L'0': {out = 48; break;}
                case L'1': {out = 49; break;}
                case L'2': {out = 50; break;}
                case L'3': {out = 51; break;}
                case L'4': {out = 52; break;}
                case L'5': {out = 53; break;}
                case L'6': {out = 54; break;}
                case L'7': {out = 55; break;}
                case L'8': {out = 56; break;}
                case L'9': {out = 57; break;}
                case L'!': {out = 33; break;}
                case L'\"': {out = 34; break;}
                case L'#': {out = 35; break;}
                case L'%': {out = 37; break;}
                case L'&': {out = 38; break;}
                case L'\'': {out = 39; break;}
                case L'(': {out = 40; break;}
                case L')': {out = 41; break;}
                case L'*': {out = 42; break;}
                case L'+': {out = 43; break;}
                case L',': {out = 44; break;}
                case L'-': {out = 45; break;}
                case L'.': {out = 46; break;}
                case L'/': {out = 47; break;}
                case L';': {out = 59; break;}
                case L'<': {out = 60; break;}
                case L'=': {out = 61; break;}
                case L'>': {out = 62; break;}
                case L'?': {out = 63; break;}
                case L'[': {out = 91; break;}
                case L'\\': {out = 92; break;}
                case L']': {out = 93; break;}
                case L'^': {out = 94; break;}
                case L'_': {out = 95; break;}
                case L'{': {out = 123; break;}
                case L'|': {out = 124; break;}
                case L'}': {out = 125; break;}
                case L'~': {out = 126; break;}
                case L' ': {out = 32; break;}
                case L':': {out = 58; break;}
                case L'\t': {out = 9; break;}
                case L'\v': {out = 11; break;}
                case L'\f': {out = 12; break;}
                case L'\a': {out = 7; break;}
                case L'\b': {out = 8; break;}
                case L'\r': {out = 13; break;}
                case L'\n': {out = 10; break;}
                case L'\0': {out = 0; break;}
                default: {fnd = 0; break;}
        }
        if (!fnd)
                return STR_CONV_ERR_BAD;
        *size = 1;
        ((unsigned char*)(r))[0] = out;
        return STR_CONV_ERR_OK;
}
