# What is ghdisk.fat?

The tool 'ghdisk.fat' is a tool to read, edit and create file images (possibly
devices, too) formatted with the FAT filesystem. It supports FAT12, FAT16 and
FAT32, but **not exFAT**, because it is a different filesystem. It is meant to
be used for scripting and interactively.

# Licence

The project is licensed under the MIT licence, with a copy on 'LICENCE'.

# Building

The project uses C89/C90/ANSI C, and is build using GNU Make with GNU
extensions. It supports Windows NT (Windows >=2000) and POSIX as host OSes. It
only supports the GCC/Clang compilers.

To build with the default settings, simply use `make`, which will auto-detect
the host OS and build the project into the `build/` directory.

For further information, see 'dev/build.txt'.

## Documentation

An internal, developer-targeted, documentation is available in 'dev/'.
