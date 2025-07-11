#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define max 1024
#define SA struct sockaddr
#define port 8000

int main() {
   int sockfd;
   struct sockaddr_in serveraddr, clientaddr;

   sockfd = socket(AF_INET, SOCK_DGRAM, 0);
   if(sockfd!=-1) printf("socket created\n");

   serveraddr.sin_family = AF_INET;
   serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
   serveraddr.sin_port = htons(port);
   
   bind(sockfd, (SA*)&serveraddr, sizeof(serveraddr));
   
   char buff[max];
   bzero(buff, max);
   int len = sizeof(clientaddr);
   recvfrom(sockfd, buff, max, 0, (SA*)&clientaddr, &len);
   printf("msg received: %s", buff);

   bzero(buff, max);
   int i = 0;
   printf("enter msg: ");
   while((buff[i++]=getchar())!='\n');
   sendto(sockfd, buff, max, 0, (SA*)&clientaddr, len);
}
