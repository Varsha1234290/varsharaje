/*
================================================================================================
 
 Problem Statement : Process control system calls: The demonstration of fork, execve and
			   		 wait system calls along with zombie and orphan states.
			   
						b. Implement the C program in which main program accepts an integer array. 
			   	 		Main program uses the fork system call to create a new process called a 
			   	 		child process. Parent process sorts an integer array and passes the sorted
			   	 		array to child process through the command line arguments of execve system 
			   	 		call. The child process uses execve system call to load new program that 
			   	 		uses this sorted array for performing the binary search to search the 
			   	 		particular item in the array.				  	
================================================================================================
*/




#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 

int main(int argc, char *argv[]) 
{ 
int val[10],ele; 
pid_t pid; 
char* cval[10]; 
char *newenviron[] = { NULL }; 
int i,j,n,temp; 

printf("\nEnter the size for an array: "); 
scanf("%d",&n); 

printf("\nEnter %d elements : ", n); 
  for(i=0;i<n;i++) 
  scanf("%d",&val[i]); 
     
  printf("\nEntered elements are: "); 
  for(i=0;i<n;i++) 
  printf("\t%d",val[i]); 

   for(i=1;i<n;i++) 
   { 
   for(j=0;j<n-1;j++) 
   { 
   if(val[j]>val[j+1]) 
   { 
   temp=val[j]; 
   val[j]=val[j+1]; 
   val[j+1]=temp; 
    } 
    } 
    } 
  printf("\nSorted elements are: "); 
  for(i=0;i<n;i++) 
  printf("\t%d",val[i]); 

  printf("\nEnter element to search: "); 
  scanf("%d",&ele); 
  val[i] = ele; 
  for (i=0; i < n+1; i++) 
  {    
   char a[sizeof(int)];     
   snprintf(a, sizeof(int), "%d", val[i]); 

   cval[i] = malloc(sizeof(a)); 
   strcpy(cval[i], a); 
  }    
  cval[i]=NULL; 
         
  pid=fork(); 
  if(pid==0) 
  { 
  execve(argv[1], cval, newenviron); 
 perror("Error in execve call..."); 
 } 
} 


/* OUTPUT

amol@amol-Aspire-5742:~$ gcc main-sort.c -o main
amol@amol-Aspire-5742:~$ gcc search.c -o search
amol@amol-Aspire-5742:~$ ./main ./search

Enter the size for an array: 5

Enter 5 elements : 100
23
10
5
85

Entered elements are: 	100	23	10	5	85
Sorted elements are: 	5	10	23	85	100
Enter element to search: 23
amol@amol-Aspire-5742:~$ 
Element Found in the given Array...!!!
 */
