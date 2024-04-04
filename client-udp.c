#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int calculate_skew(long int t){
    int skew;
    time_t t_n = time(NULL);

    skew = t_n - t;
    
    return skew;
}


int main(int argc, char const *argv[]) {
    bool hasPasswd = false;
    long int passwd = 1;
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
    socklen_t addrlen = sizeof(serv_addr);
    long int timer;
    
    
    // Create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, addr, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Send request to server
    if (sendto(sock, NULL, 0, 0, (struct sockaddr *)&serv_addr, addrlen) < 0) {
        perror("sendto failed");
        exit(EXIT_FAILURE);
    }

    // Receive response from server
    if ((valread = recvfrom(sock, &timer, sizeof(timer), 0, (struct sockaddr *)&serv_addr, &addrlen)) < 0) {
        perror("recvfrom failed");
        exit(EXIT_FAILURE);
    }

    if(hasPasswd){
        timer = timer ^ passwd;
    }
    timer -= 2208988800;
    int skew = calculate_skew(timer);

    time_t t = (time_t) timer;
    
    printf("Response from server: %jd\n", t);
    printf("Local time from server is %s", asctime(localtime(&t)));
    printf("Skew is %d seconds\n", skew);

    return 0;
}
