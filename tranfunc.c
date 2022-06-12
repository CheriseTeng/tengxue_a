#include <stdio.h>
#include "aladef.h"

/*
 *Function : get current path
 *Author:
 *Date:2022/04/02
 *
*/

void prompt( void ){

    char buf[256];
    getcwd( buf, 256 );
    printf("%s$", buf);

    return ;
}

/*
 *Function : parse string 
 *Author:
 *Date:2022/04/02
 *
*/
void parse_comm ( const char *comm, char *argv[]){


     return;
}
