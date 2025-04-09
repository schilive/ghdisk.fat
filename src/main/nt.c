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

/* This implements a direct entry function, that does not initialise the
 * standard library, for Windows NT.
 */

#include <windows.h>
#include "../ghdisk.fat.h"
#include "../sys.h"
#include "../lang.h"

void _start(void)
{
        LPWSTR args;
        int argc;
        LPWSTR *wArgv;
        LPSTR *argv;
        SIZE_T argvSz;
        int i;
        SIZE_T off;
        int r;
        sys_init_console();

        args = GetCommandLineW();
        wArgv = CommandLineToArgvW(args, &argc);
        if (wArgv == NULL) {
                sys_prnferr_ss("%a: %b\n", 
                        _("Fatal error"), 
                        _("Could not get command-line argument")
                );
                ExitProcess(1);
        }

        argvSz = 0;
        for (i = 0; i < argc; i++)
                argvSz += lstrlenW(wArgv[i]);
        argv = LocalAlloc(
                LMEM_FIXED, 
                argvSz
                + (SIZE_T)argc
                + ((SIZE_T)argc + 1)* sizeof(char*)
        );
        if (argv == NULL) {
                sys_prnferr_ss("%a: %b\n",
                        _("Fatal error"),
                        _("Could not parse Windows command-line")
                );
                ExitProcess(1);
        }

        off = 0;
        for (i = 0; i < argc; i++) {
                LPWSTR arg1 = wArgv[i];
                LPSTR arg2 = ((char*)argv + (argc + 1) * sizeof(char*)) + off;
                SIZE_T argLen = lstrlenW(wArgv[i]);
                SIZE_T j;
                argv[i] = arg2;

                for (j = 0; j < argLen; j++) {
                        WCHAR c1 = arg1[j];
                        CHAR c2;
                        CHAR dft = '?';
                        /* ANSI code pages should only use bytes for characters,
                         * nothing multi-byte.
                         */
                        int r = WideCharToMultiByte(
                                CP_ACP,
                                0,
                                &c1,
                                1,
                                &c2,
                                1,
                                &dft,
                                NULL
                        );
                        if (r == 0) {
                                sys_prnferr_ss("%a: %b\n",
                                        _("Fatal error"),
                                        _("Could not convert command-line from UTF-16 to ANSI")
                                );
                                ExitProcess(1);
                        }

                        arg2[j] = c2;
                }
                arg2[argLen] = 0;
                off += argLen;
        }
        argv[argc] = NULL;

        r = ghdisk_fat(argc, argv);
        ExitProcess((DWORD)r);
}
