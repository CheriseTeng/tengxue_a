#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>  //IPv4
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>

int main(){
    char buf[999999+1] = {0};
    struct sockaddr_in addr;
    struct sockaddr_in ser_addr;
    int sockfd = socket( AF_INET, SOCK_STREAM, 0);
    char ipbuf[20] = {0};

    memset( &ser_addr, 0, sizeof(ser_addr));

    if( sockfd == -1 ){
        perror( "socket" );
        exit( EXIT_FAILURE );
    }

    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons( 7777 );
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int res = connect( sockfd, (struct sockaddr*)&ser_addr, sizeof(ser_addr));
    if( res==-1 ){
        perror("connect");
        exit( EXIT_FAILURE );
    }

    while( 1 ){
       printf("input:");
       char buf[128] = {0};
       fgets(buf,127,stdin);
       printf("%s\n", buf);
       if(strncmp(buf, "end",3) ==0 ){
           break;
       }

       send(sockfd, buf, strlen(buf)-1,0);
       memset(buf,0,128);
       recv( sockfd, buf, 127, 0);
       printf("%s\n", buf);
    }

    close(sockfd);

    return 0;
}


