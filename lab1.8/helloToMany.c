#include <pthread.h>
#include <stdio.h>


/* the thread runs in this function */
void *runner(void *param); 

main(int argc, char *argv[])
{
	int i, policy;
  int ThreadsNumber; 
  int valor, j;
  printf("Number of Threads you wish to enter: ");
  fflush(stdout);
  scanf("%d",&ThreadsNumber);
  args args_array[ThreadsNumber];
  
	pthread_t tid[ThreadsNumber]; 	
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	
	if (pthread_attr_getschedpolicy(&attr,&policy) != 0)
		fprintf(stderr, "Unable to get policy.\n");
	else {
		if (policy == SCHED_OTHER)
			printf("SCHED_OTHER\n");
		else if (policy == SCHED_RR)
			printf("SCHED_OTHER\n");
		else if (policy == SCHED_FIFO)
			printf("SCHED_FIFO\n");
	}
  
	
	
	if (pthread_attr_setschedpolicy(&attr, SCHED_OTHER) != 0)
		printf("unable to set scheduling policy to SCHED_OTHER \n");

	for (i = 0; i < ThreadsNumber; i++) 
    
    args_array[i]=;
    args_array[i].valor=i;
   	pthread_create(&tid[i],&attr,runner,(void *) &args_array[i]); 
    printf("I am thread 1. Created new thread (%ld) in iteration %d\n",(void *)args_array[i].j,args_array[i].valor);
    
    
}
	for (i = 0; i < NUM_THREADS; i++) 
		pthread_join(tid[i], NULL);
}

void *runner(void *param) 
{
	
  printf("Hello from thread %d  - I was created in iteration %ld\n",a->id,a->iteration);

	pthread_exit(0);
}
