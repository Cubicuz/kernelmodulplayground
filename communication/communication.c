#include "linux/printk.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/skbuff.h> 
#include <net/netlink.h>
#include <net/genetlink.h>
#include "../globals.h"

enum {
    DOC_COMMS_A_UNSPEC,
    DOC_COMMS_A_MSG,
    __DOC_COMMS_A_MAX,
};
#define DOC_COMMS_A_MAX (__DOC_COMMS_A_MAX - 1)
//attribute policy
static struct nla_policy doc_comms_genl_policy[DOC_COMMS_A_MAX + 1] = {
    [DOC_COMMS_A_MSG] = { .type = NLA_NUL_STRING },
};


// handler
static int doc_comms_echo(struct sk_buff *skb, struct genl_info *info)
{
    /* message handling code goes here */
    struct genlmsghdr *genlhdr;
	char *hdr;
    genlhdr = nlmsg_data(nlmsg_hdr(skb));
    if (!genlhdr){
        pr_err("no genlhdr\n");
        return 0;
    }
    hdr = genlmsg_data(genlhdr);
    if (!hdr){
        pr_err("no hdr\n");
        return 0;
    }
    pr_info("new message\n");
    pr_warn("blub %s\n", hdr);
    pr_warn("blib %c\n", hdr[0]);
    return 0;
}
// operation definition
static const struct genl_ops doc_comms_genl_ops_echo[] = {
    {
        .cmd = DOC_COMMS_C_ECHO,
        .flags = 0,
        .policy = doc_comms_genl_policy,
        .doit = doc_comms_echo,
        .dumpit = NULL,
        .validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP_STRICT | GENL_DONT_VALIDATE_DUMP,
    },
};

//family definition
static struct genl_family doc_comms_genl_family = {
    .hdrsize = 0,
    .name = my_genl_family_name,
    .version = 1,
    .maxattr = __DOC_COMMS_A_MAX,
    .ops = doc_comms_genl_ops_echo,
    .n_ops = 1,
}; 

static int __init hello_init(void)
{
    int rc;
    rc = genl_register_family(&doc_comms_genl_family);
    if (rc != 0)
    {
        pr_info("register family failed %i\n", rc);
        return rc;
    }
    pr_info("registered family, with id maybe %i\n", doc_comms_genl_family.id);
    return 0;
}

static void __exit hello_exit(void)
{
    int rc;
    rc = genl_unregister_family(&doc_comms_genl_family);
    if (rc != 0)
    {
        pr_info("unregister family failed %i\n", rc);
    }
}

module_init(hello_init); module_exit(hello_exit);

MODULE_LICENSE("GPL");