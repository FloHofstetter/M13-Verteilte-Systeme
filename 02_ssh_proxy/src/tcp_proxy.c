// Source TCP Connection handeling:
// https://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
// https://www.geeksforgeeks.org/socket-programming-cc/
// Source Select File descriptors:
// https://www.youtube.com/watch?v=Y6pFtgRdUts&t=65s
// Source Signal handling:
// http://openbook.rheinwerk-verlag.de/c_von_a_bis_z/020_c_headerdateien_007.htm
#include <stdio.h>        // I/O Streams
#include <stdlib.h>       // exit() funciton
#include <sys/select.h>   // Select system call
#include <unistd.h>       // read() function
#include <string.h>       // bzero() function
#include <sys/types.h>    // Datatypes for system calls
#include <sys/socket.h>   // Structures  for sockets
#include <netinet/in.h>   // Constants and structures for Internet adresses
#include <arpa/inet.h>    // inet_addr() function (convert from dot notation)
#include <signal.h>       // Signal handling to close sockets

#define ORIGINAL_SSH_PORT 22
#define ORIGINAL_SSH_IP "192.168.0.17"
#define BUFFER_SIZE 1024


// Signal handling to close sockets before termination.
void sigfunc(int sig)
{
    long n;  // Buffer for sysconf

    // SIGINT is sent by pressing Ctrl+C.
    if(SIGINT)
    {
        printf("\nClosig down proxy server.\n");
        n = sysconf(_SC_OPEN_MAX);  // Max number of files that can be open
        // Close alle possible file descriptores.
        for(long i = _SC_OPEN_MAX; i < 2; i--)
            {
                close(i);
            }
        exit(EXIT_SUCCESS);
    }
    // Don't handle other signals.
    else
    {
        return;
    }
}


// Display Error message on stderr
void error(char *msg)
{
    long n;       // Buffer for sysconf
    perror(msg);  // Output to stderr
    // Close alle possible file descriptores.
    for(long i = 2; i < n; i++)
        {
            close(i);
        }
    exit(EXIT_FAILURE);      // exits programm
}


// Main loop...
int main(int argc, char *argv[])
{
    signal(SIGINT, sigfunc);

    int ssh_proxy_fd;          // File descriptor for socket for ssh clients
    int ssh_client_fd;         // File descriptor for accept ssh client
    int ssh_server_fd;         // File descriptor for the original ssh server
    int portno;                // Port number on which ssh proxy accepts connections
    int ssh_client_len;        // Size of address of the client
    int serlen;                // Size of address of original ssh server
    int r_client;              // return of read(); count of characters read
    int w_client;              // return of write(); count of characters written
    int r_server;              // return of read(); count of characters read
    int w_server;              // return of write(); count of characters written

    char client_buffer[BUFFER_SIZE];  // Buffer server sends to proxy
    char server_buffer[BUFFER_SIZE];  // Buffer client sends to proxy

    // Structure containing a internet address. Defined in <netinet/in.h>.
    struct sockaddr_in
    {
        short sin_family;         // Code for address family available as constant eg. AF_INET
        u_short sin_port;         // Port number in network byte order eg. htons(22)
        struct in_addr sin_addr;  // Struct for IP-Address or Constant eg. INADDR_ANY
        char sin_zero[8];         // ???
    };

    struct sockaddr_in proxy_server_addr;  // Address of proxy server
    struct sockaddr_in ssh_server_addr;    // Address of original ssh server
    struct sockaddr_in ssh_client_addr;    // Address of ssh client

    fd_set current_sockets;                  // Socket set for current sockets
    fd_set ready_sockets;                    // Create socket for ready sockets

    bzero(client_buffer, sizeof(client_buffer));  // Zero out client buffer
    bzero(server_buffer, sizeof(server_buffer));  // Zero out server buffer

    // Catch error if no port is provided for the proxy server to listen.
    if (argc < 2)
    {
        fprintf(stderr, "Error, no port provided.\n");  // Print error message.
        exit(1);                                        // Exit programm with error.
    }

    // System call to get socket for ssh proxy server.
    ssh_proxy_fd = socket(AF_INET,  // Internet socket, not UNIX socket
                    SOCK_STREAM,    // Stream Data, not chunked
                    0);             // Protocol 0 -> let OS decide
    
    // Catch error if OS could not provide socket for proxyserver.
    if (ssh_proxy_fd < 0)
    {
        // Call Error handling function with message.
        error("Error opening socket for proxy server.");
    }
    
    bzero((char *) &proxy_server_addr, sizeof(proxy_server_addr));  // Set all to zero in serv_addr buffer
    portno = atoi(argv[1]);                                         // Port from cli input -> string to int

    // Proxy server address configuration
    proxy_server_addr.sin_family = AF_INET;           // proxy server address family
    proxy_server_addr.sin_port = htons(portno);       // proxy server port in network byteorder
    proxy_server_addr.sin_addr.s_addr = INADDR_ANY;   // proxy server listens on any IP-Address
    
    // Catch error if binding fails
    if  (
        bind(                                       // System call to bind proxy server socket to address
            ssh_proxy_fd,                           // Socked file descriptor to bind
            (struct sockaddr*) &proxy_server_addr,  // Casted address structure which socket bind to
            sizeof(proxy_server_addr)               // Size of address
            ) < 0                                   // <0 -> binding failed
        )
    {
        error("Error on binding proxy server socket.");  // Call error handling function
    }

    // Catch error if proxy server listening fails.
    if (listen(ssh_proxy_fd, 5))  // Proxy server accepts max 5 clients in queue
    {
        error("Error on listening on proxy server port.");  // Call error handling function
    }

    ssh_client_len = sizeof(ssh_client_addr);  // Size of address of the ssh client
    // Accept connection from ssh client.
    ssh_client_fd = accept(ssh_proxy_fd, (struct sockaddr*) &ssh_client_addr, &ssh_client_len);

    // Catch error if accepting ssh client fails.
    if (ssh_client_fd < 0)
    {
        error("Error on accept ssh client.");  // Call error handling function
    }

    ssh_server_fd = socket(AF_INET, SOCK_STREAM, 0);  // Create socket for original ssh server
    // Catch error if socket creation for original ssh server fails
    if (ssh_server_fd < 0)
    {
        error("Error on creating sockeck for original ssh server");  // Call error handling function
    }

    // Original ssh server address configuration
    ssh_server_addr.sin_family = AF_INET;                          // Original ssh server address family
    ssh_server_addr.sin_port = htons(ORIGINAL_SSH_PORT);           // Original ssh server port in network byteorder
    ssh_server_addr.sin_addr.s_addr = inet_addr(ORIGINAL_SSH_IP);  // Original ssh server listens on any IP-Address


    if  (
        connect(ssh_server_fd,
               (struct sockaddr*)&ssh_server_addr,
                sizeof(ssh_server_addr)
        ) < 0)
        { 
            error("Error on connection to original ssh server");  // Call error handling function
        } 

    FD_ZERO(&current_sockets);               // Initialize current sockets fd set
    FD_SET(ssh_server_fd, &current_sockets);  // Add original ssh server to current fd set
    FD_SET(ssh_client_fd, &current_sockets);  // Add ssh_client_fd to current fd set

    // While client is connectet
    while(1)
    {
        ready_sockets = current_sockets;  // copy because select is destructive

        if 
        (
            select(FD_SETSIZE,      // Maximum possible file descriptor
                   &ready_sockets,  // Set to check for readeing
                   NULL,            // Set to check for writing
                   NULL,            // Set to check for errors
                   NULL             // Timeout -> selec waits forever
                  ) < 0
        )
        {
            error("Select on file descriptores failed.");  // Call error handling function
        }

        // Iterate over all possible file descriptores
        for (int i=0; i < FD_SETSIZE; i++)
        {
            // Is this file descriptor part of the ready set?
            if (FD_ISSET(i, &ready_sockets))
            {
                // SSH client wants to write to original ssh server
                if (i == ssh_client_fd)
                {
                    // Copy ssh client message to buffer
                    // read(ssh_client_fd, client_buffer, sizeof(client_buffer));
                    ssize_t ret = recv(ssh_client_fd, &client_buffer, sizeof(client_buffer), 0);
                    // printf("Got message from ssh client.\n");
                    // Write buffer to original ssh server
                    // write(ssh_server_fd, client_buffer, sizeof(client_buffer));
                    send(ssh_server_fd, &client_buffer, ret, 0);
                    // sendto(ssh_server_fd, &client_buffer, sizeof(client_buffer), 0, (struct sockaddr*)&ssh_server_addr, serlen);
                    // printf("SSH Client: %s\n", client_buffer);
                    // Set all to zero in buffer
                    // bzero(client_buffer, sizeof(client_buffer));
                }
                // Original ssh server wants to write to ssh client
                else if (i == ssh_server_fd)
                {
                    // Copy ssh client message to buffer
                    ssize_t ret = recv(ssh_server_fd, &server_buffer, sizeof(server_buffer), 0);
                    // read(ssh_server_fd, server_buffer, sizeof(server_buffer));
                    // printf("Got message from server.")
                    // Write buffer to original ssh server
                    // write(ssh_client_fd, server_buffer, sizeof(server_buffer));
                    send(ssh_client_fd, &server_buffer, ret, 0);
                    // sendto(ssh_client_fd, &client_buffer, sizeof(client_buffer), 0, (struct sockaddr*)&ssh_client_addr, ssh_client_len);
                    // printf("SSH Server: %s\n", server_buffer);
                    // bzero(server_buffer, sizeof(server_buffer));
                }
            }
        }        
    }

    // Will never be reached...

    close(ssh_client_fd);  // Close ssh client socket file descriptor
    close(ssh_proxy_fd);   // Close ssh proxy server file descriptor

    return 0;
}
