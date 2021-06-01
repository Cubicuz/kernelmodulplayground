#include <bits/types/struct_iovec.h>
#include <iostream>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NETLINK_USER 31
#define MAX_PAYLOAD 1024
struct sockaddr_nl src_addr, dest_addr;
struct nlmsghdr *nlh = NULL;
struct iovec iov;
int sock_fd;
struct msghdr msg;

int main(){
    std::cout << "hello" << std::endl;

    sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
    if (sock_fd < 0)
    {
        std::cout << "Error creating Socket: " << sock_fd << std::endl;
        return -1;
    }

    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid();

    int ret = bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr));
    if (ret < 0){
        std::cout << "bind returned " << ret << std::endl;
        return -1;
    }

    nlh = (struct nlmsghdr *) malloc(NLMSG_SPACE(MAX_PAYLOAD));
    if (!nlh){
        std::cout << "nomem: " << nlh << std::endl;
        return -1;
    }
    memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
    nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = 0;

    auto ptr = NLMSG_DATA(nlh);
    strcpy((char*)ptr, "Hello");

    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;
    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    std::cout << "sending message to kernel" << std::endl;
    sendmsg(sock_fd, &msg, 0);

    std::cout << "waiting for message" << std::endl;
    ret = recvmsg(sock_fd, &msg, 0);
    std::cout << "received " << ret << " bytes" << std::endl;
    close(sock_fd);

    return 0;
}