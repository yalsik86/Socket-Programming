#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>

#define max 80
#define port 8000
#define SA struct sockaddr

void func(int connfd){
   char buff[max];
   int i;

   for(;;) {
      bzero(buff, max);
      read(connfd, buff, max);
      printf("mesage form client: %s", buff);

      bzero(buff, max);
      printf("enter message\n");
      i = 0;
      while((buff[i++] = getchar()) != '\n');
      write(connfd, buff, max);

      if((strncmp(buff, "exit", 4))==0){
         printf("server exit\n"); break;
      }
   }
}

int main() {
   struct sockaddr_in serveraddr, clientaddr;
   int sockfd, connfd, len;

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if(sockfd==-1) {
      printf("socket creation failed\n");
      return 0;
   } else {
      printf("socket creation successful\n");
   }

   serveraddr.sin_family = AF_INET;
   serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); 
   serveraddr.sin_port = htons(port);
   
   if(bind(sockfd, (SA*)&serveraddr, sizeof(serveraddr)) != 0) {
      printf("server bind failed\n");
      return 0;
   } else {
      printf("server bind successful\n");
   }

   if(listen(sockfd, 5) != 0) {
      printf("server listen failed\n");
      return 0;
   } else {
      printf("server listening...\n");
   }

   len = sizeof(clientaddr);
   connfd = accept(sockfd, (SA*)&clientaddr, &len);
   if(connfd==-1) {
      printf("server accept failed\n");
      return 0;
   } else {
      printf("server accept successful\n");
   }

   func(connfd);
   close(connfd);
}
