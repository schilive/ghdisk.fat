# All internal variables are prefixed with a letter then "_". The following list
# says the meanings of each prefix.
#
#  - M_: Modifiable by the user.
#  - C_: Constants.
#  - V_: Modifiable only by Makefile.
#
#  Definitions are always written prefixed with "fn_". Their use and
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
        SET STR=$(1) &&\
	SET STR=%STR:\\=/% &&\
        IF NOT EXIST %STR% (MD %STR%) ELSE IF NOT EXIST %STR%/ (ECHO.Error: file '%STR%' is not a directory >&2 & EXIT /B 1)
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

###
### 1.2. File and Directory Settings
###

C_O := .o

M_TARGET ?= ghdisk.fat
M_BUILD_DIR ?= build
C_SRC_DIR := src

####
#### 2. Targets
####

build: $(M_BUILD_DIR)/$(M_TARGET)$(V_E)

clean:
	$(call fn_rmdir,$(M_BUILD_DIR))

$(M_BUILD_DIR)/$(M_TARGET)$(V_E): $(C_SRC_DIR)/ghdisk.fat.c | build_dir
	gcc -Wall -Wextra -pedantic -c -o $(M_BUILD_DIR)/ghdisk.fat$(C_O) $(C_SRC_DIR)/ghdisk.fat.c
	gcc -Wall -Wextra -pedantic -o $(M_BUILD_DIR)/$(M_TARGET)$(V_E) $(M_BUILD_DIR)/ghdisk.fat$(C_O)

build_dir:
	$(call fn_fmkdir,$(M_BUILD_DIR))

.PHONY: build clean build_dir
