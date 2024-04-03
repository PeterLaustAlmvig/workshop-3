#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>


int main(int argc, char const *argv[]) {
    bool hasPasswd = false;
    int passwd = 1;
    if(argc < 3){
        fprintf(stderr, "Two few arguments given\n");
        exit(EXIT_FAILURE);
    }
    if(argc == 4){
        printf("Password enabled\n");
        hasPasswd = true;
        passwd = atoi(argv[3]);
    }
    const char* addr = argv[1];
    long int port = atoi(argv[2]);

    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    long int timer;
    
    
    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    int option = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, addr, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // Receive response from server
    valread = read(sock, &timer, sizeof(long int));

    if(hasPasswd){
        timer = timer ^ passwd;
    }

    timer_t t = (time_t*) timer;
    
    

    printf("Response from server: %jd\n", t);

    return 0;
}
