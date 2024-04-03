#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[]) {
    bool hasPasswd = false;
    int passwd = 1;

    if(argc < 2){
        perror("Two few arguments given\n");
        exit(EXIT_FAILURE);
    }
    if(argc == 3){
        printf("Password enabled\n");
        hasPasswd = true;
        passwd = atoi(argv[2]);
    }
    long int port = atoi(argv[1]);

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    time_t t; // Example long int value

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        fprintf(stderr, "Two few arguments given\n");
        exit(EXIT_FAILURE);
    }

    // Set address information
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind the socket to localhost and specific port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // Accept incoming connections
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // Send long int to client
    t = time(NULL);
    //const void *  timer =  (void *) t;
    if(hasPasswd){
        t = t ^ passwd;
    }
    send(new_socket, &t, sizeof(t), 0);
    printf("Time sent to client\n");

    close(new_socket);
    close(server_fd);

    return 0;
}
