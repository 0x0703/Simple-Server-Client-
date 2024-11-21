#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, 1);

    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);

    read(client_socket, buffer, BUFFER_SIZE);
    printf("Client: %s\n", buffer);

    // Send a message back to the client
    char *response = "Message received";
    write(client_socket, response, strlen(response));

    close(client_socket);
    close(server_socket);

    return 0;
}
