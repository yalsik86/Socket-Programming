#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define max 1024
#define SA struct sockaddr
#define port 8000

void send_file(int sockfd, struct sockaddr_in serveraddr) {
   FILE *fp;
   char* filename = "temp.txt";
   fp = fopen(filename, "r");
   
   char buff[max];
   bzero(buff, max);
   printf("sending file...\n");
   while(fgets(buff, max, fp)!=NULL) {
      sendto(sockfd, buff, max, 0, (SA*)&serveraddr, sizeof(serveraddr));
      bzero(buff, max);
   }

   strcpy(buff, "END");
   sendto(sockfd, buff, max, 0, (SA*)&serveraddr, sizeof(serveraddr));
   fclose(fp);
}

int main() {
   int sockfd;
   struct sockaddr_in serveraddr;

   sockfd = socket(AF_INET, SOCK_DGRAM, 0);
   if(sockfd!=-1) printf("socket created\n");

   serveraddr.sin_family = AF_INET;
   serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   serveraddr.sin_port = htons(port);
  
   send_file(sockfd, serveraddr);
   close(sockfd);
}
