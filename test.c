#include "aladef.h"

int main( int argc, char *argv[] ){
   char comm[256];
   int fd;

   while(1);

   while(1){
       prompt();
       gets();
       fd=open(argv[1],O_RDONLY);
       if( fd<0 ){
           perror("open");
           return 1;
       }
       dup2( fd, STDIN_FILENO );
       printf("%s\n", comm);
       /* 解析命令 */
       //pase_comm( comm, argc[] );
       //执行命令
       //execl( ".upper", "upper", NULL);
       close(fd);
   }

    return 0;
}
