#include <winsock2.h>
#include "Configurations/NetworkConfigs.h"
#define TCPSOCKET 1

SOCKET SocketFactory(int Type)
{
    SOCKET ClientSocket;
    struct sockaddr_in serv_addr;

    switch (Type)
    {
        case TCPSOCKET:
            ClientSocket = socket(ADDR_FAMILY, SOCK_STREAM, IPPROTO_TCP);
            break;
        default:
            printf("Something went Wrong");
            break;
    }
    if (ClientSocket < 0)
    {
        printf("\n Socket creation error \n");
        //Todo:Handle the errors properly 
        //Todo:Implement things like logging
        exit(-1);
    }
    return ClientSocket;
}

SOCKET GetTCPSocketFromFactory()
{
    return SocketFactory(TCPSOCKET);
}