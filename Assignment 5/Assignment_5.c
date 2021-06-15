#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

sem_t wrt;
pthread_mutex_t mutex;
int shared,readcount=0;

void* readers(void* arg)
{
    int i=(int)arg;
    while(1)
    {
        sleep(rand()%10);
        pthread_mutex_lock(&mutex);
        readcount++;
        printf("\nReader %d arrives\n",i);
        if(readcount==1)
        {
            printf("-------------------------------------------------\n");
            printf("\nReader %d is the first reader....",i);
            printf("...Writers are blocked\n");
            sem_wait(&wrt);
        }
        printf("\nReadcount: %d",readcount);
        pthread_mutex_unlock(&mutex);

        printf("\nReader %d reads %d",i,shared);
        sleep(2);

        pthread_mutex_lock(&mutex);
        readcount--;
        printf("\nReader %d is leaving!",i);
        printf("\nReadcount: %d",readcount);
        if(readcount==0)
        {
            printf("\nReader %d is the last reader!\nEnabling writers!\n",i);
            printf("-------------------------------------------------\n");
            sem_post(&wrt);
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void* writers(void* arg)
{
    int i=(int)arg;
    while(1)
    {
        sem_wait(&wrt);
        shared=rand()%10;
        printf("-------------------------------------------------\n");
        printf("\nWriter %d is entering",i);
        printf("\nWriter %d is writing %d",i,shared);
        printf("\nWriter %d is leaving!\n");
        printf("-------------------------------------------------\n");
        sem_post(&wrt);
        sleep(rand()%10);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t* reader,*writer;
    int rd_count,wr_count;
    int i;
    printf("\nEnter reader count => ");
    scanf("%d",&rd_count);

    printf("\nEnter writer count => ");
    scanf("%d",&wr_count);

    sem_init(&wrt,0,1);
    pthread_mutex_init(&mutex,NULL);

    reader=(pthread_t*)malloc(rd_count*sizeof(pthread_t));
    writer=(pthread_t*)malloc(wr_count*sizeof(pthread_t));

    for(i=0;i<rd_count;i++)
    {
        pthread_create(&reader[i],NULL,readers,(void*)i);
        printf("\nReader %d starting!\n",i);
    }

    for(i=0;i<wr_count;i++)
    {
        pthread_create(&writer[i],NULL,writers,(void*)i);
        printf("\nWriter %d starting!\n",i);
    }

    for(i=0;i<rd_count;i++)
    {
        pthread_join(reader[i],NULL);
        printf("\nReader %d joined!\n",i);
    }

    for(i=0;i<wr_count;i++)
    {
        pthread_join(writer[i],NULL);
        printf("\nWriter %d joined!\n",i);
    }
    return 0;
}
