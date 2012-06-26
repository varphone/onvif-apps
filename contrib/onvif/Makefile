# contrib/onvif/wsdl/Makefile
#
# Notes:
# http proxy: 119.97.144.25:80
#
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
	ver10/actionengine.wsdl\

sub_dirs := ver10/device/wsdl\
	ver10/event/wsdl\
	ver10/media/wsdl\
	ver10/network/wsdl\
	ver10/schema\
	ver20/imaging/wsdl\
	ver20/analytics/wsdl\
	ver20/ptz/wsdl\
	ver20/util\

xsd_files := ver10/schema/onvif.xsd
xsl_files := ver20/util/onvif-wsdl-viewer.xsl

echo		:= @echo
mkdir		:= @mkdir
sed		:= @sed
test		:= @test
wget		:= @wget -c --no-http-keep-alive --no-cache
soapcpp2	:= @${GSOAP2_ROOT}/bin/soapcpp2 -2 -c -L -dout -I${GSOAP2_ROOT}/include:${GSOAP2_ROOT}/share/gsoap:${GSOAP2_ROOT}/share/gsoap/import
wsdl2h		:= @${GSOAP2_ROOT}/bin/wsdl2h -t ${GSOAP2_ROOT}/share/gsoap/WS/typemap.dat
base_href	:= http://www.onvif.org/onvif/

all:

clean:
	rm $(wsdl_files) $(xsd_files) $(xsl_files)

prepare:
	$(mkdir) -p $(sub_dirs)

fetch: $(wsdl_files) $(xsd_files) $(xsl_files)

%.wsdl:
	$(echo) "Fetching" $(base_href)$@
	$(test) -d "$(shell dirname $@)" || mkdir -p "$(shell dirname $@)"
	$(wget) $(base_href)$@ -O $@

%.xsd:
	$(echo) "Fetching" $(base_href)$@
	$(test) -d "$(shell dirname $@)" || mkdir -p "$(shell dirname $@)"
	$(wget) $(base_href)$@ -O $@

%.xsl:
	$(echo) "Fetching" $(base_href)$@
	$(test) -d "$(shell dirname $@)" || mkdir -p "$(shell dirname $@)"
	$(wget) $(base_href)$@ -O $@

#patch: $(wsdl_files)
#	$(echo) "Patching " $^ " for xml-stylesheet href"
#	$(sed) -i 's/\(<?xml-stylesheet type="text\/xsl" href="\)\(.*\)\("?>\)/\1onvif-wsdl-viewer.xsl\3/' $^
#	$(echo) "Patching " $^ " for schemaLocation"
#	$(sed) -i 's/\(\s*<xs:import namespace="http:\/\/www.onvif.org\/ver10\/schema" schemaLocation="\)\(.*\)\("\/>\)/\1onvif.xsd\3/' $^

translation: trans-wsdl trans-header

trans-wsdl: $(wsdl_files)
	$(wsdl2h) -c -x -o onvif.h $^

trans-header: onvif.h
	$(soapcpp2) -ponvif $^

