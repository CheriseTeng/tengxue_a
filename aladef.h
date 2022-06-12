#ifndef _ALADEF_H_
#define _ALADEF_H_ 

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* 获取当前路径 */
extern void prompt ( void ); 
/* 解析命令 */
extern void parse_comm ( const char *comm, char *argv[] );

#endif
