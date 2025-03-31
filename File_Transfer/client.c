#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>

#define SA struct sockaddr
#define port 9000 
#define max 1024

void send_file(FILE *fp, int sockfd) {
   char buff[max] = {0};

   while(fgets(buff, max, fp) != NULL) {
      if(send(sockfd, buff, max, 0) == -1) {
         printf("error in sending file\n");
         exit(0);
      }
      bzero(buff, max);
   }
}

int main() {
   FILE *fp;
   char* filename = "temp.txt";
   struct sockaddr_in serveraddr;
   int sockfd;

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if(sockfd==-1) {
      printf("socket creation error\n");
      exit(0);
   }
   printf("socket creation successful\n");

   serveraddr.sin_family = AF_INET;
   serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   serveraddr.sin_port = htons(port);


   if(connect(sockfd, (SA*)&serveraddr, sizeof(serveraddr)) != 0) {
      printf("connection error\n");
      exit(0);
   }
   printf("connection successful\n");

   fp = fopen(filename, "r");
   if(fp==NULL) {
      printf("error in reading file\n");
      exit(0);
   }
   send_file(fp, sockfd);
   
   close(sockfd);
   printf("exiting program\n");
}
