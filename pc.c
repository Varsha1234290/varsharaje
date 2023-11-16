// Bounded-Buffer Producer/Consumer Problem with semaphores using multithreading.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TRUE 1
#define BUFFER_SIZE 5

typedef int buffer_item;

buffer_item buffer[BUFFER_SIZE];
// DECLARE THE 3 SEMAPHORES empty, full, AND mutex
int insertPointer = 0, removePointer = 0;

void *producer(void *);
void *consumer(void *);
int insert_item(buffer_item item);
int remove_item(buffer_item *item);


int insert_item(buffer_item item)
{
  	// EXECUTE OPERATION ON empty SEMAPHORE TO WAIT FOR EMPTY SPACE IN BUFFER
  
  	// EXECUTE OPERATION ON mutex SEMAPHORE TO WAIT FOR ACCESS TO CRITICAL
  	// SECTION (I.E., BUFFER) TO INSERT ITEM
  
  	buffer[insertPointer++] = item;
  	insertPointer = insertPointer % 5;

  	// EXECUTE OPERATION ON mutex SEMAPHORE TO RELEASE ACCESS TO CRITICAL SECTION (I.E., BUFFER)
 
  	// EXECUTE OPERATION ON full SEMAPHORE TO SIGNAL AVAILABILITY OF ONE MORE ITEM IN BUFFER
     
  	return 0;
}


int remove_item(buffer_item *item)
{
  	// EXECUTE OPERATION ON full SEMAPHORE TO WAIT FOR ITEM IN BUFFER
  
  	// EXECUTE OPERATION ON mutex SEMAPHORE TO WAIT FOR ACCESS TO CRITICAL
 	// SECTION (I.E., BUFFER) TO REMOVE ITEM
  
 	*item = buffer[removePointer];
  	buffer[removePointer++] = -1;
  	removePointer = removePointer % 5;

  	// EXECUTE OPERATION ON mutex SEMAPHORE TO RELEASE ACCESS TO CRITICAL SECTION (I.E., BUFFER)
 
  	// EXECUTE OPERATION ON empty SEMAPHORE TO SIGNAL AVAILABILITY OF ONE MORE FREE SPACE IN BUFFER
 
  	return 0;
}


int main(int argc, char *argv[])
{
  	int sleepTime, producerThreads, consumerThreads;
  	int i, j;

  	if(argc != 4)
   	{
      	fprintf(stderr, "Usage: <sleep time> <producer threads> <consumer threads>\n");
      	return -1;
    	}

  	sleepTime = atoi(argv[1]);
  	producerThreads = atoi(argv[2]);
  	consumerThreads = atoi(argv[3]);

  	// INITIALIZE THE THREE SEMAPHORES
 
 
  	srand(time(0));

  	//Create the producer and consumer threads

  	for(i = 0; i < producerThreads; i++)
    	{
      	pthread_t tid;
      	pthread_attr_t attr;
      	pthread_attr_init(&attr);
      	pthread_create(&tid, &attr, producer, NULL);
    	}

  	for(j = 0; j < consumerThreads; j++)
    	{
      	pthread_t tid;
      	pthread_attr_t attr;
      	pthread_attr_init(&attr);
      	pthread_create(&tid, &attr, consumer, NULL);
    	}

  	//Sleep for user specified time
  	sleep(sleepTime);
  	return 0;
}


void *producer(void *param)
{
  	buffer_item random;
  	int r;

  	while(TRUE)
    	{
      	r = rand() % 5;
      	sleep(r);
      	random = rand();

      	if(insert_item(random))
       	fprintf(stderr, "Error");

      	printf("Producer produced %d \n", random);

    	}

}


void *consumer(void *param)
{
  	buffer_item random;
  	int r;

  	while(TRUE)
    	{
      	r = rand() % 5;
     	 sleep(r);

      	if(remove_item(&random))
       	fprintf(stderr, "Error Consuming");
      	else
     	printf("Consumer consumed %d \n", random);
    	}
}
 

/*
amol@amol-Aspire-5742:~$ gcc pc.c -lpthread
amol@amol-Aspire-5742:~$ ./a.out
Usage: <sleep time> <producer threads> <consumer threads>
amol@amol-Aspire-5742:~$ ./a.out 10 2 2
Producer produced 1961815286 
Producer produced 777221283 
Consumer consumed 1961815286 
Consumer consumed 777221283 
Producer produced 1556644843 
Producer produced 2026234110 
Consumer consumed 1556644843 
Producer produced 377326796 
Producer produced 1519773066 
Producer produced 509349146 
Producer produced 547445997 
Consumer consumed 2026234110 
Consumer consumed 377326796 
Producer produced 1859857603 
Producer produced 710668389 
Consumer consumed 1519773066 
Producer produced 831015041 
Consumer consumed 509349146 
amol@amol-Aspire-5742:~$ 

*/ 
