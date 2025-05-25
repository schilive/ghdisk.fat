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

/* This implements the function 'str_conv_x_y' from the encoding Wide String (W)
 * to the encoding US-ASCII.
 */

#include "../enc.h"
#include "../converr.h"

enum str_conv_error str_conv_w_usascii(
        struct str_buffer in,
        struct str_buffer *out,
        size_t *off
)
{
        wchar_t inC;
        unsigned char outC;
        int fnd;
        if (in.size < sizeof(wchar_t))
                return STR_CONV_ERR_INCOMP;
        *off = sizeof(wchar_t);
        inC = ((wchar_t*)in.buffer)[0];

        fnd = 1;
        switch (inC) {
                case L'A': {outC = 0x41; break;}
                case L'B': {outC = 0x42; break;}
                case L'C': {outC = 0x43; break;}
                case L'D': {outC = 0x44; break;}
                case L'E': {outC = 0x45; break;}
                case L'F': {outC = 0x46; break;}
                case L'G': {outC = 0x47; break;}
                case L'H': {outC = 0x48; break;}
                case L'I': {outC = 0x49; break;}
                case L'J': {outC = 0x4a; break;}
                case L'K': {outC = 0x4b; break;}
                case L'L': {outC = 0x4c; break;}
                case L'M': {outC = 0x4d; break;}
                case L'N': {outC = 0x4e; break;}
                case L'O': {outC = 0x4f; break;}
                case L'P': {outC = 0x50; break;}
                case L'Q': {outC = 0x51; break;}
                case L'R': {outC = 0x52; break;}
                case L'S': {outC = 0x53; break;}
                case L'T': {outC = 0x54; break;}
                case L'U': {outC = 0x55; break;}
                case L'V': {outC = 0x56; break;}
                case L'W': {outC = 0x57; break;}
                case L'X': {outC = 0x58; break;}
                case L'Y': {outC = 0x59; break;}
                case L'Z': {outC = 0x5a; break;}
                case L'a': {outC = 0x61; break;}
                case L'b': {outC = 0x62; break;}
                case L'c': {outC = 0x63; break;}
                case L'd': {outC = 0x64; break;}
                case L'e': {outC = 0x65; break;}
                case L'f': {outC = 0x66; break;}
                case L'g': {outC = 0x67; break;}
                case L'h': {outC = 0x68; break;}
                case L'i': {outC = 0x69; break;}
                case L'j': {outC = 0x6a; break;}
                case L'k': {outC = 0x6b; break;}
                case L'l': {outC = 0x6c; break;}
                case L'm': {outC = 0x6d; break;}
                case L'n': {outC = 0x6e; break;}
                case L'o': {outC = 0x6f; break;}
                case L'p': {outC = 0x70; break;}
                case L'q': {outC = 0x71; break;}
                case L'r': {outC = 0x72; break;}
                case L's': {outC = 0x73; break;}
                case L't': {outC = 0x74; break;}
                case L'u': {outC = 0x75; break;}
                case L'v': {outC = 0x76; break;}
                case L'w': {outC = 0x77; break;}
                case L'x': {outC = 0x78; break;}
                case L'y': {outC = 0x79; break;}
                case L'z': {outC = 0x7a; break;}
                case L'0': {outC = 0x30; break;}
                case L'1': {outC = 0x31; break;}
                case L'2': {outC = 0x32; break;}
                case L'3': {outC = 0x33; break;}
                case L'4': {outC = 0x34; break;}
                case L'5': {outC = 0x35; break;}
                case L'6': {outC = 0x36; break;}
                case L'7': {outC = 0x37; break;}
                case L'8': {outC = 0x38; break;}
                case L'9': {outC = 0x39; break;}
                case L'!': {outC = 0x21; break;}
                case L'\"': {outC = 0x22; break;}
                case L'#': {outC = 0x23; break;}
                case L'%': {outC = 0x25; break;}
                case L'&': {outC = 0x26; break;}
                case L'\'': {outC = 0x27; break;}
                case L'(': {outC = 0x28; break;}
                case L')': {outC = 0x29; break;}
                case L'*': {outC = 0x2a; break;}
                case L'+': {outC = 0x2b; break;}
                case L',': {outC = 0x2c; break;}
                case L'-': {outC = 0x2d; break;}
                case L'.': {outC = 0x2e; break;}
                case L'/': {outC = 0x2f; break;}
                case L';': {outC = 0x3b; break;}
                case L'<': {outC = 0x3c; break;}
                case L'=': {outC = 0x3d; break;}
                case L'>': {outC = 0x3e; break;}
                case L'?': {outC = 0x3f; break;}
                case L'[': {outC = 0x5b; break;}
                case L'\\': {outC = 0x5c; break;}
                case L']': {outC = 0x5d; break;}
                case L'^': {outC = 0x5e; break;}
                case L'_': {outC = 0x5f; break;}
                case L'{': {outC = 0x7b; break;}
                case L'|': {outC = 0x7c; break;}
                case L'}': {outC = 0x7d; break;}
                case L'~': {outC = 0x7e; break;}
                case L' ': {outC = 0x20; break;}
                case L':': {outC = 0x3a; break;}
                case L'\t': {outC = 0x9; break;}
                case L'\v': {outC = 0xb; break;}
                case L'\f': {outC = 0xc; break;}
                case L'\a': {outC = 0x7; break;}
                case L'\b': {outC = 0x8; break;}
                case L'\r': {outC = 0xd; break;}
                case L'\n': {outC = 0xa; break;}
                case L'\0': {outC = 0x0; break;}
                default: {fnd = 0; break;}
        }
        if (!fnd)
                return STR_CONV_ERR_BAD;
        ((unsigned char*)(out->buffer))[0] = outC;
        out->size = 1;
        return STR_CONV_ERR_OK;
}
