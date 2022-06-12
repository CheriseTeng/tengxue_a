#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msgbuf{
      long type;
      char buf[128];
   };

int main(void){
   key_t key;
   int msqid;
   struct msgbuf mbuf = {3,"hello world"};
   //copy字符串，strcpy
   key = ftok(".",21);
   if(key==-1){
      perror("ftok");
      return 1;
   }

   /* 获取和键值相关的消息队列的id */
   msqid=msgget(key, IPC_CREAT|0664);
   if(msqid==-1){
       perror("msgget");
       return 2;
   }

   long msgsz = sizeof(struct msgbuf)-sizeof(long);
   msgsnd(msqid,&mbuf,msgsz,0);
   return 0;
}
