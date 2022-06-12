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
   struct msgbuf mbuf;

   key = ftok(".",21);
   if(key==-1){
      perror("ftok");
      return 1;
   }

   /* 获取和键值相关的消息队列的id */
   msqid=msgget(key, IPC_CREAT|0664);
   if(msqid==-1){
       perror("msgget");\
       return 2;
   }
   while(1){
   long msgsz = sizeof(struct msgbuf)-sizeof(long);
   msgrcv(msqid,&mbuf,msgsz,3,0);
   printf("msgRCV:%s\n", mbuf.buf);
   }
   return 0;
}
