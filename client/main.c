#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <unistd.h>
#include "Headers/DNSResolver.h"  
#include "Headers/SocketFactory.h"  
#include "Headers/HttpRequestBuilder.h"  
#include "Headers/Utilities/SystemUtils.h"  
#include "Headers/Utilities/NetworkUtils.h"
#include "Headers/Configurations/NetworkConfigs.h"

#define MAX_DOMAINNAME 512
#define MAX_FILE_PATH 1024
#define MAX_BUFFER_SIZE 1024

int main(int argc, char const *argv[])
{
    char DomainName[MAX_DOMAINNAME];
    char Path[MAX_FILE_PATH];

    //Initailizing Windows Socket API to use the Networking functions in Windows 
    InitailizeWSA();

    // Get HostName From User
    ReadString("Enter DomainName",DomainName);

    // Resolve HostName to ipv4 address
    char *p_ResolvedHostName = GetIPV4FromDNS(DomainName);

    // Enter the path/file link
    ReadString("Enter Path",Path);

    SOCKET ClientSocket = GetTCPSocketFromFactory();
    ConnectToSockAddr(ClientSocket,GetSockAddr(ADDR_FAMILY,p_ResolvedHostName));

    HttpRequestBuilder builder;
    HttpRequestBuilder_init(&builder);

    setMethod(&builder, "GET");
    setPath(&builder,Path);
    // addHeader(&builder, "Host","example.com");
    // addHeader(&builder, "Content-Type","application/json");
    // setBody(&builder, "{\"username\": \"john_doe\", \"password\": \"pass123\"}");

    char *request = buildRequest(&builder);
    printf("%s\n", request);
    send(ClientSocket,request , strlen(request), 0);

    char response_buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_received;
    while ((bytes_received = recv(ClientSocket, response_buffer, MAX_BUFFER_SIZE, 0)) > 0) {
        fwrite(response_buffer, 1, bytes_received, stdout);
    }
    if (bytes_received < 0) {
        perror("Receive failed");
        return 1;
    }
    printf(response_buffer);
    close(ClientSocket);
    free(request);

    return 0;
}





