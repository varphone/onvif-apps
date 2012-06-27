# contrib/gsoap2/Makfile
#

include ../../Common.mk

PWD		:= $(shell pwd)

build: check_source
	@echo "Building gsoap2 ..."
	@cd gsoap2-svn && ./configure --host=$(CROSS_COMPILER_NAME) --prefix=$(PWD)/$(COMPILER_NAME) && make && make install

clean:
	@echo "Cleaning ..."
	@[ -d gsoap2-svn ] && rm -rf gsoap2-svn

fetch:
	@echo "Fetching gsoap2 ..."
	@[ -d gsoap2-svn ] || svn co https://gsoap2.svn.sourceforge.net/svnroot/gsoap2 gsoap2-svn

package:
	@echo "Packing $(COMPILER_NAME) ..."
	@[ -d $(COMPILER_NAME) ] && tar jcf gsoap2-$(COMPILER_NAME).tar.bz2 $(COMPILER_NAME)

patch: check_source
	@echo "Update configure ..."
	@cd gsoap2-svn && autoreconf && automake
	@echo "Patching import headers ..."
	@[ -e gsoap2-svn-HEAD.patch ] && patch -N -p0 < gsoap2-svn-HEAD.patch

help:
	@echo "Supported target:"
	@echo "  build		Build gsoap2 from source."
	@echo "  clean		Clean all files."
	@echo "  fetch		Fetch gsoap2 from svn repository."
	@echo "  package	Archive the builted files."
	@echo "  patch		Patching the source code than fit to our project."
	@echo "  help		Display help message."

check_source:
	@[ -d gsoap2-svn ] || {\
	echo "gsoap2 does not exists, use make fetch first."\
	exit 1}

