include ../Common.mk

onvif_ws_SRCS := onvif_ws.c\
	onvifServer.c\
	onvifC.c	

onvif_ws_OBJS := onvif_ws.o\
	onvifServer.o\
	onvifC.o

all: onvif_ws

clean:
	rm $(onvif_ws_OBJS)

onvif_ws: $(onvif_ws_OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

onvif_ws.o: onvifServer.o
	$(CC) $(CFLAGS) -c -o $@ onvif_ws.c

onvifC.o:
	$(CC) $(CFLAGS) -c -o $@ $(ONVIF_SRC_DIR)/onvifC.c

onvifServer.o: onvifC.o
	$(CC) $(CFLAGS) -c -o $@ $(ONVIF_SRC_DIR)/onvifServer.c

