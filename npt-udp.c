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

    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    time_t t; // Example long int value

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) == 0) {
        perror("socket failed");
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

    while (1) {
        // Receive data from client
        if (recvfrom(server_fd, &t, sizeof(t), 0, (struct sockaddr *)&address, (socklen_t*)&addrlen) < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        t = time(NULL);
        //add 70 years in seconds.
        t += 2208988800;
        if(hasPasswd){
            t = t ^ passwd;
        }

        // Send time to client
        if (sendto(server_fd, &t, sizeof(t), 0, (struct sockaddr *)&address, addrlen) < 0) {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }

        printf("Time sent to client\n");

        sleep(RESTART_INTERVAL); // Wait before processing next request
    }

    return 0;
}
