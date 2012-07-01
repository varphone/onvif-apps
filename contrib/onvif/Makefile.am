ACLOCAL_AMFLAGS = -I m4

include ssom.am

NAMESPACE := onvif
ONVIFHOME := http://www.onvif.org/onvif/

lib_LTLIBRARIES = libonvif_core.la libonvif_cli.la libonvif_svr.la libonvif_ssom.la

libonvif_core_la_SOURCES = onvifC.c onvifH.h
libonvif_core_la_LIBADD = -lgsoap

libonvif_cli_la_SOURCES = onvifClient.c onvifStub.h
libonvif_cli_la_LIBADD = libonvif_core.la

libonvif_svr_la_SOURCES = onvifServer.c onvifH.h onvifStub.h
libonvif_svr_la_LIBADD = libonvif_core.la
libonvif_svr_la_DEPENDENCIES =

libonvif_ssom_la_SOURCES = $(ssom_SOURCES)
	onvifStub.h\
	onvifServer.h\
	onvifC.h

libonvif_ssom_la_LIBADD = libonvif_svr.la libonvif_core.la
libonvif_ssom_la_DEPENDENCIES =

onvif_inc_dir = $(includedir)/onvif
onvif_inc__HEADERS = onvif.h\
	onvifH.h\
	onvifStub.h\
	onvif.nsmap

wsdl_FILES := ver10/device/wsdl/devicemgmt.wsdl\
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

wsdl_SUBDIRS := ver10/device/wsdl\
	ver10/event/wsdl\
	ver10/media/wsdl\
	ver10/network/wsdl\
	ver10/schema\
	ver20/imaging/wsdl\
	ver20/analytics/wsdl\
	ver20/ptz/wsdl\
	ver20/util

xsd_FILES := ver10/schema/onvif.xsd
xsl_FILES := ver20/util/onvif-wsdl-viewer.xsl

soapcpp2 := $(CONTRIB_DIR)/bin/soapcpp2
soapcpp2_FLAGS := -2 -c -x -p$(NAMESPACE) -I$(CONTRIB_DIR)/include:$(CONTRIB_DIR)/share/gsoap:$(CONTRIB_DIR)/share/gsoap/import
soapsomg := @$(CONTRIB_DIR)/bin/soapsomg
soapsomg_FLAGS :=
wsdl2h := @$(CONTRIB_DIR)/bin/wsdl2h
wsdl2h_FLAGS := -c -g -t WS-typemap-onvif.dat -n$(NAMESPACE) -r168.234.217.6:8080
xmlnsscan := @$(CONTRIB_DIR)/bin/xmlnsscan 
xmlnsscan_FLAGS := -o xmlns.list

fetch: $(wsdl_FIELS) $(xsd_FILES) $(xsl_FILES)
	@echo "Patching wsdl files ..."
	@[ -e wsdl.patch ] && patch -N -p0 < wsdl.patch

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
	$(xmlnsscan) $(xmlnsscan_FLAGS) -f $(wsdl_FILES)
	$(wsdl2h) $(wsdl2h_FLAGS) -o $(NAMESPACE).h $(wsdl_FILES)

translate-proto:
	$(soapcpp2) $(soapcpp2_FLAGS) $(NAMESPACE).h
	@cp DeviceBinding.nsmap $(NAMESPACE).nsmap

translate-ssom:
	$(soapsomg) -f $(NAMESPACE)Stub.h -n $(NAMESPACE).nsmap -i $(NAMESPACE)H.h -r SOAP_OK

