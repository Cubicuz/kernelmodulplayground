#include "netlink/socket.h"
#include <iostream>
#include <libnl3/netlink/netlink.h>
#include <libnl3/netlink/genl/ctrl.h>
#include <libnl3/netlink/genl/genl.h>
#include <libnl3/netlink/genl/family.h>

int main(){

    nl_sock* sock = nl_socket_alloc();
    if (!sock){
        std::cout << "no socket" << std::endl;
        return 0;
    }
    int ret = genl_connect(sock);
    if (ret){
        std::cout << "genl_connect returned " << ret << std::endl;
    }

    ret = genl_ctrl_resolve(sock, "DOC_COMMS");
    if (ret){
        std::cout << "genl_ctrl_resolve returned " << ret << std::endl;
    }
    
    

    nl_socket_free(sock);
    return 0;
}