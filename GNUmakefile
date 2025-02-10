# All internal variables are prefixed with a letter then "_". The following list
# says the meanings of each prefix.
#
#  - M_: Modifiable by the user.
#  - C_: Constants.
#  - V_: Modifiable only by Makefile.
#
#  Definitions have two prefixes:
#
#  - fn_: Utility macro, OS-specific or tool-specific
#
#  are always written prefixed with "fn_". Their use and
#  implications are explained by a comment directly above them.
#

####
#### 1. Settings
####

###
### 1.1. OS Settings
###

##
## 1.1.1. Identifying Host OS
##

ifndef M_HOST_OS
    $(info Info: No host OS operating system manually given. Auto-detecting.)
ifeq ($(OS),Windows_NT)
    M_HOST_OS := WIN32
    $(info Info: Auto-detected Windows, through %OS%)
else
ifneq ($(shell uname),)
    M_HOST_OS := NIX
    $(info Info: Auto-detected Unix, through 'uname')
else
    $(error Could not auto-detect host operating system)
endif
endif
endif

##
## 1.1.2. Defining OS-specific variables
##

ifeq ($(M_HOST_OS),WIN32)
    V_E := .exe
else
ifeq ($(M_HOST_OS),NIX)
    V_E := 
else
    V_BADOS := 1
endif
endif
$(if $(filter $(V_BADOS),1),$(error M_HOST_OS must be either WIN32 or NIX, not '$(M_HOST_OS)'))

##
## 1.1.3. Defining OS-specific functions
##

# Creates a directory if it already does not exist. If it could not create the
# directory, it logs and returns an error. It allows to define a directory in a
# tree (a/b/c). The character "/" on Windows is replaced to "\".
#
# Usage: <dir/dirs>
ifeq ($(M_HOST_OS),WIN32)
    define fn_fmkdir
        IF NOT EXIST "$(subst /,\,$(1))" (\
            MD "$(subst /,\,$(1))"\
        ) ELSE IF NOT EXIST "$(subst /,\,$(1))" (\
            ECHO Error: file "$(subst /,\,$(1))" is not a directory >&2 & EXIT /B 1\
        )
    endef
else
    define fn_fmkdir
        if ! [ -e $(1) ]; then\
            mkdir -p $(1);\
        elif ! [ -d $(1) ]; then\
            echo "Error: file '$(1)' is not a directory" >&2;\
        exit 1;\
        fi
    endef
endif

# Deletes file and subdirectories. Does not return error.
# Usage <file/dir>
ifeq ($(M_HOST_OS),WIN32)
    define fn_rmdir
        DEL /S /Q $(1)
        @-RD /S /Q $(1)
    endef
else
    define fn_rmdir
        rm -rf $(1)
    endef
endif

# Copies one file to another location.
# Usage: <src> <dest>
ifeq ($(M_HOST_OS),WIN32)
    define fn_copy
        COPY /Y $(subst /,\,$(1)) $(subst /,\,$(2))
    endef
else
    define fn_copy
        cp -rf $(1) $(2)
    endef
endif

# Executes Python with arguments. It seems that on UNIX, the python binary is
# "python3", and on Windows, "python".
# Usage: <arguments>
ifeq ($(M_HOST_OS),WIN32)
    define fn_python
        python $(1)
    endef
else
    define fn_python
        python3 $(1)
    endef
endif

###
### 1.2. File and Directory Settings
###

M_TARGET ?= ghdisk.fat
M_BUILD_DIR ?= build
C_SRC_DIR := src
C_PO_DIR := po

###
### 1.3. Compiler Settings
###

M_DEBUG ?= 0

M_COMPILER_MSVC ?= 0
ifeq ($(M_COMPILER_MSVC),0)
    V_O := .o
    M_CC ?= gcc
    M_CFLAGS ?= -Wall -Wextra -pedantic -std=c89
    ifneq ($(M_DEBUG),0)
        M_CFLAGS += -g
    endif
else
    V_O := .o
    M_CC ?= CL
    M_LD ?= LINK
    M_CFLAGS ?= /Wall
    M_LFLAGS=
    ifneq ($(M_DEBUG),0)
        M_CFLAGS += /DEBUG
	M_LFLAGS += /DEBUG
    endif
endif

##
## 1.3.1. Defining compiler-specific functions
##

# Compiles C source file to an object file. The suffix of the file <output>
# should be $(V_O).
#
# Usage: <input>, <output>
ifeq ($(M_COMPILER_MSVC),0)
    define fn_cc_obj
        $(M_CC) $(M_CFLAGS) -c -o $(2) $(1)
    endef
else
    define fn_cc_obj
        $(M_CC) $(M_CFLAGS) /c /Fo:$(2) $(1)
    endef
endif

# Links one or more object files to an executable. The suffix of the file
# <input> should be $(V_O); and of <output>, $(V_E).
#
# Usage: <input> ..., <output>
ifeq ($(M_COMPILER_MSVC),0)
    define fn_ld_exe
        $(M_CC) $(M_CFLAGS) -o $(2) $(1)
    endef
else
    define fn_ld_exe
        $(M_LD) $(M_LFLAGS) /OUT:$(2) $(1)
    endef
endif

# Executes the processor of a C file. The suffix of the file <input>.
# Usage: <input> <output>
ifeq ($(M_COMPILER_MSVC),0)
    define fn_cc_i
        $(M_CC) $(M_CFLAGS) -E -o $(2) $(1)
    endef
else
    define fn_cc_i
        $(M_CC) $(M_CFLAGS) /P /Fi:$(2) $(1)
    endef
endif

####
#### 2. Targets
####

build: $(M_BUILD_DIR)/$(if $(M_LANG),$(M_LANG)/)$(M_TARGET)$(V_E)

ifeq ($(origin M_LANG),undefined)
$(M_BUILD_DIR)/$(M_TARGET)$(V_E): $(M_BUILD_DIR)/ghdisk.fat$(V_O) | build_dir
	$(call fn_ld_exe,$(word 1,$^),$@)

$(M_BUILD_DIR)/ghdisk.fat$(V_O): $(C_SRC_DIR)/ghdisk.fat.c $(C_SRC_DIR)/lang.h | build_dir
	$(call fn_cc_obj,$(word 1,$^),$@)
else
$(M_BUILD_DIR)/$(M_LANG)/ghdisk.fat$(V_E): $(M_BUILD_DIR)/$(M_LANG)/ghdisk.fat$(V_O) | build_dir
	$(call fn_ld_exe,$(word 1,$^),$@)

$(M_BUILD_DIR)/$(M_LANG)/ghdisk.fat$(V_O): $(M_BUILD_DIR)/$(M_LANG)/ghdisk.fat.c | build_dir
	$(call fn_cc_obj,$(word 1,$^),$@)

$(M_BUILD_DIR)/$(M_LANG)/ghdisk.fat.c: $(M_BUILD_DIR)/ghdisk.fat.c $(C_PO_DIR)/$(M_LANG)/ghdisk.fat.po | build_dir pot_uptodate_ghdisk.fat.c po_uptodate_ghdisk.fat.c_$(M_LANG)
	$(call fn_copy,$(word 1,$^),$@)
	$(call fn_python,lang.py replace_c_file $(word 2,$^) $@)

$(M_BUILD_DIR)/ghdisk.fat.c: $(C_SRC_DIR)/ghdisk.fat.c $(C_SRC_DIR)/lang.h | build_dir
	$(call fn_cc_i,$(word 1,$^),$@)

pot_uptodate_ghdisk.fat.c:
	$(call fn_python,lang.py update_pot $(C_SRC_DIR)/ghdisk.fat.c $(C_PO_DIR)/ghdisk.fat.pot -n)

po_uptodate_ghdisk.fat.c_$(M_LANG):
	$(call fn_python,lang.py update_po $(C_PO_DIR)/ghdisk.fat.pot $(C_PO_DIR)/$(M_LANG)/ghdisk.fat.po -n)

endif

build_dir:
	$(call fn_fmkdir,$(M_BUILD_DIR))
	$(call fn_fmkdir,$(M_BUILD_DIR)/$(M_LANG))

clean:
	$(call fn_rmdir,$(M_BUILD_DIR))

.PHONY: build build_dir clean po_uptodate
