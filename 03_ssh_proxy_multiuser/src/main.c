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
#include "getPi.h"



int main()
{
    getPi();
    return 0;
}
