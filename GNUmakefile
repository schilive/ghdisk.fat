# All variables/options are prefixed with an uppercase letter then "_", then
# their name. Each prefix has a meaning, specified in the following list.
#
#  - M_: Option, that may be set by the "builder".
#  - C_: A variable of constant value. Change at your own risk.
#  - V_: A variable set internally. Do not change externally.
#
#  All macro starts with the prefix 'fn_'.
#

####
#### 1. Settings
####

###
### 1.1. OS Settings
###

C_SRC_DIR = src/

M_HOST_OS ?=
ifeq ($(M_HOST_OS),)
    $(info Info: The option 'M_HOST_OS' is unset. Trying to auto-detect)
    ifeq ($(OS),Windows_NT)
        M_HOST_OS = winnt
        $(info Info: Auto-detected Windows NT: 'M_HOST_OS' set to 'winnt')
    else
    ifneq ($(shell uname),)
        M_HOST_OS = posix
        $(info Info: Auto-detected POSIX: 'M_HOST_OS' set to 'posix')
    else
        $(error Error: Could not auto-detect host OS)
endif
endif
endif
ifneq ($(M_HOST_OS),winnt)
ifneq ($(M_HOST_OS),posix)
    $(error Error: Value of 'M_HOST_OS' is invalid: "$(M_HOST_OS)". Unsupported host OS)
endif
endif
ifeq ($(M_TARGET_OS),)
    $(info Info: The option 'M_TARGET_OS' is unset. Setting to 'M_HOST_OS': '$(M_HOST_OS)')
    M_TARGET_OS ?= $(M_HOST_OS)
endif
ifneq ($(M_TARGET_OS),winnt)
ifneq ($(M_TARGET_OS),posix)
    $(error Error: Value of 'M_TARGET_OS' is invalid: "$(M_TARGET_OS)". Unsupported host OS)
endif
endif

ifeq ($(M_TARGET_OS),winnt)
    M_E ?= .exe
else
ifeq ($(M_TARGET_OS),posix)
    M_E ?=
endif
endif

###
### 1.2. Compiler
###

M_COMPILER ?= gcc
ifneq ($(M_COMPILER),gcc)
ifneq ($(M_COMPILER),msvc)
    $(error Error: Value of 'M_COMPILER' in invalid: "$(M_COMPILER)".\
        Unsupported compiler command-line syntax)
endif
endif

ifeq ($(M_COMPILER),gcc)
    M_CC ?= gcc
    M_LD ?= $(M_CC)
    M_O ?= .o
    M_CFLAGS ?= -Wall -Wextra -pedantic -std=c89
else
ifeq ($(M_COMPILER),msvc)
    M_CC ?= cl
    M_LD ?= LINK
    M_O ?= .obj
    M_CFLAGS ?= /Wall
endif
endif

###
### 1.3. Etc.
###

M_TARGET ?= ghdisk.fat
M_BUILD_DIR ?= build

####
#### 2. Macros
####

###
### 2.1. OS-Specific
###

# Creates a directory if it already does not exist. If it could not create the
# directory, it logs and returns an error. It allows to define a directory in a
# tree (a/b/c). The character "/" on Windows is replaced to "\".
#
# Usage: <dir/dirs>
ifeq ($(M_HOST_OS),winnt)
    define fn_fmkdir
        IF NOT EXIST "$(subst /,\,$(1))" (MD "$(subst /,\,$(1))")\
        ELSE IF NOT EXIST "$(subst /,\,$(1))\\" (\
            ECHO.Error: file "$(subst /,\,$(1))" is not a directory >&2\
            & EXIT /B 1\
        )
    endef
else
ifeq ($(M_HOST_OS),posix)
    define fn_fmkdir
        if ! [ -e $(1) ]; then\
            mkdir -p $(1);\
        elif ! [ -d $(1) ]; then\
            echo "Error: file '$(1)' is not a directory" >&2;\
            exit 1;\
        fi
    endef
endif
endif

# Deletes file and subdirectories. Does not return error.
# Usage <file/dir>
ifeq ($(M_HOST_OS),winnt)
    define fn_rmdir
        -DEL /S /Q $(1)
        -RD /S /Q $(1)
    endef
else
ifeq ($(M_HOST_OS),posix)
    define fn_rmdir
        rm -rf $(1)
    endef
endif
endif

###
### 2.2. Compiler-Specific
###

# Compiles $(1) to object file $(2)
# Usage <C source file, Output file>
ifeq ($(M_COMPILER),gcc)
    define fn_c_to_o
        $(M_CC) $(M_CFLAGS) $(M_ACFLAGS) -c -o $(2) $(1)
    endef
else
ifeq ($(M_COMPILER),msvc)
    define fn_c_to_o
        $(M_CC) $(M_CFLAGS) $(M_ACFLAGS) /c /Fo:$(2) $(1)
    endef
endif
endif

# Links $(1) to executable file $(2)
# Usage <Object file(s), Output file>
ifeq ($(M_COMPILER),gcc)
    define fn_o_to_out
        $(M_LD) -o $(2) $(1) $(M_LDFLAGS)
    endef
else
ifeq ($(M_COMPILER),msvc)
    define fn_o_to_out
        $(M_LD) $(M_LDFLAGS) /OUT:$(2) $(1)
    endef
endif
endif
        
####
#### 3. Targets
####

build: $(M_BUILD_DIR)/$(M_TARGET)$(M_E)

$(M_BUILD_DIR)/$(M_TARGET)$(M_E): $(M_BUILD_DIR)/ghdisk.fat$(M_O) | build_dir
	$(call fn_o_to_out,$^,$@)

$(M_BUILD_DIR)/ghdisk.fat$(M_O): $(C_SRC_DIR)/ghdisk.fat.c | build_dir
	$(call fn_c_to_o,$^,$@)

build_dir:
	$(call fn_fmkdir,$(M_BUILD_DIR))

clean:
	$(call fn_rmdir,$(M_BUILD_DIR))

re: clean build

.PHONY: build clean re build_dir
