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

/* This implements the function 'str_conv_x_y' from the encoding US-ASCII to the
 * encoding Wide String (W).
 */

#include "../enc.h"
#include "../converr.h"

#define USASCII_MAXIMUM 127

enum str_conv_error str_conv_usascii_w(
        struct str_buffer in,
        struct str_buffer *out,
        size_t *off
)
{
        unsigned char inC;
        wchar_t outC;
        int fnd;
        if (in.size < 1)
                return STR_CONV_ERR_INCOMP;
        *off = 1;
        inC = ((unsigned char*)in.buffer)[0];
        if (inC > USASCII_MAXIMUM)
                return STR_CONV_ERR_BAD;

        fnd = 1;
        switch (inC) {
                case 0x41: {outC = L'A'; break;}
                case 0x42: {outC = L'B'; break;}
                case 0x43: {outC = L'C'; break;}
                case 0x44: {outC = L'D'; break;}
                case 0x45: {outC = L'E'; break;}
                case 0x46: {outC = L'F'; break;}
                case 0x47: {outC = L'G'; break;}
                case 0x48: {outC = L'H'; break;}
                case 0x49: {outC = L'I'; break;}
                case 0x4a: {outC = L'J'; break;}
                case 0x4b: {outC = L'K'; break;}
                case 0x4c: {outC = L'L'; break;}
                case 0x4d: {outC = L'M'; break;}
                case 0x4e: {outC = L'N'; break;}
                case 0x4f: {outC = L'O'; break;}
                case 0x50: {outC = L'P'; break;}
                case 0x51: {outC = L'Q'; break;}
                case 0x52: {outC = L'R'; break;}
                case 0x53: {outC = L'S'; break;}
                case 0x54: {outC = L'T'; break;}
                case 0x55: {outC = L'U'; break;}
                case 0x56: {outC = L'V'; break;}
                case 0x57: {outC = L'W'; break;}
                case 0x58: {outC = L'X'; break;}
                case 0x59: {outC = L'Y'; break;}
                case 0x5a: {outC = L'Z'; break;}
                case 0x61: {outC = L'a'; break;}
                case 0x62: {outC = L'b'; break;}
                case 0x63: {outC = L'c'; break;}
                case 0x64: {outC = L'd'; break;}
                case 0x65: {outC = L'e'; break;}
                case 0x66: {outC = L'f'; break;}
                case 0x67: {outC = L'g'; break;}
                case 0x68: {outC = L'h'; break;}
                case 0x69: {outC = L'i'; break;}
                case 0x6a: {outC = L'j'; break;}
                case 0x6b: {outC = L'k'; break;}
                case 0x6c: {outC = L'l'; break;}
                case 0x6d: {outC = L'm'; break;}
                case 0x6e: {outC = L'n'; break;}
                case 0x6f: {outC = L'o'; break;}
                case 0x70: {outC = L'p'; break;}
                case 0x71: {outC = L'q'; break;}
                case 0x72: {outC = L'r'; break;}
                case 0x73: {outC = L's'; break;}
                case 0x74: {outC = L't'; break;}
                case 0x75: {outC = L'u'; break;}
                case 0x76: {outC = L'v'; break;}
                case 0x77: {outC = L'w'; break;}
                case 0x78: {outC = L'x'; break;}
                case 0x79: {outC = L'y'; break;}
                case 0x7a: {outC = L'z'; break;}
                case 0x30: {outC = L'0'; break;}
                case 0x31: {outC = L'1'; break;}
                case 0x32: {outC = L'2'; break;}
                case 0x33: {outC = L'3'; break;}
                case 0x34: {outC = L'4'; break;}
                case 0x35: {outC = L'5'; break;}
                case 0x36: {outC = L'6'; break;}
                case 0x37: {outC = L'7'; break;}
                case 0x38: {outC = L'8'; break;}
                case 0x39: {outC = L'9'; break;}
                case 0x21: {outC = L'!'; break;}
                case 0x22: {outC = L'\"'; break;}
                case 0x23: {outC = L'#'; break;}
                case 0x25: {outC = L'%'; break;}
                case 0x26: {outC = L'&'; break;}
                case 0x27: {outC = L'\''; break;}
                case 0x28: {outC = L'('; break;}
                case 0x29: {outC = L')'; break;}
                case 0x2a: {outC = L'*'; break;}
                case 0x2b: {outC = L'+'; break;}
                case 0x2c: {outC = L','; break;}
                case 0x2d: {outC = L'-'; break;}
                case 0x2e: {outC = L'.'; break;}
                case 0x2f: {outC = L'/'; break;}
                case 0x3b: {outC = L';'; break;}
                case 0x3c: {outC = L'<'; break;}
                case 0x3d: {outC = L'='; break;}
                case 0x3e: {outC = L'>'; break;}
                case 0x3f: {outC = L'?'; break;}
                case 0x5b: {outC = L'['; break;}
                case 0x5c: {outC = L'\\'; break;}
                case 0x5d: {outC = L']'; break;}
                case 0x5e: {outC = L'^'; break;}
                case 0x5f: {outC = L'_'; break;}
                case 0x7b: {outC = L'{'; break;}
                case 0x7c: {outC = L'|'; break;}
                case 0x7d: {outC = L'}'; break;}
                case 0x7e: {outC = L'~'; break;}
                case 0x20: {outC = L' '; break;}
                case 0x3a: {outC = L':'; break;}
                case 0x9: {outC = L'\t'; break;}
                case 0xb: {outC = L'\v'; break;}
                case 0xc: {outC = L'\f'; break;}
                case 0x7: {outC = L'\a'; break;}
                case 0x8: {outC = L'\b'; break;}
                case 0xd: {outC = L'\r'; break;}
                case 0xa: {outC = L'\n'; break;}
                case 0x0: {outC = L'\0'; break;}
                default: {fnd = 0; break;}
        }
        if (!fnd)
                return STR_CONV_ERR_NOEQ;
        ((wchar_t*)(out->buffer))[0] = outC;
        out->size = sizeof(wchar_t);
        return STR_CONV_ERR_OK;
}
