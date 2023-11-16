#include<stdio.h>
#include<stdlib.h>

void  fcfs(int n,int re[],int m);
void  sstf(int n,int re[],int m);
void cscan(int n,int re[],int m);

void main()
{
	int n,i,re[999]={0},m,ch;
	
	printf("\n Enter total no of Tracks:");
	scanf("%d",&n);

	printf("Enter Requested Track No.s:-\n");
	for(i=0;i<n;i++)
	scanf("%d",&re[i]);

	printf("\n Enter Initial Head Position:-");
	scanf("%d",&m);
	do
	{
		
		printf("\n\n***********SCHEDULING ALGORITHM*****************");
		printf("\n 1.FCFS");
		printf("\n 2.SSTF");
		printf("\n 3.C-SCAN");
		printf("\n 4.EXIT");
		printf("****************************************************");
		printf("\n\nEnter your Choice:-");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:fcfs(n,re,m);
			       break;
			case 2:sstf(n,re,m);
			       break;
			case 3:cscan(n,re,m);
			       break;
			case 4:exit(0);
			       break;

			default:printf("Wrong choice Entered...");
				break;
		}
	}while(ch=4);
}

void fcfs(int n,int re[999],int m)
{
	int ac[999],i,st[999],j,seek=0;
	j=m;
	st[0]=abs(j-re[0]);
	ac[0]=re[0];
	for(i=1;i<n;i++)
	{
		ac[i]=re[i];
		st[i]=abs(re[i]-re[i-1]);
	}
	
	printf("\n\n---------------------------------------------------");
	printf("\n Received Tracks\tAccessed Tracks\t\tSteps Required");
	for(i=0;i<n;i++)
	printf("\n\t%d\t\t\t%d\t\t\t%d",re[i],ac[i],st[i]);
	printf("\n\n---------------------------------------------------");
	printf("\n Total Seek Time");
	for(i=0;i<n;i++)
	seek=st[i]+seek;
	printf("\t%d",seek);
	printf("\n----------------------------------------------------");

}

void sstf(int n,int re[999],int m)
{
	int temp[999],z=0,i,j,seek=0,st[999],ac[999],k,b[999]={0},min,pos;
	k=m;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(b[j]==0)
			temp[j]=abs(re[j]-k);
			else
			temp[j]=999;
		}
		min=999;
		for(j=0;j<n;j++)
		{
			if(min>temp[j])
			min=temp[j];
		}
		for(j=0;j<n;j++)
		{
			if(min==temp[j])
			{
				pos=j;
				break;
			}
		}
		b[pos]=1;
		ac[z]=re[pos];
		st[z]=abs(k-re[pos]);
		z++;
		k=re[pos];
	}
	
	printf("\n\n--------------------------------------------------");
	printf("\n Received Tracks\tAccessed Tracks\t\tSteps Required");
	printf("\n----------------------------------------------------------");
	for(i=0;i<n;i++)
	printf("\n\t%d\t\t\t%d\t\t\t%d",re[i],ac[i],st[i]);
	printf("\n\n---------------------------------------------------");
	printf("\n Total Seek Time");
	for(i=0;i<n;i++)
	seek=st[i]+seek;
	printf("\t%d",seek);
	printf("\n----------------------------------------------------------");
}

void cscan(int n,int re[],int m)
{
	int z=0,i,j,seek=0,min,st[999],ac[999],k,b[999]={0},ch,o;
	k=m;
	printf("\n\n\n**********DIRECTION OF HEAD MOVEMENT************");
	printf("\n1:-HEAD IS MOVING IN REVERSE DIRECTION");
	printf("\n2:-HEAD IS MOVING IN FORWARD DIRECTION");
	printf("\n****************************************************");
	printf("\n\nENter Your Choice:-");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:for(i=0;i<n;i++)
		       for(j=0;j<n;j++)
		       {
				if(re[i]>re[j] && min>re[j])
				min=re[j];
		       }
		       o=min*2;
		       for(i=m;i<999;i++)
		       {
				for(j=0;j<n;j++)
				{
					if(b[j]==0 && re[j]==i)
					{
						ac[z]=re[j];
						st[z]=abs(re[j]-k);
						k=re[j];
						b[j]=1;
						z++;
					}
				}
				if(z==n)
				break;
		       }
		       for(i=0;i<999;i++)
		       {
				for(j=0;j<n;j++)
				{
					if(b[j]==0 && re[j]==i)
					{
						ac[z]=re[j];
						st[z]=abs(re[j]-k)+o;
						k=re[j];
						b[j]=1;
						z++;
						o=0;
					}
				}
				if(z==n)
				break;
		       }
		case 2:for(i=m;i>=0;i++)
		       {
				for(j=0;j<n;j++)
				{
					if(b[j]==0 && re[j]==i)
					{
						ac[z]=re[j];
						st[z]=abs(re[j]-k);
						k=re[j];
						b[j]=1;
						z++;
					}
				}
				if(z==n)
				break;
		       }
		       o=2*ac[z-1];
		       for(i=999;i>0;i--)
		       {
				for(j=0;j<n;j++)
				{
					if(b[j]==0 && re[j]==i)
					{
						ac[z]=re[j];
						st[z]=abs(re[j]-k)+o;
						k=re[j];
						b[j]=1;
						z++;
						o=0;
					}
				}
				if(z==n)
				break;
		       }

		default: printf("\n Wrong choice Entered...");
			 break;
	}
	
	printf("\n\n--------------------------------------------------");
	printf("\n Received Tracks\tAccessed Tracks\t\tSteps Required");
	printf("\n----------------------------------------------------------");
	for(i=0;i<n;i++)
	printf("\n\t%d\t\t\t%d\t\t\t%d",re[i],ac[i],st[i]);
	printf("\n\n---------------------------------------------------");
	printf("\n Total Seek Time");
	for(i=0;i<n;i++)
	seek=st[i]+seek;
	printf("\t%d",seek);
	printf("\n----------------------------------------------------------");
}



