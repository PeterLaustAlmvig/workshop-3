from socket import *

#create socket
sockfd = socket(AF_INET, SOCK_STREAM)
#bind socket
sockfd.bind(("127.0.0.1", 9999))
#listen for connections
sockfd.listen()
while True:
    #accept connection
    newsockfd, address = sockfd.accept() 
    #recv message
    data, client_addr = sockfd.recvfrom(1024)
    print(f"connected to{newsockfd}")

    #recieve message
    response = newsockfd.recv(1024)
    print(response)

    #send message
    message = "yo, yo"
    msg = message.encode()
    sockfd.sendto(msg, client_addr)

