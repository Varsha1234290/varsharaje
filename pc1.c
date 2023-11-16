#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<semaphore.h>

sem_t empty,full,mutex;

char buff[10];

void *produce_item(void *arg)
{
	int i;
	printf("\nInside producer:\n");
	for(i=0;i<10;i++)
	{
		sem_wait(&empty);
		sem_wait(&mutex);
		buff[i]=i;
		printf("\nProduced item is :%d\n",buff[i]);
		sem_post(&mutex);
		sem_post(&full);
		sleep(1);
	}
	pthread_exit("producer:\n");
}

void *consume_item(void *arg)
{
	int j;
	printf("\nInside consumer:\n");
	for(j=0;j<10;j++)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		j=buff[j];
		printf("\nConsumed item is:%d\n",buff[j]);
		sem_post(&mutex);
		sem_post(&empty);
		sleep(5);
	}
	pthread_exit("Consumer\n");
}

int main()
{
	pthread_t t_id1,t_id2;
	
	sem_init(&empty,0,10);
	sem_init(&full,0,0);
	sem_init(&mutex,1,1);
	
	void *status;
	pthread_create(&t_id1,NULL,produce_item,NULL);
	pthread_create(&t_id2,NULL,consume_item,NULL);

	pthread_join(t_id1,&status);
	printf("\nThe exited status is %s\n",(char*)status);

	pthread_join(t_id2,&status);
	printf("\nThe exited status is %s\n",(char*)status);

	return 0;
}

/* 
amol@amol-Aspire-5742:~$ gcc pc1.c -lpthread
amol@amol-Aspire-5742:~$ ./a.out

Inside producer:

Produced item is :0

Inside consumer:

Consumed item is:0

Produced item is :1

Produced item is :2

Produced item is :3

Produced item is :4

Consumed item is:1

Produced item is :5

Produced item is :6

Produced item is :7

Produced item is :8

Produced item is :9

Consumed item is:2

The exited status is producer:


Consumed item is:3

Consumed item is:4

Consumed item is:5

Consumed item is:6

Consumed item is:7

Consumed item is:8

Consumed item is:9

The exited status is Consumer

*/
