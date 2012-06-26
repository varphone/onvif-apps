### To Make patch:

  diff -Naur gsoap2-svn/gsoap/import/wsdd10.h gsoap2-svn/gsoap/import/wsdd10-patched.h > gsoap2-svn-HEAD.patch
  diff -Naur gsoap2-svn/gsoap/import/wsdx10.h gsoap2-svn/gsoap/import/wsdx10-patched.h >> gsoap2-svn-HEAD.patch

### To Apply patch:

  patch -N -p0 < gsoap2-svn-HEAD.patch

About gSOAP
-----------

### wsdl2h:

  WSDL/schema importer and data binding mapper tool.

### soapcpp2:

  sub/skeleton compiler and code generator.

A client example
----------------

### Generate the header file:

  wsdl -c -o cacl.h www.genivia.com/calc.wsdl

### Generate the stubs API:

  soapcpp2 -c -I${GSOAP2_ROOT}/share/gsoap/import cacl.h

### The main entry:

  #include "soapH.h"
  #include "cacl.nsmap"
  int main(int argc, char** argv)
  {
     struct soap *soap = soap_new();
     double result;
     if (soap_call_ns__add(soap, 1.0, 2.0, &result) == SOAP_OK)
        printf("The sum of 1.0 and 2.0 is %lg\n", result);
     else
        soap_print_fault(soap, stderr);
     soap_end(soap);
     soap_free(soap);
  }

### Compile the client:

  cc -o calc cacl.c calcC.c -lgsoap


