#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define GET 0
#define POST 1
#define OPTIONS 2
#define MAX_LEN 50000

char* DNSLookUp(const char* URL) {
  struct hostent *honestUnit;

  honestUnit = gethostbyname(URL);

  if (!honestUnit) {
    puts("E: Error on gethostbyname() function");
    printf("Error code: %d\n", *(int*)honestUnit);
    exit(-1);
  }

  return inet_ntoa(*(struct in_addr*)honestUnit->h_addr_list[0]);
}

int checkIP(const char *ip) { // IPv4 only
  return (strlen(ip)>0 && strlen(ip)<16) ? 1 : 0;
}

int request(int flag, const char* ip, char* data) { // request(GET, "https://www.google.co.kr./", NULL)
  if (!checkIP(ip)) { puts("E: Beep! The len of IP Address error dude.") exit(-1); }

  int fdSock,lastone;
  char buf[MAX_LEN], *str="";
  struct sockaddr_in servAddr;

  if ((fdSock=socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    exit(-1);
  }
  
  memset(&servAddr,0,sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = inet_addr(ip);
  servAddr.sin_port = htons(80);

  if((connect(fdSock, (struct sockaddr *)&servAddr, sizeof(servAddr))) < 0) {
    puts("E: Error on connect() function");
    exit(-1);
  }
  
  if ( (lastone=read(fdSock,buf,MAX_LEN))>0 ) {
    buf[lastone]='\0';
    close(fdSock);

    return 0;
  }

  close(fdSock);

  return -1;
}
