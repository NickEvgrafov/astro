#include "network.h"

#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------//
int create_tcp_socket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        fprintf(stderr, "socket() : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

//-----------------------------------------------------------------------------//
void set_reuse_addr_opt(int sockfd)
{
    int enable = 1;
    int setOptRes = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
                               &enable, sizeof(int));
    if (setOptRes == -1)
    {
        fprintf(stderr, "setsockopt() : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

//-----------------------------------------------------------------------------//
void listen_tcp_socket(int sockfd)
{
    int listened = listen(sockfd, SOMAXCONN);
    if (listened == -1)
    {
        fprintf(stderr, "listen() : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

//-----------------------------------------------------------------------------//
int accept_client_connection(
    int masterSockFd,
    struct sockaddr_in* clientInAddr)
{
    socklen_t clientInAddrLen = sizeof(*clientInAddr);
    bzero(&clientInAddr, sizeof(struct sockaddr_in));

    int slaveSocket = -1;
    while (slaveSocket == -1)
    {

        slaveSocket = accept(masterSockFd, (struct sockaddr *)(&clientInAddr),
                             &clientInAddrLen);
        
        if (slaveSocket == -1 && errno != EINTR)
        {
            fprintf(stderr, "accept() : %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    return slaveSocket;
}
