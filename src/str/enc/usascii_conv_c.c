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
 * encoding C String (C).
 */

#include "../enc.h"
#include "../converr.h"

#define USASCII_MAXIMUM 127

enum str_conv_error str_conv_usascii_c(
        struct str_buffer in,
        struct str_buffer *out,
        size_t *off
)
{
        unsigned char inC;
        char outC;
        int fnd;
        if (in.size < 1)
                return STR_CONV_ERR_INCOMP;
        *off = 1;
        inC = ((unsigned char*)in.buffer)[0];
        if (inC > USASCII_MAXIMUM)
                return STR_CONV_ERR_BAD;

        fnd = 1;
        switch (inC) {
                case 0x41: {outC = 'A'; break;}
                case 0x42: {outC = 'B'; break;}
                case 0x43: {outC = 'C'; break;}
                case 0x44: {outC = 'D'; break;}
                case 0x45: {outC = 'E'; break;}
                case 0x46: {outC = 'F'; break;}
                case 0x47: {outC = 'G'; break;}
                case 0x48: {outC = 'H'; break;}
                case 0x49: {outC = 'I'; break;}
                case 0x4a: {outC = 'J'; break;}
                case 0x4b: {outC = 'K'; break;}
                case 0x4c: {outC = 'L'; break;}
                case 0x4d: {outC = 'M'; break;}
                case 0x4e: {outC = 'N'; break;}
                case 0x4f: {outC = 'O'; break;}
                case 0x50: {outC = 'P'; break;}
                case 0x51: {outC = 'Q'; break;}
                case 0x52: {outC = 'R'; break;}
                case 0x53: {outC = 'S'; break;}
                case 0x54: {outC = 'T'; break;}
                case 0x55: {outC = 'U'; break;}
                case 0x56: {outC = 'V'; break;}
                case 0x57: {outC = 'W'; break;}
                case 0x58: {outC = 'X'; break;}
                case 0x59: {outC = 'Y'; break;}
                case 0x5a: {outC = 'Z'; break;}
                case 0x61: {outC = 'a'; break;}
                case 0x62: {outC = 'b'; break;}
                case 0x63: {outC = 'c'; break;}
                case 0x64: {outC = 'd'; break;}
                case 0x65: {outC = 'e'; break;}
                case 0x66: {outC = 'f'; break;}
                case 0x67: {outC = 'g'; break;}
                case 0x68: {outC = 'h'; break;}
                case 0x69: {outC = 'i'; break;}
                case 0x6a: {outC = 'j'; break;}
                case 0x6b: {outC = 'k'; break;}
                case 0x6c: {outC = 'l'; break;}
                case 0x6d: {outC = 'm'; break;}
                case 0x6e: {outC = 'n'; break;}
                case 0x6f: {outC = 'o'; break;}
                case 0x70: {outC = 'p'; break;}
                case 0x71: {outC = 'q'; break;}
                case 0x72: {outC = 'r'; break;}
                case 0x73: {outC = 's'; break;}
                case 0x74: {outC = 't'; break;}
                case 0x75: {outC = 'u'; break;}
                case 0x76: {outC = 'v'; break;}
                case 0x77: {outC = 'w'; break;}
                case 0x78: {outC = 'x'; break;}
                case 0x79: {outC = 'y'; break;}
                case 0x7a: {outC = 'z'; break;}
                case 0x30: {outC = '0'; break;}
                case 0x31: {outC = '1'; break;}
                case 0x32: {outC = '2'; break;}
                case 0x33: {outC = '3'; break;}
                case 0x34: {outC = '4'; break;}
                case 0x35: {outC = '5'; break;}
                case 0x36: {outC = '6'; break;}
                case 0x37: {outC = '7'; break;}
                case 0x38: {outC = '8'; break;}
                case 0x39: {outC = '9'; break;}
                case 0x21: {outC = '!'; break;}
                case 0x22: {outC = '\"'; break;}
                case 0x23: {outC = '#'; break;}
                case 0x25: {outC = '%'; break;}
                case 0x26: {outC = '&'; break;}
                case 0x27: {outC = '\''; break;}
                case 0x28: {outC = '('; break;}
                case 0x29: {outC = ')'; break;}
                case 0x2a: {outC = '*'; break;}
                case 0x2b: {outC = '+'; break;}
                case 0x2c: {outC = ','; break;}
                case 0x2d: {outC = '-'; break;}
                case 0x2e: {outC = '.'; break;}
                case 0x2f: {outC = '/'; break;}
                case 0x3b: {outC = ';'; break;}
                case 0x3c: {outC = '<'; break;}
                case 0x3d: {outC = '='; break;}
                case 0x3e: {outC = '>'; break;}
                case 0x3f: {outC = '?'; break;}
                case 0x5b: {outC = '['; break;}
                case 0x5c: {outC = '\\'; break;}
                case 0x5d: {outC = ']'; break;}
                case 0x5e: {outC = '^'; break;}
                case 0x5f: {outC = '_'; break;}
                case 0x7b: {outC = '{'; break;}
                case 0x7c: {outC = '|'; break;}
                case 0x7d: {outC = '}'; break;}
                case 0x7e: {outC = '~'; break;}
                case 0x20: {outC = ' '; break;}
                case 0x3a: {outC = ':'; break;}
                case 0x9: {outC = '\t'; break;}
                case 0xb: {outC = '\v'; break;}
                case 0xc: {outC = '\f'; break;}
                case 0x7: {outC = '\a'; break;}
                case 0x8: {outC = '\b'; break;}
                case 0xd: {outC = '\r'; break;}
                case 0xa: {outC = '\n'; break;}
                case 0x0: {outC = '\0'; break;}
                default: {fnd = 0; break;}
        }
        if (!fnd)
                return STR_CONV_ERR_NOEQ;
        ((char*)(out->buffer))[0] = outC;
        out->size = sizeof(char);
        return STR_CONV_ERR_OK;
}
