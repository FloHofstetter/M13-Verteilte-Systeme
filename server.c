#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 2048
#define PORT 50000

double cpu_load(void)
{
    // Open proc File and take first value for CPU load.
    // Returns cpu load.
    // Returntype: double
    
    FILE *filepointer;
    filepointer = fopen("/proc/loadavg", "r");    
    double cpu;
    fscanf(filepointer, "%lf\n", &cpu);
    fclose(filepointer);
    return cpu;
}

int logged_in_users(void)
{
    // Opens shell (tested with bash) and returns via multible pipes
    // the amount of users with a differend username.
    // Returntype: int
    
    FILE *filepointer;
    char command[] = "who | awk -F ' ' '{print $1}' | sort -u | wc -l";
    filepointer = popen(command, "r");
    int user_count;
    fscanf(filepointer, "%d\n", &user_count);
    pclose(filepointer);
    return user_count;
}

int main(int arc, char **argsv)
{
    printf("Hello,\nthis is rload! Have a nice day!\n\n");
    struct rload_stat
    {
        double load;
        int users;
    } payload;
    
    payload.load = cpu_load();
    payload.users = logged_in_users();
    
    char message[BUFSIZE];
    char remote_ip[INET_ADDRSTRLEN];
    struct sockaddr_in myaddr;
    struct sockaddr_in remaddr;
    socklen_t addrlen = sizeof(remaddr);
    int recvlen;
    int fd;
    
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Cannot create socket\n");
        exit(EXIT_FAILURE);
    }
    
    memset((char *)&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    myaddr.sin_port=htons(PORT);
    
    if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    
    for (;;)
    {
        printf("Waiting on port %d for incomming connection\n", PORT);
        recvlen = recvfrom(fd, &message, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
        
        if (recvlen > 0)
        {
            // inform user on stdout
            inet_ntop(AF_INET, &(remaddr.sin_addr), remote_ip, INET_ADDRSTRLEN);
            printf("\033[1m");
            printf("%s: ", remote_ip);
            printf("\"");
            printf("\033[m");
            printf("%s", message);
            printf("\"\n");
            
            // process request
            // char reply[] = "Das ist eine Antwort";
            sendto(fd, &payload, sizeof(payload), 0, (struct sockaddr *)&remaddr, sizeof(remaddr));
            //sendto(fd, (const char *)reply, strlen(reply), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
//             if( send(fd , reply , strlen(reply) , 0) < 0)
//             {
//                 puts("Send Reply failed");
//                 return -1;
//             }
            
            printf("Send UDP packet successfully!\n");
        }
    }
}
