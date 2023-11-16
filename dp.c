// Implement Dining Philosopher Problem using POSIX threads and Semaphores.

#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

void philosopher(int);
sem_t chopstick[5]={1};
int i=0,j=0,count;

int main()
{
pthread_t th1,th2,th3,th4,th5;
for(i=0;i<5;i++)
sem_init(&chopstick[i],0,1);
i=0;

pthread_create(&th1,NULL,(void*)philosopher,(void*)i);
i++;
pthread_create(&th2,NULL,(void*)philosopher,(void*)i);
i++;
pthread_create(&th3,NULL,(void*)philosopher,(void*)i);
i++;
pthread_create(&th4,NULL,(void*)philosopher,(void*)i);
i++;
pthread_create(&th5,NULL,(void*)philosopher,(void*)i);

pthread_join(th1,NULL);
pthread_join(th2,NULL);
pthread_join(th3,NULL);
pthread_join(th4,NULL);
pthread_join(th5,NULL);
}


void philosopher(int i)
{
printf("\n Philosopher %d is thinking.......",i+1);
sleep(2);
printf("\n Philosopher %d is waiting for 1st fork",i+1);
sem_wait(&chopstick[i]);
printf("\n Philosopher %d is waiting for 2nd fork",i+1);
sem_wait(&chopstick[(i+1)%5]);
printf("\n Philosopher %d is eating...",i+1);
sleep(2);
printf("\n Philosopher %d has put down 2nd fork...",i+1);
sem_post(&chopstick[i]);
printf("\n Philosopher %d has put down 1st fork....",i+1);
sem_post(&chopstick[i]);
printf("\n Philosopher %d completed eating..",i+1);
}

/* Output
amol@amol-Aspire-5742:~$ gcc dp.c -lpthread
dp.c: In function ‘main’:
dp.c:19:45: warning: cast to pointer from integer of different size [-Wint-to-pointer-cast]
 pthread_create(&th1,NULL,(void*)philosopher,(void*)i);
                                             ^
dp.c:21:45: warning: cast to pointer from integer of different size [-Wint-to-pointer-cast]
 pthread_create(&th2,NULL,(void*)philosopher,(void*)i);
                                             ^
dp.c:23:45: warning: cast to pointer from integer of different size [-Wint-to-pointer-cast]
 pthread_create(&th3,NULL,(void*)philosopher,(void*)i);
                                             ^
dp.c:25:45: warning: cast to pointer from integer of different size [-Wint-to-pointer-cast]
 pthread_create(&th4,NULL,(void*)philosopher,(void*)i);
                                             ^
dp.c:27:45: warning: cast to pointer from integer of different size [-Wint-to-pointer-cast]
 pthread_create(&th5,NULL,(void*)philosopher,(void*)i);
                                             ^
amol@amol-Aspire-5742:~$ ./a.out

 Philosopher 2 is thinking.......
 Philosopher 1 is thinking.......
 Philosopher 5 is thinking.......
 Philosopher 4 is thinking.......
 Philosopher 3 is thinking.......
 Philosopher 2 is waiting for 1st fork
 Philosopher 2 is waiting for 2nd fork
 Philosopher 2 is eating...
 Philosopher 1 is waiting for 1st fork
 Philosopher 1 is waiting for 2nd fork
 Philosopher 5 is waiting for 1st fork
 Philosopher 5 is waiting for 2nd fork
 Philosopher 3 is waiting for 1st fork
 Philosopher 4 is waiting for 1st fork
 Philosopher 4 is waiting for 2nd fork
 Philosopher 2 has put down 2nd fork...
 Philosopher 2 has put down 1st fork....
 Philosopher 2 completed eating..
 Philosopher 1 is eating...
 Philosopher 1 has put down 2nd fork...
 Philosopher 1 has put down 1st fork....
 Philosopher 1 completed eating..
 Philosopher 5 is eating...
 Philosopher 5 has put down 2nd fork...
 Philosopher 5 has put down 1st fork....
 Philosopher 5 completed eating..
^Z
[4]+  Stopped                 ./a.out
amol@amol-Aspire-5742:~$ 
*/
