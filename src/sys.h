/*
MIT License

Copyright (c) 2025 Gabriel Silva Schilive <schilive100@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* This defines an OS-agnostic interface with OS-specific implementation.
 *
 * Before any "system function" is called, the function 'sys_init()' must be
 * called. Not doing so, may end in undefined behaviour or even a sudden error.
 *
 * == Print functions ==
 * The print functions do not use 'printf()' interface, to achieve potential
 * enhancements. Instead of the number of parameters being determined by the
 * content of the format string, it is determined by the function's name. It
 * also always allow NULL as input for pointer inputs. However, usage of bad
 * pointers may still cause an error.
 *
 * Assumptions:
 *        1. Input characters are assumed to be encoded as standard C
 *        characters, through <''> and <"">.
 *        2. The character encoding is a one-byte encoding (e.g. ASCII).
 *        3. The character encoding supports a-z, A-Z, "%" and " " (SP).
 *        4. The term "letter" refers to a-z and A-Z, and no letter is encoded
 *        by 0.
 * Observations:
 *      1. If the function fails internally, nothing is reported and the error
 *      is ignored.
 *
 * The function and its usage is explained below, referencing a table. This
 * table is the last "section" of this text.
 *
 * -- Explanation --
 *
 * The input character encoding should be characters as provided by C, by the
 * use <""> and <''>. It is assumed to be a one-byte--based encoding, instead of
 * double-byte-- or other forms. It is also assumed that the lower-case letters
 * a-z are provided and none are 0; their encoding order is not assumed. When
 * the word "letter" is used, a-z and A-Z is meant.
 *
 * The name of a print function is three texts in series. The first is
 * "sys_prnf", which identifies the function as a print function. The second
 * identifies the output stream; "out" for standard output, and "err" for
 * standard error. The third is optional, its presence and content define
 * the number and type of parameters, and it can make available messages whose
 * content depend on external variables, like "printf"; if present, it is "_"
 * followed by a series of letters. This series is called the "specifiers list",
 * and each letter is called a "specifier". The available specifiers are present
 * in the table, in the column "Letter". When the third text is absent, the list
 * of specifiers is said to be empty.
 *
 * If 'Es' is the length of the specifiers list, the number of parameters in the
 * function is 'Es + 1'. The first parameter is the "format" (abbreviated
 * 'fmt'), which determines what is to be printed. If 2 <= n <= Es, then the
 * type of the n-th parameter is determined only by the letter of the (n-1)-th
 * specifier. Each letter's correspondent type is given in the table, in the
 * column "Type".
 *
 * The format parameter is a series of 2 commands: letter commands and specifier
 * commands. Letter commands are a letter (except 'NUL'), which is ordered to
 * be printed. The specifier command is "%" followed by a lower-case letter, and
 * its order depends on this letter. Let 'pos' be the specifier command's
 * letter's position in the alphabet. If 'pos > Es', then " " (SP) is printed.
 * If 'pos <= Es', then the 'pos'-th letter of the specifiers list identifies
 * what is to be printed, taking the '(pos + 1)'-parameter as input. This is
 * described by the table.
 *
 * -- Table --
 * Letter       Type    Order (input 'i')
 * c            char    The character 'i' is printed as-is, even if NUL.
 * s            char*   The NULL-terminated string 'i' is printed, left-right.
 *
 * == END ==
 *
 */

#ifndef SYS_H
#define SYS_H

/* This function must be called before any other function. It sets the specific
 * system imlementation to an initial known state.
 */
void sys_init(void);

/* Prints to stdout the 'n' first characters of the character array 'cs'. */
void sys_prnout(char *cs, size_t n);

/* Prints to stderr the 'n' first characters of the character array 'cs'. */
void sys_prnerr(char *cs, size_t n);

/* Vide header. */
void sys_prnfout(char *fmt);

/* Vide header. */
void sys_prnferr(char *fmt);

/* Vide header. */
void sys_prnferr_c(char *fmt, char c1);

/* Vide header. */
void sys_prnferr_s(char *fmt, char *s1);

/* Vide header. */
void sys_prnferr_ss(char *fmt, char *s1, char *s2);

/* Vide header. */
void sys_prnferr_sss(char *fmt, char *s1, char *s2, char *s3);

/* Vide header. */
void sys_prnfout_ssssss(
        char *m,
        char *s1,
        char *s2,
        char *s3,
        char *s4,
        char *s5,
        char *s6
);

#endif /* SYS_H */
