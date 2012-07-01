ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = onvif_ws onvif_rdc onvif_rds

onvif_ws_SOURCES = onvif_ws.c
onvif_ws_LDADD = -lonvif_svr -lonvif_ssom -lonvif_core -lgsoap

onvif_rdc_SOURCES = onvif_rdc.c
onvif_rdc_LDADD = -lonvif_cli -lonvif_core -lgsoap -luuid

onvif_rds_SOURCES = onvif_rds.c
onvif_rds_LDADD = -lonvif_svr -lonvif_ssom -lonvif_core -lgsoap -luuid

