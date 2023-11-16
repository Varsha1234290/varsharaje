/*      
   Deadlock Avoidance using Banker's Algorithm 
*/


#include<stdio.h>

int n, m, available[10], max[10][10], allocation[10][10], need[10][10],
    work[5], ss[10], s = 0;
char finish[10];

int SS ();
void rr ();

main ()
{
  int i, j, ch;
  printf("------------===============Banker`s Algorithm====================------------\n");
  printf ("\n Enter no. of processes : ");
  scanf ("%d", &n);
  printf ("Enter no. of resource Types : ");
  scanf ("%d", &m);
  printf ("Enter no. of available resources of each type: \n");
  for (i = 0; i < m; i++)
    {
      printf ("Resource-%c : ", i + 65);
      scanf ("%d", &available[i]);
    }
  printf ("Enter Maximum Demand of each process : \n");
  for (i = 0; i < n; i++)
    {
      finish[i] = 'F';
      printf ("For Process P%d : ", i);
      for (j = 0; j < m; j++)
	scanf ("%d", &max[i][j]);
    }
  printf ("Enter Allocation of each process : \n");
  for (i = 0; i < n; i++)
    {
      printf ("For Process P%d : ", i);
      for (j = 0; j < m; j++)
	scanf ("%d", &allocation[i][j]);
    }
  printf ("Calculation of Need matrix\n");
  for (i = 0; i < n; i++)
    {
      for (j = 0; j < m; j++)
	need[i][j] = max[i][j] - allocation[i][j];
    }
  printf ("--------Need Matrix---------\n");
  for (i = 0; i < n; i++)
    {
      for (j = 0; j < m; j++)
	printf ("%d", need[i][j]);
      printf ("\n");
    }
  do
    {
      printf ("***************MENU*************\n");
      printf ("\t1 : Safe Sequence\n\t2 : Resource Request\n\t3 : Exit\n");
      printf ("Enter your choice : ");
      scanf ("%d", &ch);
      switch (ch)
	{
	case 1:
	  SS ();
	  break;
	case 2:
	  rr ();
	  break;
	
	}
    }
  while (ch != 3);
}
 //----------------------------------------------------------------------------
int SS ()
{
  int i, j, flag = 0, k, s = 0;
  for (i = 0; i < m; i++)
    work[i] = available[i];
  for (i = 0; i < n; i++)
    finish[i] = 'F';
  j = 2;
  while (j > 0)
    {
      for (i = 0; i < n; i++)
	{
	  if (finish[i] == 'F')
	    {
	      for (k = 0; k < m; k++)
		{
		  if (need[i][k] <= work[k])
		    continue;
		  else
		    break;
		}
	      if (k == m)
		{
		  printf ("Process P[%d] over\nFinish[",i);
		  finish[i] = 'T';
		  for (k = 0; k < n; k++)
		    printf ("%c", finish[k]);
		  printf ("]-----------------------\n");
		  for (k = 0; k < m; k++)
		    work[k] += allocation[i][k];
		  ss[s++] = i;
		}
	    }
	}
      j = j - 1;
    }
  for (i = 0; i < n; i++)
    {
      if (finish[i] == 'T')
	continue;
      else
	break;
    }
  if (i <= n)
    {
      printf ("System is in safe state\n<");
      for (i = 0; i < s; i++)
	printf ("P%d,", ss[i]);
      printf (">\n");
      return 1;
    }
  else
    printf ("System is not in safe state\n");
  return 0;
}
//Code for Resource Request Algorithm

void rr ()
{
  int i, j, flag, flag1, reply, request[10];
  printf ("Enter process no : ");
  scanf ("%d", &i);
  printf ("Enter the request : ");
  for (j = 0; j < m; j++)
    scanf ("%d", &request[j]);
  for (flag = 0, j = 0; j < m; j++)
    if (request[j] > need[i][j])
      flag = 1;
  if (flag == 0)
    {
      for (flag1 = 0, j = 0; j < m; j++)
	if (request[j] > available[j])
	  flag = 1;
      if (flag1 == 0)
	{
	  for (j = 0; j < m; j++)
	    {
	      available[j] -= request[j];
	      allocation[i][j] += request[j];
	      need[i][j] -= request[j];
	    }
	  reply = SS ();
	  if (reply==1)
	    printf ("Process P%d is allocated it`s resources\n", i);
	  else
	    printf ("Process P%d must wait for resources\n", i);
	}
        else 
     	printf("Process P%d must wait, since the resources are not available\n",i);
    }
  else
    printf("Process P%d has exceeded it's maximum claim\n",i);
}


