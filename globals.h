#ifndef globals_h
#define globals_h

#define my_genl_family_name "DOC_COMMS"

// commands
enum {
    DOC_COMMS_C_UNSPEC,
    DOC_COMMS_C_ECHO,
    __DOC_COMMS_C_MAX,
};
#define DOC_COMMS_C_MAX (__DOC_COMMS_C_MAX - 1)

struct my_hdr{
    char msg [50];
};


#endif// globals_h