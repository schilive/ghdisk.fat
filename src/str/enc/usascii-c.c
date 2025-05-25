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
 * encoding C.
 */

#include "../common.h"
#include <stddef.h>

enum str_conv_error str_conv_usascii_c(
        struct str s,
        void *r,
        size_t *off,
        size_t *size
)
{
        unsigned char in;
        char out;
        int fnd;
        if (s.size < 1)
                return STR_CONV_ERR_INCOMP;
        in = ((unsigned char*)(s.string))[0];
        *off = 1;

        fnd = 1;
        switch (in) {
                case 65: {out = 'A'; break;}
                case 66: {out = 'B'; break;}
                case 67: {out = 'C'; break;}
                case 68: {out = 'D'; break;}
                case 69: {out = 'E'; break;}
                case 70: {out = 'F'; break;}
                case 71: {out = 'G'; break;}
                case 72: {out = 'H'; break;}
                case 73: {out = 'I'; break;}
                case 74: {out = 'J'; break;}
                case 75: {out = 'K'; break;}
                case 76: {out = 'L'; break;}
                case 77: {out = 'M'; break;}
                case 78: {out = 'N'; break;}
                case 79: {out = 'O'; break;}
                case 80: {out = 'P'; break;}
                case 81: {out = 'Q'; break;}
                case 82: {out = 'R'; break;}
                case 83: {out = 'S'; break;}
                case 84: {out = 'T'; break;}
                case 85: {out = 'U'; break;}
                case 86: {out = 'V'; break;}
                case 87: {out = 'W'; break;}
                case 88: {out = 'X'; break;}
                case 89: {out = 'Y'; break;}
                case 90: {out = 'Z'; break;}
                case 97: {out = 'a'; break;}
                case 98: {out = 'b'; break;}
                case 99: {out = 'c'; break;}
                case 100: {out = 'd'; break;}
                case 101: {out = 'e'; break;}
                case 102: {out = 'f'; break;}
                case 103: {out = 'g'; break;}
                case 104: {out = 'h'; break;}
                case 105: {out = 'i'; break;}
                case 106: {out = 'j'; break;}
                case 107: {out = 'k'; break;}
                case 108: {out = 'l'; break;}
                case 109: {out = 'm'; break;}
                case 110: {out = 'n'; break;}
                case 111: {out = 'o'; break;}
                case 112: {out = 'p'; break;}
                case 113: {out = 'q'; break;}
                case 114: {out = 'r'; break;}
                case 115: {out = 's'; break;}
                case 116: {out = 't'; break;}
                case 117: {out = 'u'; break;}
                case 118: {out = 'v'; break;}
                case 119: {out = 'w'; break;}
                case 120: {out = 'x'; break;}
                case 121: {out = 'y'; break;}
                case 122: {out = 'z'; break;}
                case 48: {out = '0'; break;}
                case 49: {out = '1'; break;}
                case 50: {out = '2'; break;}
                case 51: {out = '3'; break;}
                case 52: {out = '4'; break;}
                case 53: {out = '5'; break;}
                case 54: {out = '6'; break;}
                case 55: {out = '7'; break;}
                case 56: {out = '8'; break;}
                case 57: {out = '9'; break;}
                case 33: {out = '!'; break;}
                case 34: {out = '\"'; break;}
                case 35: {out = '#'; break;}
                case 37: {out = '%'; break;}
                case 38: {out = '&'; break;}
                case 39: {out = '\''; break;}
                case 40: {out = '('; break;}
                case 41: {out = ')'; break;}
                case 42: {out = '*'; break;}
                case 43: {out = '+'; break;}
                case 44: {out = ','; break;}
                case 45: {out = '-'; break;}
                case 46: {out = '.'; break;}
                case 47: {out = '/'; break;}
                case 59: {out = ';'; break;}
                case 60: {out = '<'; break;}
                case 61: {out = '='; break;}
                case 62: {out = '>'; break;}
                case 63: {out = '?'; break;}
                case 91: {out = '['; break;}
                case 92: {out = '\\'; break;}
                case 93: {out = ']'; break;}
                case 94: {out = '^'; break;}
                case 95: {out = '_'; break;}
                case 123: {out = '{'; break;}
                case 124: {out = '|'; break;}
                case 125: {out = '}'; break;}
                case 126: {out = '~'; break;}
                case 32: {out = ' '; break;}
                case 58: {out = ':'; break;}
                case 9: {out = '\t'; break;}
                case 11: {out = '\v'; break;}
                case 12: {out = '\f'; break;}
                case 7: {out = '\a'; break;}
                case 8: {out = '\b'; break;}
                case 13: {out = '\r'; break;}
                case 10: {out = '\n'; break;}
                case 0: {out = '\0'; break;}
                default: {fnd = 0; break;}
        }
        if (!fnd)
                return STR_CONV_ERR_NOEQ;
        *size = sizeof(char);
        ((char*)(r))[0] = out;
        return STR_CONV_ERR_OK;
}

