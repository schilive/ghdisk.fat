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

/* This is the entry function. */

#include <stdio.h>
#include <string.h>
#include "lang.h"

static void usage(void)
{
        printf(
                "%s: [ops...] <%s> <%s...>\n"
                "\n"
                "%s:\n"
                "        --help, -h      %s.\n"
                "        --version, -v   %s.\n",
                _("Usage"), _("Command"), _("Command args"), _("Commands"),
                _("Displays help message"), _("Displays version")
        );
}

static void version(void)
{
        printf("Version 0.0.0");
}

int main(int argc, char *argv[])
{
        int i;
        int h = 0, v = 0;
        int cmd = -1;
        if (argv[0] == NULL || argv[1] == NULL) {
                usage();
                return 0;
        }

        for (i = 1; argv[i] != NULL; i++) {
                const char *arg = argv[i];
                int opt_long = 0;
                if (arg[0] != '-' || arg[1] == 0) {
                        cmd = i;
                        break;
                }
                opt_long = arg[1] == '-';

                if (opt_long) {
                        if (strcmp(arg, "--help") == 0) {
                                h = 1;
                                continue;
                        }
                        if (strcmp(arg, "--version") == 0) {
                                v = 1;
                                continue;
                        }
                }
                else {
                        int j;
                        for (j = 1; arg[j] != 0; j++) {
                                if (arg[j] == 'h') {
                                        h = 1;
                                        continue;
                                }
                                if (arg[j] == 'v') {
                                        v = 1;
                                        continue;
                                }
                                break;
                        }
                }

                if (h || v)
                        break;

                (void)fprintf(stderr, "%s: %s: '",
                        _("Fatal error"), _("unknown option given"));
                if (opt_long)
                        (void)fprintf(stderr, "%s", arg);
                else
                        (void)fprintf(stderr, "-%c", arg[1]);
                (void)fprintf(stderr, "'\n");
                return 1;
        }

        if (h) {
                usage();
                return 0;
        }
        if (v) {
                version();
                return 0;
        }

        if (cmd == -1)
                goto error_no_command;
        (void)fprintf(stderr,
                        "%s: %s: '%s'\n", 
                        _("Fatal error"), _("unknown command given"), argv[i]
                     );
        return 1;

error_no_command:
        (void)fprintf(stderr, "%s: %s\n",
                _("Fatal error"), _("no command given"));
        return 1;
}
