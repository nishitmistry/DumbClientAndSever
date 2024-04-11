
#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <unistd.h>

#define PORT 80
#define MAX_BUFFER_SIZE 1024

int main(int argc, char const* argv[])
{
	int status, valread;
    SOCKET client_fd;
	struct sockaddr_in serv_addr;

    unsigned long ulAddr = INADDR_NONE;
    // Initialize WSA variables
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);

    // Check for initialization success
    if (wsaerr != 0) {
        printf("The winsock dll not found\n");
        return 0;
    } else {
       printf("The Winsock dll found\n");
       printf("The status: %s \n",wsaData.szSystemStatus);
    }

	char* hello = "GET / HTTP/1.1\r\nHost: www.safratti.com\r\n\r\n";
	char buffer[1024] = { 0 };
	if ((client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}



	// Convert IPv4 and IPv6 addresses from text to binary
	// form
    ulAddr= inet_addr("192.229.179.87");
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.S_un.S_addr = ulAddr;
    if ( ulAddr == INADDR_NONE ) {
        printf("inet_addr failed and returned INADDR_NONE\n");
        return 1;
    }   
    
    if (ulAddr == INADDR_ANY) {
        printf("inet_addr failed and returned INADDR_ANY\n");
        return 1;  
    }

    printf("inet_addr returned success\n");

	if ((status
		= connect(client_fd, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed :-\n");
		return -1;
	}
	send(client_fd, hello, strlen(hello), 0);
	printf("Hello message sent\n");
	valread = read(client_fd, buffer,
				1024 - 1); // subtract 1 for the null
							// terminator at the end
	char response_buffer[MAX_BUFFER_SIZE];
    ssize_t bytes_received;
    while ((bytes_received = recv(client_fd, response_buffer, MAX_BUFFER_SIZE, 0)) > 0) {
        fwrite(response_buffer, 1, bytes_received, stdout);
    }
    if (bytes_received < 0) {
        perror("Receive failed");
        return 1;
    }
    printf(response_buffer);
	// closing the connected socket
	close(client_fd);
	return 0;
}
