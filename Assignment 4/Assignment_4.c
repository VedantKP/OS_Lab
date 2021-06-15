#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define NP 4 //indicates number of producers
#define NC 3 //indicates number of consumers
#define Items 5 //indicates number of items
#define BSize 5 //indicates number of buffer size

typedef struct resource
{
	int in,out,buffer[BSize]; //in: first empty location, out: first full location, buffer[]: holds items produced
	sem_t full; //semaphone to incdicate slot full
	sem_t empty; //semaphone to incdicate slot empty
	pthread_mutex_t mutex; //Mutex (Door knob)
}resource;

resource shared; //shared resource (buffer)

void *produce(void* arg)
{
	int i,item,index;
	index=(int)arg; //thread number
	for(i=0;i<Items;i++)
	{
		item=i; //Item to be placed in the buffer
		sleep(rand()%10); //Random sleep for concurrency
		sem_wait(&shared.empty); //Knock on the door, waits till recieves a knock...otherwise continues
		pthread_mutex_lock(&shared.mutex); //Locks door from inside
		shared.buffer[shared.in]=item;//Stores item in buffer
		shared.in=(shared.in+1)%BSize; //updates empty slot
		pthread_mutex_unlock(&shared.mutex); //Comes out and keeps door unlocked
		printf("\nProducer [%d] is producing => %d\n",index,item); 
		fflush(stdout);
		sem_post(&shared.full); //Indicates vacancy
		//printf("\nProducer %d finished producing!\n",index);
	}
}

void *consume(void* arg)
{
	int item,index,i;
	index=(int)arg; //Thread number
	for(i=0;i<Items;i++)
	{
		sleep(rand()%10); //Random sleep for concurrency
		sem_wait(&shared.full); //Knock on the door, waits till receives a knock...otherwise continues
		pthread_mutex_lock(&shared.mutex); //Locks door from inside
		item=shared.buffer[shared.out]; //Keeps item with itself
		shared.out=(shared.out+1)%BSize; //Updates next full slot
		pthread_mutex_unlock(&shared.mutex); //Comes out and keeps door unlocked
		printf("\nConsumer [%d] has consumed item => %d\n",index,item);
		fflush(stdout);
		sem_post(&shared.empty); //Indicates vacancy
	}
}

int main()
{
	pthread_t proId,conId; //handles for producer and consumer
	sem_init(&shared.full,0,0); //initializes full slots to 0, second argument '0' indicates semaphore not shareable with processes
	sem_init(&shared.empty,0,BSize); //initializes empty slots to full, second argument '0' indicates semaphore not shareable with processes
	pthread_mutex_init(&shared.mutex,NULL); //Creates door knob
	shared.in=shared.out=0;

	int i;
	
	for(i=0;i<NP;i++)
		pthread_create(&proId,NULL,produce,(void*)i); //Creates threads for producer	
	for(i=0;i<NC;i++)
		pthread_create(&conId,NULL,consume,(void*)i); //Creates threads for consumer	
	pthread_exit(NULL); 
	return 0;
}
