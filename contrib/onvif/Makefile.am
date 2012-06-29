ACLOCAL_AMFLAGS = -I m4

NAMESPACE := onvif
ONVIFHOME := http://www.onvif.org/onvif/

lib_LTLIBRARIES = libonvif_core.la libonvif_svr.la libonvif_ssom.la
libonvif_core_la_SOURCES = duration.c onvifC.c onvifH.h
libonvif_core_la_LIBADD = -lgsoap

libonvif_svr_la_SOURCES = onvifServer.c onvifH.h onvifStub.h
libonvif_svr_la_LIBADD = libonvif_core.la
libonvif_svr_la_DEPENDENCIES =

libonvif_ssom_la_SOURCES = onvif1-SSOM.c\
	onvif2-SSOM.c\
  onvif3-SSOM.c\
  onvif4-SSOM.c\
  onvif5-SSOM.c\
  onvif6-SSOM.c\
  onvif7-SSOM.c\
  onvif8-SSOM.c\
  onvif9-SSOM.c\
  onvif10-SSOM.c\
  onvif11-SSOM.c\
  onvif12-SSOM.c\
  onvif13-SSOM.c\
  onvif14-SSOM.c\
  onvif15-SSOM.c\
  onvif16-SSOM.c\
  onvif17-SSOM.c\
  onvif18-SSOM.c\
  onvif19-SSOM.c\
  onvif20-SSOM.c\
  onvif21-SSOM.c\
  onvif22-SSOM.c\
  onvif23-SSOM.c\
  onvif24-SSOM.c\
  onvif25-SSOM.c\
  onvif26-SSOM.c\
  onvif27-SSOM.c\
  onvif28-SSOM.c\
  onvif29-SSOM.c\
  onvif30-SSOM.c\
  onvif31-SSOM.c\
  onvif32-SSOM.c\
  onvif33-SSOM.c\
  onvif34-SSOM.c\
  wsa-SSOM.c\
  wsa5-SSOM.c\
	wsdd10-SSOM.c\
  xmime-SSOM.c\
  xop-SSOM.c\
  xsd-SSOM.c\
  xsi-SSOM.c\
	onvifStub.h\
	onvifServer.h\
	onvifC.h

libonvif_ssom_la_LIBADD = libonvif_svr.la libonvif_core.la
libonvif_ssom_la_DEPENDENCIES =

onvif_inc_dir = $(includedir)/onvif
onvif_inc__HEADERS = onvif.h\
	onvifH.h\
	onvifStub.h\
	DeviceBinding.nsmap

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
	$(soapsomg) -f $(NAMESPACE)Stub.h -n DeviceBinding.nsmap -i $(NAMESPACE)H.h -r SOAP_OK

