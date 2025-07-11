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

void write_file(int sockfd) {
   FILE *fp;
   char* filename = "receive.txt";
   char buff[max];

   fp = fopen(filename, "w");
   if(fp==NULL) {
      printf("error opening file\n");
      return;
   }

   while(1) {
      int res = recv(sockfd, buff, max, 0);
      if(res == 0) {
         printf("file tranfer successful\n");
         return;
      }
      if(res == -1) {
         printf("file transfer failed\n");
         return;
      }
      fprintf(fp, "%s", buff);
      bzero(buff, max);
   }
}

int main() {
   struct sockaddr_in serveraddr, clientaddr;
   int sockfd, connfd, len;

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if(sockfd==-1) {
      printf("socket creation error\n");
      exit(0);
   }
   printf("socket creation successful\n");

   serveraddr.sin_family = AF_INET;
   serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
   serveraddr.sin_port = htons(port);


   if(bind(sockfd, (SA*)&serveraddr, sizeof(serveraddr)) != 0) {
      printf("bind error\n");
      exit(0);
   }
   printf("bind successful\n");
  
   if(listen(sockfd, 5) != 0) {
      printf("listen error\n");
      exit(0);
   }
   printf("server listening,,,\n");
  
   len = sizeof(clientaddr);
   connfd = accept(sockfd, (SA*)&clientaddr, &len);
   if(connfd==-1) {
      printf("accpet error\n");
      exit(0);
   }
   printf("accept successful\n");
  
   write_file(connfd);
   close(connfd);
   printf("exiting program\n");
}
