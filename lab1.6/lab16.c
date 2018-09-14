/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>



#define MAX_LINE		80 /* 80 chars per line, per command */

int main(void)
{
	char buf[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
  int should_run = 1;
  pid_t baby_pid; 
  int i=0, upper=0;
 
		
    while (should_run){   
        printf("osh>");
        fflush(stdout);
        fgets(buf,MAX_LINE,stdin);
        
        baby_pid = fork();
        

        
        if(baby_pid<0){
          printf("Not a child or a parent\n");
          return 1; 
        }
        else if(baby_pid==0){
          char * x[MAX_LINE]={"/bin/bash","-c",buf};
          execvp(x[0],x);
          return 0; 
        }
        else if (baby_pid > 0){
          wait(NULL);
          return 0;
        
        }
        
    }
    
	return 0;
}
