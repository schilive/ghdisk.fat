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

static void print_last_error(void)
{
        DWORD err = GetLastError();
        LPSTR msg;
        DWORD r = FormatMessageA(
                FORMAT_MESSAGE_ALLOCATE_BUFFER
                | FORMAT_MESSAGE_FROM_SYSTEM
                | FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                err,
                0,
                msg,
                0, /* MS docs used 0 in the example */
                NULL
        );
        if (r == 0) {
                sys_prnferr_s("[%a]", 
                        _("Could not get error message from system"));
                return;
        }
        sys_prnferr_s("%a", msg);
        LocalFree(msg);
}

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
                sys_prnferr_ss("%a: %b: ", 
                        _("Fatal error"), 
                        _("Could not get command-line argument")
                );
                print_last_error();
                sys_prnferr("\n");
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
                sys_prnferr_ss("%a: %b: ",
                        _("Fatal error"),
                        _("Could not parse Windows command-line")
                );
                print_last_error();
                sys_prnferr("\n");
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
                                sys_prnferr_ss("%a: %b: ",
                                        _("Fatal error"),
                                        _("Could not convert command-line from UTF-16 to ANSI")
                                );
                                print_last_error();
                                sys_prnferr("\n");
                                ExitProcess(1);
                        }

                        arg2[j] = c2;
                }
                arg2[argLen] = 0;
                off += argLen;
        }
        argv[argc] = NULL;

        r = ghdisk_fat(argc, argv);
        /* Type 'int' in MinGW and MSVC, is 4 bytes, like 'DWORD' */
        ExitProcess((DWORD)r);
}
