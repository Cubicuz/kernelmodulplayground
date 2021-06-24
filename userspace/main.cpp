#include "netlink/handlers.h"
#include "netlink/msg.h"
#include "netlink/socket.h"
#include <cstdio>
#include <iostream>
#include <libnl3/netlink/netlink.h>
#include <libnl3/netlink/genl/ctrl.h>
#include <libnl3/netlink/genl/genl.h>
#include <libnl3/netlink/genl/family.h>
#include <linux/netlink.h>
#include "../globals.h"


int main(){
    nl_debug = 1;
    nl_sock* sock = nl_socket_alloc();
    if (!sock){
        std::cout << "no socket" << std::endl;
        return 0;
    }
    int ret = genl_connect(sock);
    if (ret){
        std::cout << "genl_connect returned " << ret << std::endl;
    }
    int familyId;
    ret = genl_ctrl_resolve(sock, my_genl_family_name);
    if (ret){
        std::cout << "genl_ctrl_resolve returned " << ret << std::endl;
        familyId = ret;
        ret = genl_send_simple(sock, familyId, DOC_COMMS_C_ECHO, 1, 0);
        std::cout << "send simple returned " << ret << std::endl;
    }

    struct nl_msg *msg;
    char *user_hdr;

    msg = nlmsg_alloc();
    if (!msg){
        std::cout << "error allocating nlmsg_alloc" << std::endl;
    }
    user_hdr =static_cast<char*>(genlmsg_user_hdr(genlmsg_hdr(nlmsg_hdr(msg))));
    ret = sprintf(user_hdr, "hallooooo12345678910111213141516171819");
    auto somehdr = genlmsg_put(msg, NL_AUTO_PORT, NL_AUTO_SEQ, familyId, sizeof("hallooooo12345678910111213141516171819"), 0, DOC_COMMS_C_ECHO, 1);
    std::cout << "myptr: " << (void*)user_hdr << " putptr: " << somehdr << std::endl;
    std::cout << "printed " << ret << " caracters " << user_hdr << std::endl;

    ret = nl_send_auto(sock, msg);
    if (ret){
        std::cout << "sent " << ret << " bytes" << std::endl;
    }
    nl_socket_free(sock);
    return 0;
}