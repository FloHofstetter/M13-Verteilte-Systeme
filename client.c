#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <arpa/inet.h>

void show_usage(void)
{
    printf("Usage: client <host> <port>.\n");
}

int main(int argc, char *argv[])
{
    // payload struct
    struct rload_stat
    {
        double load;
        int users;
    } payload;
    
    // Struct for connection to socket
    struct sockaddr_in {
    short            sin_family;        // e.g. AF_INET, AF_INET6
    unsigned short   sin_port;          // e.g. htons(3490)
    struct in_addr   sin_addr;          // see struct in_addr, below
    char             sin_zero[8];       // zero this if you want to
    };

    struct in_addr {
        unsigned long s_addr;           // load with inet_pton()
    };

    struct sockaddr {
        unsigned short    sa_family;    // address family, AF_xxx
        char              sa_data[14];  // 14 bytes of protocol address
    };
    
    struct sockaddr_in server;   // for connection to server
    char target_host[255] = "";  // for server ip
    uint16_t target_port = 0;    // for server port
    if (argc == 3)
    {
        strcpy(target_host, argv[1]);
        target_port = (uint16_t) atoi(argv[2]);
        if (target_port < 1 || atoi(argv[2]) > 65535)
        {
            printf("Invalid port\n");
            printf("Port must be between 1 and 65535\n");
            show_usage();
            return -1;
        }
    }
    else
    {
        show_usage();
        return -1;
    }
    
    int socket_file_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_file_descriptor < 0) {
        printf("Faild to create socket\n");
        return -1;
    }
    printf("Got Socket file descriptor: %d\n", socket_file_descriptor);
    
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 50000 );
    
    if (connect(socket_file_descriptor , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        printf("Faild to connect to socket!\n");
        return -1;
    }
    
    char message[] = "Lieber Server, wie stark bist du denn belastet?";
    
    if( send(socket_file_descriptor , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return -1;
    }
    
    printf("Send UDP packet successfully!\n");
    printf("Waiting for reply");
    // char server_reply[2000];
    //Receive a reply from the server
    if( recv(socket_file_descriptor, &payload , 2048 , 0) < 0)
    {
    puts("recv failed");
    }
    printf("Reply received\n");
    printf("CPU: %2.2lf\n", payload.load);
    printf("User: %d\n", payload.users);
    
    close(socket_file_descriptor);
    
    return 0;
}
