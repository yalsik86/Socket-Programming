#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define max 1024
#define SA struct sockaddr
#define port 8000

void recv_file(int sockfd, struct sockaddr_in clientaddr) {
   FILE* fp;
   char* filename = "received.txt";
   fp = fopen(filename, "w");

   int len = sizeof(clientaddr);
   char buff[max];
   bzero(buff, max);

   while(1) {
      recvfrom(sockfd, buff, max, 0, (SA*)&clientaddr, &len);
      if(strncmp(buff, "END", 3)==0) break;
      fprintf(fp, "%s", buff);
      bzero(buff, max);
   }
   printf("file received\n");
   fclose(fp);
}

int main() {
   int sockfd;
   struct sockaddr_in serveraddr, clientaddr;

   sockfd = socket(AF_INET, SOCK_DGRAM, 0);
   if(sockfd!=-1) printf("socket created\n");

   serveraddr.sin_family = AF_INET;
   serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
   serveraddr.sin_port = htons(port);
   
   bind(sockfd, (SA*)&serveraddr, sizeof(serveraddr));
  
   recv_file(sockfd, clientaddr);
   close(sockfd);
}
