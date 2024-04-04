#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

#define RESTART_INTERVAL 0 // in seconds

int main(int argc, char const *argv[]) {
    bool hasPasswd = false;
    long int passwd = 1;

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
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set address information
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Set socket option to reuse address
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to localhost and specific port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
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

        // Send time to client
        t = time(NULL);
        //Add 70 years in seconds.
        t += 2208988800;
        if(hasPasswd){
            t = t ^ passwd;
        }
        send(new_socket, &t, sizeof(t), 0);
        printf("Time sent to client\n");

        close(new_socket);
        // Do not close server_fd to keep it running
        sleep(RESTART_INTERVAL); // Wait before restarting the server
    }

    return 0;
}
