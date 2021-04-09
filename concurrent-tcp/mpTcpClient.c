/*

Jamal Nasser
CPSC 3600
HW4

Client program to communicate with a TCP server and send a file line by line.

*/

#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <time.h>

#define MAX 1024 

void transmitFile(int sockfd, FILE *fp, char* fname) 
{ 
    const char OK_MSG[] = "ACK: OK";
    const char EOF_MSG[] = "EOF: DONE";

    char buff[MAX]; 

    // Send local filename, get remote filename
    bzero(buff, sizeof(buff));
    write(sockfd, fname, strlen(fname));
    read(sockfd, buff, sizeof(buff));
    printf("Remote filename is: %s\n", buff);

    // Send local file line by line
    bzero(buff, sizeof(buff));
    while(fgets(buff, MAX, fp)){
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));
        // Report serverside error
        if(strcmp(buff, OK_MSG)){
            printf("Server error... \n");
            exit(1);
        }

    }
    
    write(sockfd, EOF_MSG, sizeof(EOF_MSG));

} 
  
int main(int argc, char** argv) 
{ 
    int sockfd; 
    struct sockaddr_in servaddr; 
    FILE *fp;

    // Create socket file descriptor
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // Fill in socket properties
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); 
    servaddr.sin_port = htons(atoi(argv[2])); 
  
    // Connect socket to server
    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 


    printf("Beginning file transmission...\n");

    fp = fopen(argv[3], "r");
    transmitFile(sockfd, fp, argv[3]); 
    close(sockfd); 
    fclose(fp);

    printf("File successfully sent to server.\n");
  
} 
