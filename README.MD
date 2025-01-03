# What is ghdisk.fat?

A tool to read, modify and create FAT images. It supports FAT12/16 and
FAT32, but not exFAT, since it is a very different filesystem. It can be used
by people and by scripts.

# Licence
This project is entirely licensed under the MIT Licence, with a copy on
"LICENCE.TXT"

# Bulding
The project is written in C89/ANSI C and the tool Makefile is used for
building. It supports UNIX and Windows NT (>=Windows 2000), but only compiler
with GCC syntax, like `clang`. To use the default options, which builds on
directory `build`, simply run the command `make`. The binary's path should
then be `build/ghdisk.fat.exe`.

The following configurations are available:

- `M_HOST_OS = (WIN32 | NIX)`: this will change the choice of tools and
  extensions; for example, `rm` if set as `NIX`, and `DEL` and `.exe` if set
  as `WIN32`.
- `M_TARGET`: the name of the final binary without extension. Extension is
  added anyway. This cannot be easily avoided because GCC has this behaviour.
- `M_BUILD_DIR`: directory used to build everything.

For further information, see `doc/dev.txt`.
