ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libonvif_core.la libonvif_svr.la libonvif_ssom.la
libonvif_core_la_SOURCES = onvifC.c onvifC.h
libonvif_core_la_LIBADD = libgsoap.la

#libonvif_svr_la_SOURCES = onvifServer.c onvifC.h onvifStub.h
#libonvif_svr_la_LIBADD = libonvif_core.la
#libonvif_svr_la_DEPENDENCIES = libonvif_core.la

wsdl_files := ver10/device/wsdl/devicemgmt.wsdl\
	ver10/event/wsdl/event.wsdl\
	ver10/display.wsdl\
	ver10/deviceio.wsdl\
	ver20/imaging/wsdl/imaging.wsdl\
	ver10/media/wsdl/media.wsdl\
	ver20/ptz/wsdl/ptz.wsdl\
	ver10/receiver.wsdl\
	ver10/recording.wsdl\
	ver10/search.wsdl\
	ver10/network/wsdl/remotediscovery.wsdl\
	ver10/replay.wsdl\
	ver20/analytics/wsdl/analytics.wsdl\
	ver10/analyticsdevice.wsdl\
	ver10/actionengine.wsdl

sub_dirs := ver10/device/wsdl\
	ver10/event/wsdl\
	ver10/media/wsdl\
	ver10/network/wsdl\
	ver10/schema\
	ver20/imaging/wsdl\
	ver20/analytics/wsdl\
	ver20/ptz/wsdl\
	ver20/util

xsd_files := ver10/schema/onvif.xsd
xsl_files := ver20/util/onvif-wsdl-viewer.xsl

NAMESPACE := onvif
ONVIFHOME := http://www.onvif.org/onvif/

soapcpp2 := @$(CONTRIB_DIR)/bin/soapcpp2
soapcpp2_FLAGS := -2 -c -x -p$(NAMESPACE) -I$(CONTRIB_DIR)/include:$(CONTRIB_DIR)/share/gsoap:$(CONTRIB_DIR)/share/gsoap/import
soapsomg := @$(CONTRIB_DIR)/bin/soapsomg
soapsomg_FLAGS :=
wsdl2h := @$(CONTRIB_DIR)/bin/wsdl2h
wsdl2h_FLAGS := -c -t $(CONTRIB_DIR)/share/gsoap/WS/typemap.dat -n$(NAMESPACE)

fetch:

fetch: $(wsdl_files) $(xsd_files) $(xsl_files)

%.wsdl:
	@echo "Fetching" $(ONVIFHOME)$@
	@test -d "$(shell dirname $@)" || mkdir -p "$(shell dirname $@)"
	@wget $(ONVIFHOME)$@ -O $@

%.xsd:
	@echo "Fetching" $(ONVIFHOME)$@
	@test -d "$(shell dirname $@)" || mkdir -p "$(shell dirname $@)"
	@wget $(ONVIFHOME)$@ -O $@

%.xsl:
	$(echo) "Fetching" $(ONVIFHOME)$@
	$(test) -d "$(shell dirname $@)" || mkdir -p "$(shell dirname $@)"
	$(wget) $(ONVIFHOME)$@ -O $@

translate-wsdl:
	$(wsdl2h) $(wsdl2h_FLAGS) -o $(NAMESPACE).h $(wsdl_files)

translate-proto:
	$(soapcpp2) $(soapcpp2_FLAGS) $(NAMESPACE).h

translate-ssom:
	$(soapsomg) -f $(NAMESPACE)Stub.h -i $(NAMESPACE)H.h -r SOAP_OK

