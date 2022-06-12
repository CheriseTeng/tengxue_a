#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>  //IPv4
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <time.h>
#include <sys/stat.h>

pthread_t id; //线程id号
int connfd; //连上新的客户端产生的新套接字
void *recv1( void *arg ){
    //server发给客户端的信息
    int ret;
    char buf[999+1] = {0};
    while(1){
        printf("请输入要发给客户端的信息:\n");
        scanf( "%s", buf );
        ret = send( connfd, buf, sizeof(buf), 0 );
        if( strcmp( buf,"quit") == 0 )
            exit(-1);
    }

}

static int _write_file( const char *_filepath, char *_filename, char *_buf, long _buf_size){

    char filename[512+1] = {0};

    if( access( _filepath, F_OK ) ){
        if( mkdir( _filepath, 0777 )<0 ){
            perror("mkdir");
            exit( EXIT_FAILURE );
        }
    }

    snprintf( filename, sizeof(filename), "%s/%s", _filepath, _filename ); 
    FILE *fd = fopen( filename, "ab+" );
    if( fd<0 ){
        perror("fopen");
        exit( EXIT_FAILURE );
    }

    if( fwrite( _buf, sizeof(char), _buf_size, fd )<0 ){
        perror("fwrite");
        exit( EXIT_FAILURE );
    }

    fclose( fd );

    return 0;
}



int main(){
    char buf[999999+1] = {0};
    struct sockaddr_in addr;
    struct sockaddr_in clientaddr;
    int addrsize = sizeof( clientaddr );
    int sockfd = socket( AF_INET, SOCK_STREAM, 0);
    char ipbuf[20] = {0i};
    char tittle[256+1] = {0};
    char filepath[256+1] = {0};
    char filename[256+1] = {0};

    if( sockfd == -1 ){
        perror( "socket" );
        exit( EXIT_FAILURE );
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons( 7777 );
    addr.sin_addr.s_addr = INADDR_ANY;

    if( bind( sockfd, (struct sockaddr*)&addr, sizeof(addr) ) == -1 ){
        perror( "bind" );
        exit( EXIT_FAILURE );
    }

    if( listen( sockfd, 5 ) == -1 ){
        perror( "listen" );
        exit( EXIT_FAILURE );
    }

    /*pthread_create( &id, NULL, recv1, NULL );*/

    while( 1 ){
        connfd = accept( sockfd, ( struct sockaddr* )&clientaddr, &addrsize );
        if( connfd == -1 ){
            perror( "accept" );
            exit( EXIT_FAILURE );
        }
        printf("目前连接成功的客户端信息:ip[%s] 端口[%hu]\n", inet_ntop(AF_INET,&(clientaddr.sin_addr),ipbuf,sizeof(ipbuf)),ntohs(clientaddr.sin_port));

        pid_t pid = fork();
        if(pid<0){
            perror("fork");
            close(connfd);
            return 1;
        }else if( pid>0 ){
            close(connfd);
            continue;
        }else if( 0 == pid ){
            close( sockfd );
            //打印当前链接成功的客户端信息
            while(1){
                memset( buf,  0x00, sizeof(buf) );
                int n =  recv( connfd, buf, sizeof(buf), 0 );
                if( n != -1 ){
                    struct tm *t = NULL;    //tm结构指针
                    time_t tmp_t;
                    time(&tmp_t);
                    //t = gmtime(&tmp_t);
                    t = localtime(&tmp_t);
                    printf( "Date[%d.%d.%d] Time[%d:%d:%d] buf[%ld] connfd[%d]\n", 
                            (1900+t->tm_year), (1+t->tm_mon), (t->tm_mday),
                            t->tm_hour, t->tm_min, t->tm_sec,
                            strlen(buf), connfd );
                    memset( tittle, 0x00, sizeof(tittle));
                    snprintf( tittle,sizeof(tittle), "Date[%d.%d.%d] Time[%d:%d:%d] buf[%ld] connfd[%d]\n",
                            (1900+t->tm_year), (1+t->tm_mon), (t->tm_mday),
                            t->tm_hour, t->tm_min, t->tm_sec,
                            strlen(buf), connfd );
                    snprintf( filepath, sizeof(filepath),"/home/tengxue/tengxue_a/DATA" );
                    snprintf( filename, sizeof(filename), "%s_%hu_%d%d%d_%d%d%d.txt",
                            inet_ntop(AF_INET,&(clientaddr.sin_addr),ipbuf,sizeof(ipbuf)),ntohs(clientaddr.sin_port),
                            (1900+t->tm_year), (1+t->tm_mon), (t->tm_mday),
                            t->tm_hour, t->tm_min, t->tm_sec);
                    printf("tittle:%sfilepath:%s\nfilename:%s\n",tittle,filepath,filename);
                    _write_file( filepath, filename, tittle,  strlen(tittle) );

                }else{
                    perror("recv");
                    exit( EXIT_FAILURE );
                } 

                printf("%s\n", buf);
                send( connfd, "OK", 2, 0);
            }

           // close( connfd );
        }
        //断开连接，关闭套接字（四次挥手）
        close( sockfd );
    }

    return 0;
}

