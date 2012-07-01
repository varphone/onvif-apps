#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <uuid/uuid.h>

//#include <onvif/onvifH.h>
#include <onvif/onvifStub.h>
#include <onvif/DeviceBinding.nsmap>

static void dump_d__ProbeMatchesType(struct d__ProbeMatchesType* p)
{
    printf("d__ProbeMatchesType ===========================================\n");
	for (int i=0; i<p->__sizeProbeMatch; i++) {
		printf("ProbeMatch              : %d\n", i);
    	printf("Target EP Address       : %s\r\n", p->ProbeMatch[i].wsa__EndpointReference.Address);
        printf("Target Type             : %s\r\n", *(p->ProbeMatch[i].Types));
        printf("Target Service Address  : %s\r\n", p->ProbeMatch[i].XAddrs);
        printf("Target Metadata Version : %d\r\n", p->ProbeMatch[i].MetadataVersion);
		if (p->ProbeMatch[i].Scopes) {
			printf("Target Scopes Address   : %s\n", p->ProbeMatch[i].Scopes->__item);
			printf("Target Scopes MatchBy   : %s\n", p->ProbeMatch[i].Scopes->MatchBy);
		}
	}
}

static void dump_SOAP_ENV__Header(struct SOAP_ENV__Header* p)
{
    printf("SOAP_ENV__Header ==============================================\n");
	if (p->wsa__MessageID) {
    	printf("MessageID               : %s\n", p->wsa__MessageID);
    }
    if (p->wsa__RelatesTo && p->wsa__RelatesTo->__item) {
		printf("RelatesTo               : %s\n", p->wsa__RelatesTo->__item);
	}
    if (p->wsa__To) {
    	printf("To                      : %s\n", p->wsa__To);
	}
    if (p->wsa__Action) {
		printf("Action                  : %s\n", p->wsa__Action);
	}
}

SOAP_FMAC5 int SOAP_FMAC6 soap_discovery_start(struct soap *soap, const char *soap_endpoint,
        const char *soap_action, struct d__ProbeType *d__Probe)
{
    struct __ddl__Probe ddl__Probe;

    if (!soap_action) {
        soap_action = "http://www.onvif.org/ver10/network/wsdl/Probe";
    }

	soap_default___ddl__Probe(soap, &ddl__Probe);
    ddl__Probe.d__Probe = d__Probe;

    soap->encodingStyle = NULL;
    soap_begin(soap);
    soap_serializeheader(soap);
    soap_serialize___ddl__Probe(soap, &ddl__Probe);
    if (soap_begin_count(soap)) {
        return soap->error;
    }

    if (soap->mode & SOAP_IO_LENGTH) {
        if (soap_envelope_begin_out(soap)
                || soap_putheader(soap)
                || soap_body_begin_out(soap)
                || soap_put___ddl__Probe(soap, &ddl__Probe, "-ddl:Probe", NULL)
                || soap_body_end_out(soap)
                || soap_envelope_end_out(soap)) {
            return soap->error;
        }
    }
    if (soap_end_count(soap)) {
        return soap->error;
    }
    if (soap_connect(soap, soap_endpoint, soap_action)
            || soap_envelope_begin_out(soap)
            || soap_putheader(soap)
            || soap_body_begin_out(soap)
            || soap_put___ddl__Probe(soap, &ddl__Probe, "-ddl:Probe", NULL)
            || soap_body_end_out(soap)
            || soap_envelope_end_out(soap)
            || soap_end_send(soap)) {
        return soap_closesock(soap);
    }
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 soap_discovery_recv(struct soap *soap, struct d__ProbeMatchesType *d__ProbeMatches)
{
    if (!d__ProbeMatches) {
        soap_closesock(soap);
        return -1;
    }

    soap_default_d__ProbeMatchesType(soap, d__ProbeMatches);

    if (soap_begin_recv(soap)
            || soap_envelope_begin_in(soap)
            || soap_recv_header(soap)
            || soap_body_begin_in(soap)) {
        return soap_closesock(soap);
    }
    soap_get_d__ProbeMatchesType(soap, d__ProbeMatches, "d:ProbeMatches", "d:ProbeMatchesType");
    if (soap->error) {
        soap_recv_fault(soap, 0);
        return -1;
    }
    if (soap_body_end_in(soap)
            || soap_envelope_end_in(soap)
            || soap_end_recv(soap)) {
        soap_closesock(soap);
        return -1;
    }
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 soap_discovery_stop(struct soap *soap)
{
    return soap_closesock(soap);
}


int main(int argc, char *argv[])
{
    struct soap soap;
    int result = 0;
    struct d__ProbeType req;
    struct d__ProbeMatchesType res;
    struct d__ScopesType scopes;
    struct SOAP_ENV__Header header;
    int count = 0;
    char guid_string[100];
    uuid_t uuid;

    soap_init(&soap);

    ////////////////////////////////////////////////////////////////////////////
    // discovery test
    uuid_generate(uuid);
    strcpy(guid_string, "urn:uuid:");
    uuid_unparse(uuid, guid_string+9);

    soap_set_namespaces(&soap, namespaces);
    soap.recv_timeout = 10;

    soap_default_SOAP_ENV__Header(&soap, &header);
    header.wsa__MessageID = guid_string;
    header.wsa__To = "urn:schemas-xmlsoap-org:ws:2005:04:discovery";
    header.wsa__Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe";
    soap.header = &header;

    soap_default_d__ScopesType(&soap, &scopes);
    scopes.__item = "onvif://www.onvif.org";

    static char* Types = &"dn:NetworkVideoTransmitter";
    soap_default_d__ProbeType(&soap, &req);
    req.Scopes = &scopes;
    req.Types = &Types;

#if(0)
    do {
        soap_call___ddl__Probe(&soap, "soap.udp://239.255.255.250:3702/datagram", NULL, &req, &res);

        if (soap.error) {
            printf("soap error: %d, %s, %s\n", soap.error, *soap_faultcode(&soap), *soap_faultstring(&soap));
            result = soap.error;
            break;
        } else {
			dump_SOAP_ENV__Header(&soap.header);
			dump_d__ProbeMatchesType(&res);
        }
    } while(0);
#else
    result = soap_discovery_start(&soap, "soap.udp://239.255.255.250:3702/datagram", NULL, &req);
    while (result == SOAP_OK) {
        result = soap_discovery_recv(&soap, &res);
        if (result == SOAP_OK) {
            if (soap.error) {
                //printf("soap error: %d, %s, %s\n", soap.error, *soap_faultcode(&soap), *soap_faultstring(&soap));
                result = soap.error;
            } else {
				dump_SOAP_ENV__Header(&soap.header);
				dump_d__ProbeMatchesType(&res);
            }
        } else if (soap.error) {
            //printf("soap error: %d, %s, %s\n", soap.error, *soap_faultcode(&soap), *soap_faultstring(&soap));
            result = soap.error;
        }
    }
	if (result != SOAP_OK)
    	printf("soap error: %d, %s, %s\n", soap.error, *soap_faultcode(&soap), *soap_faultstring(&soap));
    soap_discovery_stop(&soap);

#endif

    soap_destroy(&soap); // remove deserialized class instances (C++ only)
    soap_end(&soap); // clean up and remove deserialized data
    soap_done(&soap); // detach context (last use and no longer in scope)

    return result;
}
