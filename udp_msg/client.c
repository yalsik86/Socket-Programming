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
   struct sockaddr_in serveraddr;

   sockfd = socket(AF_INET, SOCK_DGRAM, 0);
   if(sockfd!=-1) printf("socket created\n");

   serveraddr.sin_family = AF_INET;
   serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   serveraddr.sin_port = htons(port);
   
   int i = 0;
   char buff[max];
   bzero(buff, max);
   printf("enter msg: ");
   while((buff[i++]=getchar())!='\n');
   sendto(sockfd, buff, max, 0, (SA*)&serveraddr, sizeof(serveraddr));

   bzero(buff, max);
   int len;
   recvfrom(sockfd, buff, max, 0, (SA*)&serveraddr, &len);
   printf("msg received: %s", buff);
}
