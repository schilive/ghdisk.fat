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

/* This defines general stuff that being put here is cleaner than put in their
 * own file(s).
 */

#ifndef COMMON_H
#define COMMON_H

/* This macro concatenates the inputs in their given order. */
#define PASTE2(a, b)                    PASTE2_INNER(a, b)
#define PASTE2_INNER(a, b)              a##b
/* This macro concatenates the inputs in their given order. */
#define PASTE3(a, b, c)                 PASTE3_INNER(a, b, c)
#define PASTE3_INNER(a, b, c)           a##b##c
/* This macro concatenates the inputs in their given order. */
#define PASTE4(a, b, c, d)              PASTE4_INNER(a, b, c, d)
#define PASTE4_INNER(a, b, c, d)        a##b##c##d

#endif /* COMMON_H */
