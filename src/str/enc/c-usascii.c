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

/* This declares the objects to convert from the encoding C to the encoding
 * US-ASCII
 */

#include "../common.h"
#include <stddef.h>

enum str_conv_error str_conv_c_usascii(
        struct str s,
        void *r,
        size_t *off,
        size_t *size
)
{
        char in;
        unsigned char out;
        int fnd;
        if (s.size < sizeof(char))
                return STR_CONV_ERR_INCOMP;
        in = ((char*)(s.string))[0];
        *off = sizeof(char);

        fnd = 1;
        switch (in) {
                case 'A': {out = 65; break;}
                case 'B': {out = 66; break;}
                case 'C': {out = 67; break;}
                case 'D': {out = 68; break;}
                case 'E': {out = 69; break;}
                case 'F': {out = 70; break;}
                case 'G': {out = 71; break;}
                case 'H': {out = 72; break;}
                case 'I': {out = 73; break;}
                case 'J': {out = 74; break;}
                case 'K': {out = 75; break;}
                case 'L': {out = 76; break;}
                case 'M': {out = 77; break;}
                case 'N': {out = 78; break;}
                case 'O': {out = 79; break;}
                case 'P': {out = 80; break;}
                case 'Q': {out = 81; break;}
                case 'R': {out = 82; break;}
                case 'S': {out = 83; break;}
                case 'T': {out = 84; break;}
                case 'U': {out = 85; break;}
                case 'V': {out = 86; break;}
                case 'W': {out = 87; break;}
                case 'X': {out = 88; break;}
                case 'Y': {out = 89; break;}
                case 'Z': {out = 90; break;}
                case 'a': {out = 97; break;}
                case 'b': {out = 98; break;}
                case 'c': {out = 99; break;}
                case 'd': {out = 100; break;}
                case 'e': {out = 101; break;}
                case 'f': {out = 102; break;}
                case 'g': {out = 103; break;}
                case 'h': {out = 104; break;}
                case 'i': {out = 105; break;}
                case 'j': {out = 106; break;}
                case 'k': {out = 107; break;}
                case 'l': {out = 108; break;}
                case 'm': {out = 109; break;}
                case 'n': {out = 110; break;}
                case 'o': {out = 111; break;}
                case 'p': {out = 112; break;}
                case 'q': {out = 113; break;}
                case 'r': {out = 114; break;}
                case 's': {out = 115; break;}
                case 't': {out = 116; break;}
                case 'u': {out = 117; break;}
                case 'v': {out = 118; break;}
                case 'w': {out = 119; break;}
                case 'x': {out = 120; break;}
                case 'y': {out = 121; break;}
                case 'z': {out = 122; break;}
                case '0': {out = 48; break;}
                case '1': {out = 49; break;}
                case '2': {out = 50; break;}
                case '3': {out = 51; break;}
                case '4': {out = 52; break;}
                case '5': {out = 53; break;}
                case '6': {out = 54; break;}
                case '7': {out = 55; break;}
                case '8': {out = 56; break;}
                case '9': {out = 57; break;}
                case '!': {out = 33; break;}
                case '\"': {out = 34; break;}
                case '#': {out = 35; break;}
                case '%': {out = 37; break;}
                case '&': {out = 38; break;}
                case '\'': {out = 39; break;}
                case '(': {out = 40; break;}
                case ')': {out = 41; break;}
                case '*': {out = 42; break;}
                case '+': {out = 43; break;}
                case ',': {out = 44; break;}
                case '-': {out = 45; break;}
                case '.': {out = 46; break;}
                case '/': {out = 47; break;}
                case ';': {out = 59; break;}
                case '<': {out = 60; break;}
                case '=': {out = 61; break;}
                case '>': {out = 62; break;}
                case '?': {out = 63; break;}
                case '[': {out = 91; break;}
                case '\\': {out = 92; break;}
                case ']': {out = 93; break;}
                case '^': {out = 94; break;}
                case '_': {out = 95; break;}
                case '{': {out = 123; break;}
                case '|': {out = 124; break;}
                case '}': {out = 125; break;}
                case '~': {out = 126; break;}
                case ' ': {out = 32; break;}
                case ':': {out = 58; break;}
                case '\t': {out = 9; break;}
                case '\v': {out = 11; break;}
                case '\f': {out = 12; break;}
                case '\a': {out = 7; break;}
                case '\b': {out = 8; break;}
                case '\r': {out = 13; break;}
                case '\n': {out = 10; break;}
                case '\0': {out = 0; break;}
                default: {fnd = 0; break;}
        }
        if (!fnd)
                return STR_CONV_ERR_BAD;
        *size = 1;
        ((unsigned char*)r)[0] = out;
        return STR_CONV_ERR_OK;
}
