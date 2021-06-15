#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define n 5
#define thinking 2
#define hungry 1
#define eating 0
#define left (i+4)%n
#define right (i+1)%n	

int state[n];
sem_t mutex;
sem_t s[n];
int currently_eating[n]={0};

void test(int i)
{
	if(state[i] == hungry && state[left]!=eating && state[right]!=eating)
	{
		state[i]=eating;
		//sleep(2);
		printf("Philosopher %d takes fork %d and %d\n",i,left,right);
		printf("Philosopher %d is eating!\n",i);
		currently_eating[i]++;
		printf("\n***Philosophers' status***\n");
		//printf("\n");
		for(int j=0;j<n;j++)
			printf("%d ",currently_eating[j]);
		printf("\n");	
		sleep(2);//other philosophers can get chance (used for showing multithreading)
		sem_post(&s[i]);
	}
}

void take_fork(int i)
{
		sem_wait(&mutex);
		state[i]=hungry;
		printf("Philosopher %d is hungry!\n",i);
		test(i);
	//sleep(1);
		sem_post(&mutex);
		sem_wait(&s[i]);
	//sleep(1);
}

void put_fork(int i)
{
	sem_wait(&mutex);
	state[i]=thinking;
	printf("Philosopher %d putting fork %d and %d\n",i,left,right);
	printf("Philosopher %d is thinking!\n\n",i);
	test(left);
	test(right);
	sem_post(&mutex);
	//sem_wait(&s[i]);
}

void* philosophers(void* arg)
{
	int i=(int)arg;
	while(1)
	{	
		sleep(1);//thinking
		take_fork(i);
		sleep(1);//eating
		put_fork(i);
		//think	
	}
}

int main()
{
    int i; 
    pthread_t thread_id[n]; 
 
    // initialize the semaphores 
    sem_init(&mutex,0,1); 
 
    for(i=0;i<n;i++) 
        sem_init(&s[i],0,0); 
    for(i=0;i<n;i++) 
    { 
        // create philosopher processes 
        pthread_create(&thread_id[i], NULL, philosophers,(void*)i); 
        printf("Philosopher %d is thinking!\n", i); 
    } 
    for(i=0;i<n;i++) 
        pthread_join(thread_id[i], NULL); 
}
		//eat
		
