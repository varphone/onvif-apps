#include <stdio.h>
#include <stdlib.h>
#include "onvifH.h"
#include "DeviceBinding.nsmap"

int main(int argc, char** argv)
{
   struct soap soap;
   int i;
   int m, s; // master and slave sockets
   soap_init(&soap);
   m = soap_bind(&soap, "localhost", 18083, 100);
   if (m < 0)
      soap_print_fault(&soap, stderr);
   else {
      fprintf(stderr, "Socket connection successful: master socket = %d\n", m);
      for (i = 1; ; i++) {
         s = soap_accept(&soap);
         if (s < 0) {
            soap_print_fault(&soap, stderr);
            break;
         }
         fprintf(stderr, "%d: accepted connection from IP=%d.%d.%d.%d socket=%d",
                 i,
                 (soap.ip >> 24)&0xFF,
                 (soap.ip >> 16)&0xFF,
                 (soap.ip >> 8)&0xFF,
                 soap.ip&0xFF,
                 s);
         if (soap_serve(&soap) != SOAP_OK) // process RPC request
            soap_print_fault(&soap, stderr); // print error
         fprintf(stderr, "request served\n");
         soap_destroy(&soap); // clean up class instances
         soap_end(&soap); // clean up everything and close socket
      }
   }
   soap_done(&soap); // close master socket and detach context
   return 0;
}

