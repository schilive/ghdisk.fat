# What is ghdisk.fat?

A tool to read, modify and create FAT images. It supports FAT12/16 and
FAT32, but not exFAT, since it is a very different filesystem. It can be used
by people and by scripts.

# Licence
This project is entirely licensed under the MIT Licence, with a copy on
"LICENCE.TXT"

# Bulding
The project is written in C89/ANSI C, the building tool used is Makefile with
GNU extensions. It auto-detects the current OS, supporting to build on UNIX and
Windows NT (>= Windows 2000). It supports GCC-like syntax and MSVC-like syntax.

To build with the default configurations, use just `make`, which will build into
the directory `build/`, using GCC without debug or optimisation flags.

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
- `M_DEBUG [= 0]`: if non-0, then it adds the debug flag when compiling and
  linking.

- `M_CC [= gcc | cl]`: the C compiler. If `M_COMPILER_MSVC` is set, the default
  value is `cl`, otherwise it is `gcc`.
- `M_LD [= LINK]`: the linker, only used if `M_COMPILER_MSVC` is set.
- `M_CFLAGS [= -Wall -Wextra -pedantic | /Wall]`: the compiler flags used when
  `M_CC` is used.

For further information, see `doc/dev.txt`.
