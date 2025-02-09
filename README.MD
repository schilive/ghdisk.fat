# What is ghdisk.fat?

A tool to read, modify and create FAT images. It supports FAT12/16 and
FAT32, but not exFAT, since it is a very different filesystem. It can be used
by people and by scripts.

# Licence
This project is entirely licensed under the MIT Licence, with a copy on
"LICENCE.TXT"

# Building
The project is written in C89/ANSI C, the building tool is GNU Make with
extensions. It auto-detects the host OS, supporting to build on UNIX and Windows
NT (>= Windows 2000). It supports GCC/Clang and MSVC.

To build with the default configurations, use just `make`, which will build into
the directory `build/`, using GCC without debug or optimisation flags.

For further information, see `doc/build.txt`.

# Developer Documentation
It is available on `dev/`.
