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

/* This configures the encodings roles.
 *
 * The preprocessor macro STR_x_ENC expands to the internal name of the encoding
 * of the role 'x'.
 */

#ifndef STR_CONF_H
#define STR_CONF_H

/* We set the encoding 'c' as the default, because it is the most neutral
 * option. We chose a default so the program _can_ be compiled without any
 * compilation settings.
 */
#ifdef _G_ENC_TRN
#       define STR_TRN_ENC      _G_ENC_TRN
#else
#       define STR_TRN_ENC      c
#endif
#ifdef _G_ENC_NRM
#       define STR_NRM_ENC      _G_ENC_NRM
#else
#       define STR_NRM_ENC      usascii
#endif
#ifdef _G_ENC_FIL
#       define STR_FIL_ENC      _G_ENC_FIL
#else
#       define STR_FIL_ENC      c
#endif

#endif /* STR_CONF_H */
