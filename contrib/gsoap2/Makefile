# contrib/gsoap2/Makfile
#

ifneq (${CROSS_COMPILER_NAME},)
COMPILER_NAME	:= ${CROSS_COMPILER_NAME}
else
COMPILER_NAME	:= i686-pc-linux-gnu
endif
PWD		:= $(shell pwd)

build:
	cd gsoap2-svn && ./configure --host=$(CROSS_COMPILER_NAME) --prefix=$(PWD)/$(COMPILER_NAME) && make && make install

fetch:
	svn co https://gsoap2.svn.sourceforge.net/svnroot/gsoap2 gsoap2-svn

package:
	tar jcf gsoap2-$(COMPILER_NAME).tar.bz2 $(COMPILER_NAME)

prepare:
	cd gsoap2-svn && autoreconf && automake

help:
	echo "build fetch package prepare"
