# All variables are prefixed with a letter then "_". The following list says the
# meanings of each prefix.
#
#  - M_: Modifiable by the user.
#  - C_: Constants.
#  - V_: Modifiable only by Makefile.
#
#  Definitions are always written prefixed with "fn_". Their use and
#  implications are explained by a comment directly above them.
#

### Settings ###
## OS Settings ##

M_HOST_OS=
ifeq ($(M_HOST_OS),)
        $(info Info: No host OS operating system manually given. Auto-detecting.)
ifeq ($(OS),Windows_NT)
        M_HOST_OS=WIN32
        $(info Info: Auto-detected Windows, through %OS%)
else
ifneq ($(shell uname),)
        M_HOST_OS=NIX
        $(info Info: Auto-detected Unix, through 'uname')
else
        $(error Could not auto-detect host operating system)
endif
endif
endif

ifeq ($(M_HOST_OS),WIN32)
        V_E=.exe
else
ifeq ($(M_HOST_OS),NIX)
        V_E=
else
        V_BADOS=1
endif
endif
$(if $(filter $(V_BADOS),1),$(error M_HOST_OS must be either WIN32 or NIX, not '$(M_HOST_OS)'))

# OS-specific tools #

# Creates a directory, but does not return error if could not create. Multiple
# directories can be created, as "a/b/c". However, on Windows, only "\" can be
# used.
#
# Usage: <dir/dirs>
define fn_mkdir
$(if $(filter $(M_HOST_OS),WIN32),@-MD $(1),mkdir -p $(1))
endef

# Deletes file and subdirectories. Does not return error.
# Usage <file/dir>
define fn_rmdir
$(if $(filter $(M_HOST_OS),WIN32),DEL /S /Q $(1)
@-RD /S /Q $(1),rm -rf $(1))
endef

## File and Directory Settings ##

C_O=.o

M_TARGET=ghdisk.fat
M_BUILD_DIR=build
C_SRC_DIR=src

### Actions ###

build: $(M_BUILD_DIR)/$(M_TARGET)$(V_E)

clean:
	$(call fn_rmdir,$(M_BUILD_DIR))

$(M_BUILD_DIR)/$(M_TARGET)$(V_E): $(C_SRC_DIR)/ghdisk.fat.c
	$(call fn_mkdir,$(M_BUILD_DIR))
	gcc -Wall -Wextra -pedantic -c -o $(M_BUILD_DIR)/ghdisk.fat$(C_O) $(C_SRC_DIR)/ghdisk.fat.c
	gcc -Wall -Wextra -pedantic -o $(M_BUILD_DIR)/$(M_TARGET)$(V_E) $(M_BUILD_DIR)/ghdisk.fat$(C_O)
