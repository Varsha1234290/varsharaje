/* Illustration of Zombie Process. */

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main ()
{
  pid_t child_pid;

  child_pid = fork ();

  	if(child_pid > 0) 
	{
    	sleep (60);
  	}
  	else 
	{
    	exit (0);
  	}
  return 0;
}




/*
Terminal 1

amol@amol-Aspire-5742:~$ gcc zombie.c
amol@amol-Aspire-5742:~$ ./a.out
^C
amol@amol-Aspire-5742:~$ 


Terminal 2
Now check the output of this command (within 1 minute) in another window:

ps -e -o pid,ppid,stat,cmd

*/
