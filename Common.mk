TOP_DIR		:= $(dir $(lastword $(MAKEFILE_LIST)))
ifneq (${CROSS_COMPILER_NAME},)
COMPILER_NAME	:= ${CROSS_COMPILER_NAME}
CC		:= $(COMPILER_NAME)-gcc
else
COMPILER_NAME	:= i686-pc-linux-gnu
CC		:= gcc
endif
GSOAP2_ROOT	:= $(TOP_DIR)contrib/gsoap2/$(COMPILER_NAME)
ONVIF_SRC_DIR	:= $(TOP_DIR)contrib/onvif/out
CFLAGS		:= -DHAVE_CONFIG_H -DLINUX -O2\
	-I$(GSOAP2_ROOT)/include -I$(GSOAP2_ROOT)/share/gsoap -I$(GSOAP2_ROOT)/share/gsoap/plugin -I$(ONVIF_SRC_DIR)
LDFLAGS		:= -DLINUX -O2 -L$(GSOAP2_ROOT)/lib -lgsoap -lcrypto -lssl -lm
