#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

int n=10;
int bt[10];
int wt[10];
int rt[10];
int avwt=0;
int i;
int j;
int total=0;
int pos;
int temp;
int count;
int time;
int remain;
int flag=0;
int time_quantum; 
wt[0]=0;   
void FCFS (void){
 
    printf("\Write Burst Time of processes\n");
    for(i=0;i<n;i++)
    {
        printf("P[%d]:",i+1);
        scanf("%d",&bt[i]);
    }
 
 
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
    }
 
    printf("\nProcess\t\tBurst Time");
    avwt/=i;
    printf("\n\nAverage Waiting Time:%d",avwt);
    return 0;
}

void PSA (void){
	printf("\nMeter Burst time and priority\n");
	    for(i=0;i<n;i++)
	    {
	        printf("\nP[%d]\n",i+1);
	        printf("Burst Time:");
	        scanf("%d",&bt[i]);
	        printf("Priority:");
	        scanf("%d",&pr[i]);
	        p[i]=i+1;        
	    }
 
	for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos])
                pos=j;
        }
 
        tem=pr[i];
        pr[i]=pr[pos];
        pr[pos]=tem;
 
        tem=bt[i];
        bt[i]=bt[pos];
        bt[pos]=tem;
 
        tem=p[i];
        p[i]=p[pos];
        p[pos]=tem;
    }
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        total+=wt[i];
    }
    avwt/=i;
    printf("\n\nAverage Waiting Time=%d",avwt);
}


void SJF (void){
	 printf("\nEnter Burst Time:\n");
    for(i=0;i<n;i++)
    {
        printf("p%d:",i+1);
        scanf("%d",&bt[i]);
        p[i]=i+1;           
    }
 
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(bt[j]<bt[pos])
                pos=j;
        }
 
        tem=bt[i];
        bt[i]=bt[pos];
        bt[pos]=tem;
 
        tem=p[i];
        p[i]=p[pos];
        p[pos]=tem;
    }
 
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        
    }
 
   avwt/=i;
 
    printf("\nProcess\t    Burst Time    \tWaiting Time");

    printf("\n\nAverage Waiting Time=%f",avwt);
  
}


int main(void){
	srand(time(NULL));
	unsigned char x=1;
	while(x){
		char select;
		printf("Select:\n1) PSA\n2) SJF\n3) FCFS\n> ");
		scanf("%c",&num);
		
		if(num==1){
			PSA();
		}
		else if (num==2){
			SJF();
		}
		else if (num==3){
			FCFS();
		}
		
	}
	return 0;
}
