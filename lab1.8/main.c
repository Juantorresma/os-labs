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
  
	pthread_t tid[ThreadsNumber]; 	/* the thread identifier */
	pthread_attr_t attr; 		/* set of attributes for the thread */

	/* get the default attributes */
	pthread_attr_init(&attr);

	/* get the current scheduling policy */
  
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
  
	
	/* set the scheduling policy - FIFO, RT, or OTHER */
  
	if (pthread_attr_setschedpolicy(&attr, SCHED_OTHER) != 0)
		printf("unable to set scheduling policy to SCHED_OTHER \n");

	/* create the threads */
	for (i = 0; i < ThreadsNumber; i++) 
    
    args_array[i]=;
    args_array[i].valor=i;
   	pthread_create(&tid[i],&attr,runner,(void *) &args_array[i]); 
    printf("I am the main thread. Created a new thread (%ld) in iteration %d\n",(void *)args_array[i].j,args_array[i].valor);
    
    
}
	/**
	 * Now join on each thread
	 */
	for (i = 0; i < NUM_THREADS; i++) 
		pthread_join(tid[i], NULL);
}

/**
 * The thread will begin control in this function.
 */
void *runner(void *param) 
{
	/* do some work ... */
  
  printf("I am thread %d. I was created in iteration %ld\n",a->id,a->iteration);

	pthread_exit(0);
}
