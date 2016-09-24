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
    printf("Starting astrolog\n");
    int masterSocket = create_tcp_socket();
    set_reuse_addr_opt(masterSocket);
    listen_tcp_socket(masterSocket);

    while (1)
    {
        struct sockaddr_in clientInAddr;
        bzero(&clientInAddr, sizeof(clientInAddr));
        int slaveSocket = accept_client_connection(masterSocket, &clientInAddr);
        printf("Connection established\n");
    }
    
    printf("Finishing astrolog\n");
    exit(EXIT_SUCCESS);
}
