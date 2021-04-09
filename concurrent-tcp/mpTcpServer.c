/*

Jamal Nasser
CPSC 3600
HW4

Concurrent TCP server program to handle connections from a client
and store reversed lines from file sent by client.

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
#include <pthread.h>

#define MAX 1024 
#define QUEUE 5

// Reverses the character array in src and places it in dst
void revBuffer(char src[], char dst[], int len){
    int j = 0;
    for(int i = len - 2; i >= 0; --i){
        dst[j++] = src[i];
    }
    if(src[len-1] == '\n')
        dst[j++] = '\n';

    dst[j] = '\0';
}


void* saveFile(void * arg) { 
    const char OK_MSG[] = "ACK: OK";
    const char EOF_MSG[] = "EOF: DONE";

    char file_id[MAX];
    char buff[MAX];
    char r_buff[MAX];

    int sockfd = *((int *)arg);

    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));

    // Generate unique filename using time & send to client
    time_t curtime = time (NULL);
    snprintf(file_id, MAX, "-%ld", curtime);
    char *fname = malloc(MAX*sizeof(char) + strlen(buff) + 1);
    strcpy(fname, buff);
    strcat(fname, file_id);
    write(sockfd, fname, MAX);

    // Receive file from client line by line
    FILE *fp = fopen(fname, "w+");
    while(1){
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));

        // Check for end of file message from client
        if(strcmp(buff, EOF_MSG) == 0){
            write(sockfd, OK_MSG, sizeof(OK_MSG));
            break;
        }

        bzero(r_buff, sizeof(r_buff)); 
        revBuffer(buff, r_buff, strlen(buff));

        fputs(r_buff, fp);
        write(sockfd, OK_MSG, sizeof(OK_MSG));
    }
    fclose(fp);
    return NULL;
} 
  
int main(int argc, char **argv) { 
    int sockfd, connfd; 
    struct sockaddr_in servaddr, cli; 
    pthread_t tid;

    // Create socket file descriptor
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    bzero(&servaddr, sizeof(servaddr)); 
  
    // Fill in socket properties
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(atoi(argv[1])); 
  
    // Bind socket to given port
    if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("Failed on bind...\n"); 
        exit(0); 
    } 
  
    // Listen for client connections
    if ((listen(sockfd, QUEUE)) != 0) { 
        printf("Failed on listen...\n"); 
        exit(0); 
    } 
    unsigned int len = sizeof(cli); 


    printf("Server is online & listening for connections...\n"); 
	while(1){
        connfd = accept(sockfd, (struct sockaddr*)&cli, &len); 
        if (connfd < 0) { 
            printf("Failed on accept...\n"); 
            exit(0); 
        } 

        // Concurrent handling of clients using multi-threading
        printf("Accepted a new client connection...\n");
        pthread_create(&tid, NULL, saveFile, &connfd);

	}
    close(sockfd); 
} 
