# What is ghdisk.fat?

A tool to read, modify and create FAT images. It supports FAT12/16 and
FAT32, but not exFAT, since it is a very different filesystem. It can be used
by people and by scripts.

# Licence
This project is entirely licensed under the MIT Licence, with a copy on
"LICENCE.TXT"

# Bulding
The project is written in C89/ANSI C and the tool Makefile with GNU extensions
is used for building. It supports UNIX and Windows NT (>=Windows 2000), and it
compiles with GCC (and GCC-like, like Clang) and additionally MSVC. To use the
default options, which builds on directory `build`, simply run the command
`make`. The binary's path should then be `build/ghdisk.fat.exe`.

The following configurations are available:

- `M_HOST_OS = (WIN32 | NIX)`: this will change the choice of tools and
  extensions; for example, `rm` if set as `NIX`, and `DEL` and `.exe` if set
  as `WIN32`.
- `M_TARGET [= ghdisk.fat]`: the name of the final binary without extension.
  Extension is added anyway. This cannot be easily avoided because GCC has this
  behaviour.
- `M_BUILD_DIR [= build]`: directory used to build everything.
- `M_COMPILER_MSVC [= 0]`: if non-0, it uses the toolchain with MSVC syntax and
  file extensions, and sets the default tools.

- `M_CC [= gcc | cl]`: the C compiler. If `M_COMPILER_MSVC` is set, the default
  value is `cl`, otherwise it is `gcc`.
- `M_LD [= LINK]`: the linker, only used if `M_COMPILER_MSVC` is set.
- `M_CFLAGS [= -Wall -Wextra -pedantic | /Wall]`: the compiler flags used when
  `M_CC` is used.

For further information, see `doc/dev.txt`.
