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

void func(int sockfd){
   char buff[max];
   int i;

   for(;;) {
      bzero(buff, max);
      printf("enter message\n");
      i = 0;
      while((buff[i++] = getchar()) != '\n');
      write(sockfd, buff, max);

      bzero(buff, max);
      read(sockfd, buff, max);
      printf("mesage form server: %s", buff);

      if((strncmp(buff, "exit", 4))==0){
         printf("client exit\n"); break;
      }
   }
}

int main() {
   struct sockaddr_in serveraddr, clientaddr;
   int sockfd, connfd;

   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if(sockfd==-1) {
      printf("socket creation failed\n");
      return 0;
   } else {
      printf("socket creation successful\n");
   }

   serveraddr.sin_family = AF_INET;
   serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   serveraddr.sin_port = htons(port);
   
  if(connect(sockfd, (SA*)&serveraddr, sizeof(serveraddr)) != 0) {
      printf("conncetion with server failed\n");
      return 0;
   } else {
      printf("connected to server...\n");     
   }

   func(sockfd);
   close(sockfd);
}
