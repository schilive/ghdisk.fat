# All variables/options are prefixed with an uppercase letter then "_", then
# their name. Each prefix has a meaning, specified in the following list.
#
#  - M_: Option, that may be set by the "builder".
#  - C_: A variable of constant value. Change at your own risk.
#  - V_: A variable set internally. Do not change externally.
#
#  All function macro starts with the prefix 'fn_<namespace>_'.
#
# !!!WARNINGS!!! Only tabs where strictly necessary, otherwise use 4 spaces for
# indentation.

####
#### 1. Settings
####

V_CFLAGS =
V_ENC_SRCS =

M_AUTO ?= 1
V_AUTO_ENC_SRCS =
V_AUTO_CFLAGS =

V_TAB1 = A	B
    V_TAB2 = $(subst A,,$(V_TAB1))
    V_TAB = $(subst B,,$(V_TAB2))
V_EMPTY =
    V_SP = $(V_EMPTY) $(V_EMPTY)

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

V_CFLAGS += $(M_CFLAGS)

###
### 1.3. String and Encoding System
###

M_ENC_TRN ?= c
M_ENC_NRM ?= c
M_ENC_FIL ?= c

M_ENC_TRN_W ?=

ifeq ($(M_ENC_SRCS),)
    V_AUTO_ENC_SRCS += $(M_ENC_TRN)_sz
    V_AUTO_ENC_SRCS += $(M_ENC_FIL)_unkch

    ifneq ($(M_ENC_TRN),$(M_ENC_FIL))
        ifeq ($(M_ENC_TRN),$(M_ENC_NRM))
            V_AUTO_ENC_SRCS += $(M_ENC_TRN)_conv_$(M_ENC_FIL)
        else
            V_AUTO_ENC_SRCS += $(M_ENC_TRN)_conv_$(M_ENC_NRM)
            ifneq ($(M_ENC_NRM),$(M_ENC_FIL))
                V_AUTO_ENC_SRCS += $(M_ENC_NRM)_conv_$(M_ENC_FIL)
            endif
        endif
    endif
else
    V_ENC_SRCS = $(M_ENC_SRCS)
endif

V_AUTO_CFLAGS += $(call fn_cc_D,_G_ENC_TRN,$(M_ENC_TRN))
V_AUTO_CFLAGS += $(call fn_cc_D,_G_ENC_NRM,$(M_ENC_NRM))
V_AUTO_CFLAGS += $(call fn_cc_D,_G_ENC_FIL,$(M_ENC_FIL))
ifneq ($(M_ENC_TRN_W),)
    V_CFLAGS += $(call fn_cc_D,_G_ENC_TRN_W,)
else
    ifeq ($(M_ENC_TRN),w)
        V_AUTO_CFLAGS += $(call fn_cc_D,_G_ENC_TRN_W,)
    endif
endif

ifneq ($(M_AUTO),)
    V_CFLAGS += $(V_AUTO_CFLAGS)
    V_ENC_SRCS += $(V_AUTO_ENC_SRCS)
endif

###
### 1.4. Etc.
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
    define fn_os_fmkdir
        IF NOT EXIST "$(subst /,\,$(1))" (MD "$(subst /,\,$(1))")\
        ELSE IF NOT EXIST "$(subst /,\,$(1))\\" (\
            ECHO.Error: file "$(subst /,\,$(1))" is not a directory >&2\
            & EXIT /B 1\
        )
    endef
else
ifeq ($(M_HOST_OS),posix)
    define fn_os_fmkdir
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
    define fn_os_rmdir
        -DEL /S /Q $(1)
        -RD /S /Q $(1)
    endef
else
ifeq ($(M_HOST_OS),posix)
    define fn_os_rmdir
        rm -rf $(1)
    endef
endif
endif

# Updates the timestamp of $(1).
# Usage: <File>
ifeq ($(M_HOST_OS),winnt)
    define fn_os_touch
        COPY /Y /B $(subst /,\,$(1)) +,, $(subst /,\,$(1)) > nul 2>&1
    endef
else
ifeq ($(M_HOST_OS),posix)
    define fn_os_touch
        touch $(1)
    endef
endif
endif

###
### 2.2. Compiler-Specific
###

# Compiles $(1) to object file $(2)
# Usage <C source file, Output file>
ifeq ($(M_COMPILER),gcc)
    define fn_cc_c_to_o
        $(M_CC) $(V_CFLAGS) $(M_ACFLAGS) -c -o $(2) $(1)
    endef
else
ifeq ($(M_COMPILER),msvc)
    define fn_cc_c_to_o
        $(M_CC) $(V_CFLAGS) $(M_ACFLAGS) /c /Fo:$(2) $(1)
    endef
endif
endif

# Links $(1) to executable file $(2)
# Usage <Object file(s), Output file>
ifeq ($(M_COMPILER),gcc)
    define fn_cc_o_to_out
        $(M_LD) -o $(2) $(1) $(M_LDFLAGS)
    endef
else
ifeq ($(M_COMPILER),msvc)
    define fn_cc_o_to_out
        $(M_LD) $(M_LDFLAGS) /OUT:$(2) $(1)
    endef
endif
endif

# Expands to the compiler-specific flag that defines the macro $(1) with the
# value $(2). Do pay attention to not include <=>, <'> or <"> in $(1).
#
# Usage: <Macro name, macro value>
ifeq ($(M_COMPILER),gcc)
    define fn_cc_D
-D "$(1)=$(2)"
    endef
else
ifeq ($(M_COMPILER),msvc)
    define fn_cc_D
/D "$(1)=$(2)"
    endef
endif
endif


###
### 2.3. Target
###

# Creates rule for $(M_BUILD_DIR)$(1)$(M_O) to compile $(1) to it, and makes
# $(C_SRC_DIR)$(1).c the requirement.
# Usage: <C source file>
define fn_tar_c
$(M_BUILD_DIR)/$(1)$(M_O): $(C_SRC_DIR)/$(1).c | build_dir
	$(call fn_cc_c_to_o,$(C_SRC_DIR)/$(1).c,$$@)
endef

# Creates a double-colon rule of name 'build_dir' to create the directory $(1).
# Usage: <dir>
define fn_tar_build_dir
build_dir::
	$(call fn_os_fmkdir,$(1))
endef

# Defines $(2) the prerequisite of target $(1)
# Usage: <Target, Requirements>
define fn_tar_req
$(1): $(2)
	$(call fn_os_touch,$(1))

$(2):
	$(call fn_os_touch,$(2))

endef
        
####
#### 3. Targets
####

V_SRCS = ghdisk.fat str print
    V_SRCS += $(foreach i,$(V_ENC_SRCS),str/enc/$(i))
V_REQS1 =\
	ghdisk.fat.c*\
		*str.h*\
		*print.h\
	common.h*\
		*str.h*\
		*print.h\
	print.h*\
		*str.h\
	print.c*\
		*print.h*\
		*sysstr.h\
	str.c*\
		*sysstr.h*\
		*str/macros.h*\
		*str/buffer.h*\
		*str/converr.h\
	str.h*\
		*str/str.h*\
		*str/strenc.h*\
		*str/macros.h\
	sysstr.h*\
		*str/converr.h*\
		*str/str.h*\
		*str/strenc.h*\
		*str/buffer.h\
	str/buffer.h\
	str/conf.h\
	str/converr.h\
	str/enc.h*\
		*str/converr.h*\
		*str/str.h*\
		*str/strenc.h*\
		*str/buffer.h\
	str/macros.h*\
		*common.h*\
		*str/macros.h*\
		*str/converr.h\
	str/str.h*\
		*str/buffer.h*\
		*str/strenc.h\
	str/strenc.h*\
		*str/macros.h
    V_REQS1 += $(foreach i,$(V_ENC_SRCS), str/enc/$(i).c**str/enc.h)
    V_REQS2 = $(subst $(V_TAB),,$(V_REQS1))
    V_REQS = $(subst * *,*,$(V_REQS2))

V_TARGET_SRCS = $(foreach i,$(V_SRCS),$(word 1,$(subst *, ,$(i))))
V_TARGET_OBJS1 = $(foreach i,$(V_SRCS),$(word 1,$(subst *, ,$(i))))
    V_TARGET_OBJS = $(foreach i,$(V_TARGET_OBJS1),$(M_BUILD_DIR)/$(i)$(M_O))
V_BUILD_DIRS1 = $(foreach i,$(V_TARGET_SRCS),$(dir $(M_BUILD_DIR)/$(i)))
    V_BUILD_DIRS = $(sort $(V_BUILD_DIRS1))

build: $(M_BUILD_DIR)/$(M_TARGET)$(M_E)

$(M_BUILD_DIR)/$(M_TARGET)$(M_E): $(V_TARGET_OBJS) | build_dir
	$(call fn_cc_o_to_out,$^,$@)

$(foreach i,$(V_TARGET_SRCS),$(eval $(call fn_tar_c,$(i))))

$(foreach i,$(V_REQS),\
	$(foreach j,$(wordlist 2,$(words $(subst *, ,$(i))),$(subst *, ,$(i))),\
		$(eval $(call fn_tar_req,\
			$(C_SRC_DIR)/$(word 1,$(subst *, ,$(i))),\
			$(C_SRC_DIR)/$(j)\
		))\
	)\
)


$(foreach i,$(V_BUILD_DIRS),$(eval $(call fn_tar_build_dir,$(i))))

clean:
	$(call fn_os_rmdir,$(M_BUILD_DIR))

re: clean build

# V_SRCS1 =\
# 	ghdisk.fat.c*\
# 		*str.h*\
# 		*print.h\
# 	str.c*\
# 		*sysstr.h*\
# 		*str/macros.h*\
# 		*str/buffer.h*\
# 		*str/converr.h\
# 	print.c*\
# 		*print.h*\
# 		*sysstr.h
# V_SRCS = $(subst * *,*,$(V_SRCS1))
# V_SRCS += $(foreach i,$(V_ENC_SRCS),str/enc/$(i).c)
# 
# V_TARGET_REQS = $(foreach i,$(V_SRCS),$(M_BUILD_DIR)/$(patsubst %.c,%$(M_O),$(word 1,$(subst *, ,$(i)))))
# V_DIRS1 = $(foreach i,$(V_SRCS),$(dir $(word 1,$(subst *, ,$(i)))))
# V_DIRS2 = $(foreach i,$(V_DIRS1),$(M_BUILD_DIR)/$(i))
# ifeq ($(V_DIRS2),)
#     V_DIRS = $(M_BUILD_DIR)
# else
#     V_DIRS = $(sort $(V_DIRS2))
# endif
# $(info A: $(V_DIRS1))
# $(info B: $(V_DIRS2))
# $(info C: $(V_DIRS))
# 
# build: $(M_BUILD_DIR)/$(M_TARGET)$(M_E)
# 
# $(M_BUILD_DIR)/$(M_TARGET)$(M_E): $(V_TARGET_REQS) | build_dir
# 	$(call fn_cc_o_to_out,$^,$@)
# 
# $(foreach i,$(V_SRCS),$(eval $(call fn_tar_c,$(subst *, ,$(i)))))
# 
# $(foreach i,$(V_DIRS),$(eval $(call fn_tar_build_dir,$(i))))
# 
# clean:
# 	$(call fn_os_rmdir,$(M_BUILD_DIR))
# 
# 
.PHONY: build clean re build_dir
