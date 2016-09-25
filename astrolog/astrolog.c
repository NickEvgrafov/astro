#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../common/network.h" 

int main(int argc, char** argv)
{
    if (argc >= 2)
    {
        int cmpRes = strcmp(argv[1], "--help");
        if (cmpRes == 0)
        {
            printf("usage: astrolog [serverPort]\n");
            exit(EXIT_SUCCESS);
        }
    }

    uint16_t port = 6666;
    if (argc >= 2)
        port = (uint16_t)atoi(argv[1]);
    printf("server port = %d\n", port);

    printf("Starting astrolog\n");
    int masterSocket = create_tcp_socket();
    set_reuse_addr_opt(masterSocket);
    bind_server_socket(masterSocket, port);
    listen_tcp_socket(masterSocket);

    pid_t myPid = getpid();
    
    while (1)
    {
        struct sockaddr_in clientInAddr;
        bzero(&clientInAddr, sizeof(clientInAddr));
        int slaveSocket = accept_client_connection(masterSocket, &clientInAddr);

        char buffer[INET_ADDRSTRLEN];
        const char* clientIpStr = inet_ntop(AF_INET, &clientInAddr.sin_addr, buffer, INET_ADDRSTRLEN);
        int clientPort = (int)clientInAddr.sin_port;
        if (clientIpStr == NULL)
        {
            fprintf(stderr, "%d: inet_ntop() : %s\n", (int)myPid, strerror(errno));
            exit(EXIT_FAILURE);
        }
        printf("%d: accepted request from %s:%d\n", (int)myPid, clientIpStr, clientPort);

        close(slaveSocket);
    }
    
    printf("Finishing astrolog\n");
    close(masterSocket);
    exit(EXIT_SUCCESS);
}
