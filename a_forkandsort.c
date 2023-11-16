/*
================================================================================================
 Name        	   : a_forkandsort.c
 
 Problem Statement : Process control system calls: The demonstration of fork, execve and
		     wait system calls along with zombie and orphan states.
			   
		     a. Implement the C program in which main program accepts the integers to be sorted. 
			Main program uses the fork system call to create a new process called a child process. 
			Parent process sorts the integers using merge sort and waits for child process using wait system call to sort the 				integers using quick sort. Also demonstrate zombie and orphan state.						  	
================================================================================================
*/

#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h>    
#include <stdlib.h>    
#include <unistd.h>  

void quicksort(int [10],int,int);
void main()
{
	int pid, ppid, a[10], size, i;

	printf("\nPARENT: My process-id is %d.", getpid());
	
	printf("\n\nEnter the number of elements in the array: ");
	scanf("%d", &size);
	printf("Enter %d elements: ", size);
  	for(i=0;i<size;i++)
    	scanf("%d",&a[i]);
	
	printf("\nForking now!\n");

	pid = fork();			//Here, the child process is created and both child & parent run 
							//simultaneously. fork() returns 0 to child process and pid of 								//child to parent process. So, if int pid here is 0, it means we 								//are in child process and if any +ve no., then in parent process 								//where the +ve no. is the child's pid.
	if(pid==0)
	{
		printf("\nCHILD: My process-id is %d.", getpid());
		printf("\nCHILD: My parent's process-id is %d.", getppid());
		quicksort(a, 0, size-1);
		
		printf("\n Sorting elements using Quick Sort: ");
 		for(i=0;i<size;i++)
    		printf(" %d",a[i]);
		
		printf("\nCHILD: I am dying now");
		printf("\n-------------------------------------------------------");
		//	ORPHAN
		printf("\nCHILD: I am sleeping now.");
		sleep(10);
		printf("\n-------------------------------------------------------\n\n");
		system("ps -elf | grep a.out");

		/*  ZOMBIE
		printf("\nCHILD: I am dying now");
		printf("\n-------------------------------------------------------\n\n");
		system("ps -elf | grep a.out");
		exit(0);*/
	}
	else if (pid>0)
	{
		system("wait");
		printf("\nPARENT: I am back. ");
		printf("\nPARENT: My process-id is %d.", getpid());	
		printf("\nPARENT: My child's process-id is %d.", pid);
		quicksort(a, 0, size-1);
		
		printf("\nSorted elements: ");
 		for(i=0;i<size;i++)
    		printf(" %d",a[i]);
		
		printf("\nPARENT: I am dying now.");
		printf("\n-------------------------------------------------------");
		//  ORPHAN
		system("ps -elf | grep a.out");
		exit(0);

		/* ZOMBIE
		printf("\nPARENT: I am sleeping now.");
		sleep(10);
		printf("\n-------------------------------------------------------\n");
		system("ps -elf | grep a.out");*/
	}
}

void quicksort(int a[10],int first,int last)
{
    int pivot,j,temp,i;

    if(first<last)
	{
		pivot=first;
        i=first;
        j=last;

        while(i<j){
            while(a[i]<=a[pivot]&&i<last)
                i++;
            while(a[j]>a[pivot])
                j--;
            if(i<j){
				temp=a[i];
                a[i]=a[j];
                a[j]=temp;
             }
         }

         temp=a[pivot];
         a[pivot]=a[j];
         a[j]=temp;
         quicksort(a,first,j-1);
         quicksort(a,j+1,last);
    }
}


/*
====================================OUTPUT====================================
amol@amol-Aspire-5742:~$ gcc a_forkandsort.c
amol@amol-Aspire-5742:~$ ./a.out

PARENT: My process-id is 12668.

Enter the number of elements in the array: 4
Enter 4 elements: 123
4
67
0

Forking now!

CHILD: My process-id is 12669.
CHILD: My parent's process-id is 12668.
 Sorting elements using Quick Sort:  0 4 67 123
CHILD: I am dying now
-------------------------------------------------------

PARENT: I am back. 
PARENT: My process-id is 12668.
PARENT: My child's process-id is 12669.
Sorted elements:  0 4 67 123
PARENT: I am dying now.
0 S amol     12668 12645  0  80   0 -  1128 wait   16:53 pts/1    00:00:00 ./a.out
1 S amol     12669 12668  0  80   0 -  1128 hrtime 16:53 pts/1    00:00:00 ./a.out
0 S amol     12671 12668  0  80   0 -  1157 wait   16:53 pts/1    00:00:00 sh -c ps -elf | grep a.out
0 S amol     12673 12671  0  80   0 -  3607 pipe_w 16:53 pts/1    00:00:00 grep a.out
amol@amol-Aspire-5742:~$ CHILD: I am sleeping now.
-------------------------------------------------------

1 S amol     12669  1566  0  80   0 -  1128 wait   16:53 pts/1    00:00:00 ./a.out
0 S amol     12674 12669  0  80   0 -  1157 wait   16:53 pts/1    00:00:00 sh -c ps -elf | grep a.out
0 S amol     12676 12674  0  80   0 -  3607 pipe_w 16:53 pts/1    00:00:00 grep a.out


^C
amol@amol-Aspire-5742:~$ 


*/

