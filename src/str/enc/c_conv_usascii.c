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

/* This implements the function 'str_conv_x_y' from the encoding C String (C) to
 * the encoding US-ASCII.
 */

#include "../enc.h"
#include "../converr.h"

enum str_conv_error str_conv_c_usascii(
        struct str_buffer in,
        struct str_buffer *out,
        size_t *off
)
{
        char inC;
        unsigned char outC;
        int fnd;
        if (in.size < sizeof(char))
                return STR_CONV_ERR_INCOMP;
        *off = sizeof(char);
        inC = ((char*)in.buffer)[0];

        fnd = 1;
        switch (inC) {
                case 'A': {outC = 0x41; break;}
                case 'B': {outC = 0x42; break;}
                case 'C': {outC = 0x43; break;}
                case 'D': {outC = 0x44; break;}
                case 'E': {outC = 0x45; break;}
                case 'F': {outC = 0x46; break;}
                case 'G': {outC = 0x47; break;}
                case 'H': {outC = 0x48; break;}
                case 'I': {outC = 0x49; break;}
                case 'J': {outC = 0x4a; break;}
                case 'K': {outC = 0x4b; break;}
                case 'L': {outC = 0x4c; break;}
                case 'M': {outC = 0x4d; break;}
                case 'N': {outC = 0x4e; break;}
                case 'O': {outC = 0x4f; break;}
                case 'P': {outC = 0x50; break;}
                case 'Q': {outC = 0x51; break;}
                case 'R': {outC = 0x52; break;}
                case 'S': {outC = 0x53; break;}
                case 'T': {outC = 0x54; break;}
                case 'U': {outC = 0x55; break;}
                case 'V': {outC = 0x56; break;}
                case 'W': {outC = 0x57; break;}
                case 'X': {outC = 0x58; break;}
                case 'Y': {outC = 0x59; break;}
                case 'Z': {outC = 0x5a; break;}
                case 'a': {outC = 0x61; break;}
                case 'b': {outC = 0x62; break;}
                case 'c': {outC = 0x63; break;}
                case 'd': {outC = 0x64; break;}
                case 'e': {outC = 0x65; break;}
                case 'f': {outC = 0x66; break;}
                case 'g': {outC = 0x67; break;}
                case 'h': {outC = 0x68; break;}
                case 'i': {outC = 0x69; break;}
                case 'j': {outC = 0x6a; break;}
                case 'k': {outC = 0x6b; break;}
                case 'l': {outC = 0x6c; break;}
                case 'm': {outC = 0x6d; break;}
                case 'n': {outC = 0x6e; break;}
                case 'o': {outC = 0x6f; break;}
                case 'p': {outC = 0x70; break;}
                case 'q': {outC = 0x71; break;}
                case 'r': {outC = 0x72; break;}
                case 's': {outC = 0x73; break;}
                case 't': {outC = 0x74; break;}
                case 'u': {outC = 0x75; break;}
                case 'v': {outC = 0x76; break;}
                case 'w': {outC = 0x77; break;}
                case 'x': {outC = 0x78; break;}
                case 'y': {outC = 0x79; break;}
                case 'z': {outC = 0x7a; break;}
                case '0': {outC = 0x30; break;}
                case '1': {outC = 0x31; break;}
                case '2': {outC = 0x32; break;}
                case '3': {outC = 0x33; break;}
                case '4': {outC = 0x34; break;}
                case '5': {outC = 0x35; break;}
                case '6': {outC = 0x36; break;}
                case '7': {outC = 0x37; break;}
                case '8': {outC = 0x38; break;}
                case '9': {outC = 0x39; break;}
                case '!': {outC = 0x21; break;}
                case '\"': {outC = 0x22; break;}
                case '#': {outC = 0x23; break;}
                case '%': {outC = 0x25; break;}
                case '&': {outC = 0x26; break;}
                case '\'': {outC = 0x27; break;}
                case '(': {outC = 0x28; break;}
                case ')': {outC = 0x29; break;}
                case '*': {outC = 0x2a; break;}
                case '+': {outC = 0x2b; break;}
                case ',': {outC = 0x2c; break;}
                case '-': {outC = 0x2d; break;}
                case '.': {outC = 0x2e; break;}
                case '/': {outC = 0x2f; break;}
                case ';': {outC = 0x3b; break;}
                case '<': {outC = 0x3c; break;}
                case '=': {outC = 0x3d; break;}
                case '>': {outC = 0x3e; break;}
                case '?': {outC = 0x3f; break;}
                case '[': {outC = 0x5b; break;}
                case '\\': {outC = 0x5c; break;}
                case ']': {outC = 0x5d; break;}
                case '^': {outC = 0x5e; break;}
                case '_': {outC = 0x5f; break;}
                case '{': {outC = 0x7b; break;}
                case '|': {outC = 0x7c; break;}
                case '}': {outC = 0x7d; break;}
                case '~': {outC = 0x7e; break;}
                case ' ': {outC = 0x20; break;}
                case ':': {outC = 0x3a; break;}
                case '\t': {outC = 0x9; break;}
                case '\v': {outC = 0xb; break;}
                case '\f': {outC = 0xc; break;}
                case '\a': {outC = 0x7; break;}
                case '\b': {outC = 0x8; break;}
                case '\r': {outC = 0xd; break;}
                case '\n': {outC = 0xa; break;}
                case '\0': {outC = 0x0; break;}
                default: {fnd = 0; break;}
        }
        if (!fnd)
                return STR_CONV_ERR_BAD;
        ((unsigned char*)(out->buffer))[0] = outC;
        out->size = 1;
        return STR_CONV_ERR_OK;
}
