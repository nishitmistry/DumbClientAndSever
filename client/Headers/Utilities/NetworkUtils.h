#include <winsock2.h>
#include <stdio.h>

void InitailizeWSA()
{
    // Initialize WSA variables
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);

    // Check for initialization success
    if (wsaerr != 0)
    {
        printf("The winsock dll not found\n");
        exit(-1);
    }
    else
    {
        printf("The Winsock dll found\n");
        printf("The status: %s \n", wsaData.szSystemStatus);
    }
}

struct sockaddr_in GetSockAddr(short AddressFamily, char *IPv4ADDRES)
{
    unsigned long ulAddr = INADDR_NONE;
    struct sockaddr_in client_addr;

    ulAddr = inet_addr(IPv4ADDRES);          // converts string ip to binary representation
    client_addr.sin_port = htons(HTTP_PORT); // htons - Host To Network short
    client_addr.sin_family = ADDR_FAMILY;
    client_addr.sin_addr.S_un.S_addr = ulAddr;
    if (ulAddr == INADDR_NONE)
    {
        printf("inet_addr failed and returned INADDR_NONE\n");
        exit(1);
    }

    if (ulAddr == INADDR_ANY)
    {
        printf("inet_addr failed and returned INADDR_ANY\n");
        exit(1);
    }
    return client_addr;
}

void ConnectToSockAddr(SOCKET Socket, struct sockaddr_in SocketAddress)
{
    int status;
    if ((status = connect(Socket, (struct sockaddr *)&SocketAddress, sizeof(SocketAddress))) < 0)
    {
        printf("\nConnection Failed :- %d\n", WSAGetLastError());
        exit(1);
    }
}