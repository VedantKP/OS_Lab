#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*
	program: 1.Inputs and sorts integer array
			 2.Creates child process and converts integer number into strings
			 3.Executes execve command to transfer control to another program. 
			   The other program implements binary search.
			 4.Program returns back to parent process ignoring remaining contents
			   of child.
			 5.End  
*/

void sel_sort(int n[],int size)
{
	int i,j,min;
	for(i=0;i<size;i++)
	{
		min=i;
		for(j=i+1;j<size;j++)
		{
			if(n[j]<n[min])
				min=j;
		}
		if(min!=i)
		{
			int temp;
			temp=n[min];
			n[min]=n[i];
			n[i]=temp;
		}
	}
}

int main()
{
	int num[10],i,size;
	char str[10],*arg[10];
	pid_t c_id,p_id;
	printf("\nEnter number of digits => ");
	scanf("%d",&size);
	for(i=0;i<size;i++)
	{
		printf("\nEnter number[%d] => ",i);
		scanf("%d",&num[i]);
	}
	printf("\n---------------");
	printf("\n| Input Over! |");
	printf("\n---------------\n");
	printf("\nEntered array => ");
	for(i=0;i<size;i++)
		printf("%d, ",num[i]);
	printf("\n\n-----------");
	printf("\n| Sorting |\n");
	printf("-----------\n\n");
	sleep(2);
	sel_sort(num,size);
	p_id=fork();
	if(p_id==0)
	{
		printf("\nIn child process\n");
		printf("\nID of child process is => %d\n ",getpid());
		printf("\nID of child's parent => %d\n",getppid());
		printf("\nSorted array is => ");
		for(i=0;i<size;i++)
		{
			printf("%d, ",num[i]);
			sprintf(str,"%d",num[i]);
			arg[i]=malloc(sizeof(str));
			strcpy(arg[i],str);
		}
		printf("\n");	
		arg[i]=NULL;
		printf("\nExecuting execve\n");
		execve("./2b2",arg,NULL);
		printf("\n\nThis won't be printed as we will return from ./2b2 to the parent process\n");
	}
	else
	{
		printf("\nIn parent process\n");
		printf("\nProcess ID => %d\n",getpid());
		printf("\nEntering child\n");
		wait();
		printf("\nBack to parent process\n");
		printf("\nExiting parent\n");
		exit(0);	
	}
	return 0;
}
