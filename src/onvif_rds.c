#include <uuid/uuid.h>
#include <onvif/onvifStub.h>
#include <onvif/DeviceBinding.nsmap>

static void dump_d__ProbeType(struct d__ProbeType* p)
{
    if (p->Types)
        printf("d__ProbeType->Types\t: %s\n", *(p->Types));
    printf("d__ProbeType->__size\t: %d\n", p->__size);
    for (int i=0; i < p->__size; i++)
        printf("__any: %s\n", p->__any[i]);
}

static int match_ProbeTypes(char* types)
{
    return strstr(types, "NetworkVideoTransmitter") ? 1 : 0;
}

#if 1
SOAP_FMAC5 int SOAP_FMAC6 __ddl__Probe(struct soap* soap,
                                       struct d__ProbeType *req,
                                       struct d__ProbeMatchesType *res)
{
    static struct d__ProbeMatchType ProbeMatch;
    static struct d__ScopesType scopes;
    static char MessageID[100];
    static char szXAddr[64];
    static char szEndpointReference[64];
    static struct wsa__Relationship wsa_RelatesTo;

    unsigned char MacAddr[8] = {0x00, 0x16, 0xe8, 0x53, 0x13, 0xc7};
    int localIP = 0x6207A8C0;

    dump_d__ProbeType(req);

	if (req->Types && !match_ProbeTypes(*req->Types))
		return SOAP_PROHIBITED;

    sprintf(szXAddr, "http://%s/onvif/device_service", inet_ntoa(*((struct in_addr *)&localIP)));
    sprintf(szEndpointReference, "urn:uuid:11223344-5566-7788-99aa-%02x%02x%02x%02x%02x%02x",
            MacAddr[0],MacAddr[1],MacAddr[2],MacAddr[3],MacAddr[4],MacAddr[5]);

    soap_default_d__ProbeMatchType(soap, &ProbeMatch);
    soap_default_d__ScopesType(soap, &scopes);
    soap_default_wsa__Relationship(soap, &wsa_RelatesTo);

    if (soap->header) {
        uuid_t uuid;

        uuid_generate(uuid);
        strcpy(MessageID, "urn:uuid:");
        uuid_unparse(uuid, MessageID+9);

        if(soap->header->wsa__MessageID) {
            printf("remote wsa__MessageID : %s\n",soap->header->wsa__MessageID);
            soap->header->wsa__RelatesTo =&wsa_RelatesTo;
            soap_default__wsa__RelatesTo(soap, soap->header->wsa__RelatesTo);
            soap->header->wsa__RelatesTo->__item = soap->header->wsa__MessageID;

            soap->header->wsa__MessageID = MessageID;
            soap->header->wsa__To = "http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous";
            soap->header->wsa__Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/ProbeMatches";
        }
    }

    scopes.__item =  "\
onvif://www.onvif.org/type/video_encoder \
onvif://www.onvif.org/type/audio_encoder \
onvif://www.onvif.org/hardware/IPC-model \
onvif://www.onvif.org/name/IPC-model";

    ProbeMatch.wsa__EndpointReference.Address = "http://onvif.com";//szEndpointReference;//"urn:uuid:464A4854-4656-5242-4530-313035394100";
    static char* Types = "dn:NetworkVideoTransmitter";
    ProbeMatch.Types = &Types;//"dn:NetworkVideoTransmitter";
//    soap_s2QName(soap, "dn:NetworkVideoTransmitter", ProbeMatch.Types, 0, -1);
    ProbeMatch.Scopes = &scopes;
    ProbeMatch.XAddrs = szXAddr;//"http://192.168.7.98/onvif/device_service";
    ProbeMatch.MetadataVersion = 1;

    res->__sizeProbeMatch = 1;
    res->ProbeMatch = &ProbeMatch;

    return SOAP_OK;
}
#endif

#if 1
SOAP_FMAC5 int SOAP_FMAC6 __drd__Hello(struct soap* soap,
                                       struct d__HelloType *d__Hello,
                                       struct d__ResolveType *dn__HelloResponse)
{
    printf("Hello\n");
    return SOAP_OK;
}
#endif

#if 1
SOAP_FMAC5 int SOAP_FMAC6 __drd__Bye(struct soap* soap,
                                     struct d__ByeType *d__Bye,
                                     struct d__ResolveType *dn__ByeResponse)
{
    printf("Bye\n");
    return SOAP_OK;
}
#endif

int main(int argc, char *argv[])
{
    struct soap soap;
    struct ip_mreq mcast;

    soap_init2(&soap, SOAP_IO_UDP|SOAP_IO_FLUSH, SOAP_IO_UDP|SOAP_IO_FLUSH);

    soap_set_namespaces(&soap, namespaces);
    soap_set_mode(&soap, SOAP_C_UTFSTRING);

    if (!soap_valid_socket(soap_bind(&soap, NULL, 3702, 10))) {
        soap_print_fault(&soap, stderr);
        exit(1);
    }

    mcast.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
    mcast.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(soap.master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mcast, sizeof(mcast)) < 0) {
        printf("setsockopt error!\n");
        return 0;
    }

    for(;;) {
        printf("Accepting requests...\n");
        if(soap_serve(&soap)) {
            soap_print_fault(&soap, stderr);
        }

        soap_destroy(&soap);
        soap_end(&soap);
    }

    soap_done(&soap);

    return 0;
}
