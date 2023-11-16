/* Illustration of Orphan Process.

 * Program to create orphan process @ Linux
 * getpid() gives process PID and 
 * getppid() gives process's parent ID 
 * here main() process ID is parent id is current shells PID
 * once process becomes orphan it is adopted by init process(it's PID is 1)
 */
  
#include<stdio.h>
#include<unistd.h>

int main()
{
	pid_t p;

	/* create child process */
	p=fork();

 	if(p==0) 
	{
    	/* fork() returns Zero to child */
    	sleep(10);
 	}

	printf("The child process pid is %d parent pid %d\n", getpid(), getppid());
	/*parent/child waits for 20 secs and exits*/
 	sleep(20);
 	printf("\nProcess %d is done its Parent pid %d...\n", getpid(), getppid());

 	return 0;
}



/*
Terminal 1

amol@amol-Aspire-5742:~$ gcc orphan.c
amol@amol-Aspire-5742:~$ ./a.out
The child process pid is 11351 parent pid 11268
The child process pid is 11352 parent pid 11351

Process 11351 is done its Parent pid 11268...
amol@amol-Aspire-5742:~$ 
Process 11352 is done its Parent pid 1566...


Terminal 2

amol@amol-Aspire-5742:~$ ps -elf | grep a.out
0 S amol     11351 11268  0  80   0 -  1127 hrtime 16:20 pts/1    00:00:00 ./a.out
1 S amol     11352 11351  0  80   0 -  1127 hrtime 16:20 pts/1    00:00:00 ./a.out
0 S amol     11354 11324  0  80   0 -  3607 pipe_w 16:21 pts/2    00:00:00 grep --color=auto a.out
amol@amol-Aspire-5742:~$ ps -elf | grep a.out
1 S amol     11352  1566  0  80   0 -  1127 hrtime 16:20 pts/1    00:00:00 ./a.out
0 S amol     11356 11324  0  80   0 -  3607 pipe_w 16:21 pts/2    00:00:00 grep --color=auto a.out
amol@amol-Aspire-5742:~$ 


*/

