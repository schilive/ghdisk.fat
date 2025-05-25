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

/* This declares the objects to convert from the encoding US-ASCII to the
 * encoding Wide String (w).
 */

#include "../common.h"
#include <stddef.h>

enum str_conv_error str_conv_usascii_w(
        struct str s,
        void *r,
        size_t *off,
        size_t *size
)
{
        unsigned char in;
        wchar_t out;
        int fnd;
        if (s.size < 1)
                return STR_CONV_ERR_INCOMP;
        in = ((unsigned char*)(s.string))[0];
        *off = 1;

        fnd = 1;
        switch (in) {
                case 65: {out = L'A'; break;}
                case 66: {out = L'B'; break;}
                case 67: {out = L'C'; break;}
                case 68: {out = L'D'; break;}
                case 69: {out = L'E'; break;}
                case 70: {out = L'F'; break;}
                case 71: {out = L'G'; break;}
                case 72: {out = L'H'; break;}
                case 73: {out = L'I'; break;}
                case 74: {out = L'J'; break;}
                case 75: {out = L'K'; break;}
                case 76: {out = L'L'; break;}
                case 77: {out = L'M'; break;}
                case 78: {out = L'N'; break;}
                case 79: {out = L'O'; break;}
                case 80: {out = L'P'; break;}
                case 81: {out = L'Q'; break;}
                case 82: {out = L'R'; break;}
                case 83: {out = L'S'; break;}
                case 84: {out = L'T'; break;}
                case 85: {out = L'U'; break;}
                case 86: {out = L'V'; break;}
                case 87: {out = L'W'; break;}
                case 88: {out = L'X'; break;}
                case 89: {out = L'Y'; break;}
                case 90: {out = L'Z'; break;}
                case 97: {out = L'a'; break;}
                case 98: {out = L'b'; break;}
                case 99: {out = L'c'; break;}
                case 100: {out = L'd'; break;}
                case 101: {out = L'e'; break;}
                case 102: {out = L'f'; break;}
                case 103: {out = L'g'; break;}
                case 104: {out = L'h'; break;}
                case 105: {out = L'i'; break;}
                case 106: {out = L'j'; break;}
                case 107: {out = L'k'; break;}
                case 108: {out = L'l'; break;}
                case 109: {out = L'm'; break;}
                case 110: {out = L'n'; break;}
                case 111: {out = L'o'; break;}
                case 112: {out = L'p'; break;}
                case 113: {out = L'q'; break;}
                case 114: {out = L'r'; break;}
                case 115: {out = L's'; break;}
                case 116: {out = L't'; break;}
                case 117: {out = L'u'; break;}
                case 118: {out = L'v'; break;}
                case 119: {out = L'w'; break;}
                case 120: {out = L'x'; break;}
                case 121: {out = L'y'; break;}
                case 122: {out = L'z'; break;}
                case 48: {out = L'0'; break;}
                case 49: {out = L'1'; break;}
                case 50: {out = L'2'; break;}
                case 51: {out = L'3'; break;}
                case 52: {out = L'4'; break;}
                case 53: {out = L'5'; break;}
                case 54: {out = L'6'; break;}
                case 55: {out = L'7'; break;}
                case 56: {out = L'8'; break;}
                case 57: {out = L'9'; break;}
                case 33: {out = L'!'; break;}
                case 34: {out = L'\"'; break;}
                case 35: {out = L'#'; break;}
                case 37: {out = L'%'; break;}
                case 38: {out = L'&'; break;}
                case 39: {out = L'\''; break;}
                case 40: {out = L'('; break;}
                case 41: {out = L')'; break;}
                case 42: {out = L'*'; break;}
                case 43: {out = L'+'; break;}
                case 44: {out = L','; break;}
                case 45: {out = L'-'; break;}
                case 46: {out = L'.'; break;}
                case 47: {out = L'/'; break;}
                case 59: {out = L';'; break;}
                case 60: {out = L'<'; break;}
                case 61: {out = L'='; break;}
                case 62: {out = L'>'; break;}
                case 63: {out = L'?'; break;}
                case 91: {out = L'['; break;}
                case 92: {out = L'\\'; break;}
                case 93: {out = L']'; break;}
                case 94: {out = L'^'; break;}
                case 95: {out = L'_'; break;}
                case 123: {out = L'{'; break;}
                case 124: {out = L'|'; break;}
                case 125: {out = L'}'; break;}
                case 126: {out = L'~'; break;}
                case 32: {out = L' '; break;}
                case 58: {out = L':'; break;}
                case 9: {out = L'\t'; break;}
                case 11: {out = L'\v'; break;}
                case 12: {out = L'\f'; break;}
                case 7: {out = L'\a'; break;}
                case 8: {out = L'\b'; break;}
                case 13: {out = L'\r'; break;}
                case 10: {out = L'\n'; break;}
                case 0: {out = L'\0'; break;}
                default: {fnd = 0; break;}
        }
        if (!fnd)
                return STR_CONV_ERR_NOEQ;
        *size = sizeof(wchar_t);
        ((wchar_t*)(r))[0] = out;
        return STR_CONV_ERR_OK;
}
