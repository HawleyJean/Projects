#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "list.h"
#define BUF_MAX  (81)

int blockcounter=0;
List_t readyProcess;
List_t blockedProcess;
List_t running;
List_t new;
List_t exitList;

typedef struct {
  char name[21];
  int lifetime; 
  int runningTime;
  int processedTime;
} pcb_t;

void alarm_bells ( int sig ) {
 //printf("About %d time units have passed\n\n", time);
 pcb_t *temp;
 void *mydata;
 void *mydata2;
 if(List_head_info(&exitList , &mydata)==1){
   List_remove_head(&exitList, &mydata);
}
 if ((List_head_info(&new, &mydata))==1) {
  List_remove_head( &new, &mydata);
  temp=mydata;
  printf("\nProcess %s : from NEW to READY queue \n",temp->name); 
List_add_tail(&readyProcess, (void *)temp);
 }
 
 List_head_info(&blockedProcess, &mydata); 
 if ((List_head_info(&blockedProcess, &mydata))==1) {
   if(blockcounter<5)
      blockcounter=blockcounter+1;
   else if(blockcounter==5) {
     List_remove_head(&blockedProcess, &mydata);
     temp=mydata;
     List_add_tail(&readyProcess, (void *)temp); 
     blockcounter=0;
  }
  }
 else
   blockcounter=0; 

 //List_head_info(&readyProcess, &mydata);
 if(((List_head_info(&readyProcess, &mydata))==1)||(List_head_info(&running, &mydata2))){
  
   pcb_t *runntemp;
   temp=mydata;
   
   List_head_info(&running, &mydata2);
   if( (List_head_info(&running, &mydata2)==1) ) {
    runntemp= mydata2; 
     if((runntemp->lifetime)>0) {
       if((runntemp->processedTime)<(runntemp->runningTime)){
        runntemp->processedTime= (runntemp->processedTime)+1; 
        runntemp->lifetime = ((runntemp->lifetime) - 1);
        }
       else {
        List_remove_head(&running, &mydata2);
        runntemp->processedTime = 0;
        List_add_tail( &readyProcess , (void *)runntemp );
        printf("\nProcess %s : from RUNNING to READY queue. Lifetime:%d\n",runntemp->name, runntemp->lifetime ); 
      }
      }
     else if((runntemp->lifetime)==0) { 
       List_remove_head(&running, &mydata2);
       runntemp = mydata2;
       List_add_tail(&exitList , (void *)runntemp);
      printf("\nProcess %s :from RUNNING to EXIT state. Lifetime : %d\n",runntemp->name, runntemp->lifetime );
     }
      }
   else {
     printf("Process %s : from READY to RUNNING state. Lifetime of %d\n", temp->name, temp->lifetime);
     List_remove_head(&readyProcess , &mydata2);
     List_add_head( &running, (void *)temp );
   }
  }
 alarm( 1 ); 
}


void sig_handler( int signo )
{
  void *mydata;
  void *context=NULL;
  pcb_t *temp, *poopduck;
  if(signo == SIGUSR1) {
List_head_info(&running, &mydata); 
poopduck=mydata;
printf("Current RUNNING STATE process ::- %s \n ",poopduck->name  );

printf("READY STATE Processes Queue\n");
       while( List_next_node( &readyProcess, &context, &mydata )&& (mydata !=NULL)) {
         poopduck = mydata;
         printf("Process:%s, Running Time:%d  Life time:%d \n", poopduck->name, poopduck->runningTime, poopduck->lifetime );
   }
       printf("NEW STATE Processes Queue\n");
       while( List_next_node( &new, &context, &mydata )&& (mydata !=NULL)) {
         poopduck = mydata;
         printf("Process:%s, Running Time:%d  Life time:%d \n", poopduck->name, poopduck->runningTime, poopduck->lifetime );
}   
        printf("BLOCKED STATE Processes Queue\n");
       while( List_next_node( &blockedProcess, &context, &mydata )&& (mydata !=NULL)) {
         poopduck = mydata;         printf("Process:%s, Running Time:%d  Life time:%d \n", poopduck->name, poopduck->runningTime, poopduck->lifetime );
}
printf("EXIT STATE Processes Queue\n");
       while( List_next_node( &exitList, &context, &mydata )&& (mydata !=NULL)) {
         poopduck = mydata;         printf("Process:%s, Running Time:%d  Life time:%d \n", poopduck->name, poopduck->runningTime, poopduck->lifetime );
}

   }
  else if (signo == SIGINT) {
   printf("Exiting program and deallocating resources\n");
   exit(0);
  }
  else if (signo == SIGUSR2){
    if((List_head_info(&running, &mydata))==1){
      List_remove_head ( &running, &mydata );
      temp=mydata;
      temp->processedTime = 0;
      printf("Process %s :from RUNNING state to BLOCKED state. Lifetime : %d\n", temp->name, temp->lifetime);
      List_add_tail( &blockedProcess, (void *)temp );
     }
    else {
   printf("There is no process in the running state! \n");
  } 
}  
}


int 
main ( int argc, char **argv )
{
  pcb_t *pcb;
  char inputbuffer[BUF_MAX];
  char name[BUF_MAX];
  int rtime, ltime;
  List_init( &new );
  List_init( &readyProcess ); 
  List_init( &blockedProcess );
  List_init( &running );
  List_init( &exitList );
  
while( 1 ) {
 if (signal(SIGUSR1, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGUSR1\n");
  else if (signal(SIGUSR2, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIG\n");
   else if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");
    // A long long wait so that we can easily issue a signal to this process
        if (signal(SIGALRM, alarm_bells )== SIG_ERR)
                       printf("The alarm didn't work");
                          else {                
                          alarm( 1 );
                                }

   if(fgets( inputbuffer, BUF_MAX-1, stdin )) {
    if (sscanf( inputbuffer, "%s %d %d", name, &ltime, &rtime)==3) {
      pcb = (pcb_t *) malloc( sizeof( pcb_t ) );
      if (pcb !=NULL) {
        strncpy( pcb->name, name, 21);
        pcb->name[22] = '\0';
        pcb->lifetime=ltime;
        pcb->runningTime=rtime;
        pcb->processedTime=0; 
        printf ("Process %s has entered NEW state \n Lifetime = %d , running Time = %d\n", pcb->name, pcb->lifetime, pcb->runningTime);
      (List_add_tail(&new, (void *)pcb));
                  
      }
     else {
       printf("Unable to allocate enough memory\n");
     }
}
    else {
      alarm(1);
         for(;;);
}
}
}
  return 0;
}
