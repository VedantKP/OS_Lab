#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int a[SIZE][SIZE],b[SIZE][SIZE],fin[SIZE][SIZE];

void *multiply(void *arg)
{
	int *values,i,j,x,k,z;
	long int endVal=0;
	values=(int *)arg;
	i=values[0];
	j=values[1];
	k=values[2];
	for(x=0;x<k;x++)
	{
		endVal=endVal+a[i][x]*b[x][j];
		printf("\nValue calculated for thread %d-%d :: %d x %d = %d",i,j,a[i][x],b[x][j],endVal);
		z=rand()%10;
		printf("\nThread %d-%d goes to sleep for %d units..\n",i,j,z);
		sleep(z);
		printf("\nThread %d-%d resumed.\n",i,j);
	}
	printf("\n\tThread %d-%d exits!\n",i,j);
	pthread_exit((void*)endVal);
}

void acceptMat(int mat[][SIZE],int r,int c)
{
	int i,j;
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
		{
			printf("Enter value at [%d][%d] => ",i,j);
			scanf("%d",&mat[i][j]);
		}
	printf("\nMatrix input over!\n");	
}

void dispMat(int mat[][SIZE],int r,int c)
{
	int i,j;
	for(i=0;i<r;i++)
	{
		for(j=0;j<c;j++)
		{
			printf("%d\t",mat[i][j]);
		}
		printf("\n");
	}
}

int main()
{
 	int i,j,r1,r2,c1,c2,*status;
 	int matval[3];
 	pthread_t threads[SIZE][SIZE];
 	do
 	{
	 	printf("\nEnter number of rows for matrix 1 => ");
	 	scanf("%d",&r1);
	 	printf("\nEnter number of columns for matrix 1 => ");
	 	scanf("%d",&c1);
	 	printf("\nEnter number of rows for matrix 2 => ");
	 	scanf("%d",&r2);
	 	printf("\nEnter number of columns for matrix 2 => ");
	 	scanf("%d",&c2);
	 	if(r2!=c1)
	 		printf("\nCannot multiply as rows2!=columns1.\nPlease enter again\n\n");
 	}while(r2!=c1);
 	
	acceptMat(a,r1,c1);
 	acceptMat(b,r2,c2);
 	
 	printf("\nEntered matrices are => \n");
 	printf("\nMatrix 1: \n");
 	dispMat(a,r1,c1);
 	printf("\nMatrix 2: \n");
 	dispMat(b,r2,c2);
 	
 	for(i=0;i<r1;i++)
 		for(j=0;j<c2;j++)
		{
			matval[0]=i;
			matval[1]=j;
			matval[2]=c1;
			if(pthread_create(&threads[i][j],NULL,multiply,matval)==0)
			{
				printf("\nThread %d-%d created!\n",i,j);
				sleep(2);
			}	
			else
				printf("\nThread %d-%d not created!\n",i,j);
		}
 	for(i=0;i<r1;i++)
 		for(j=0;j<c2;j++)
		{
 			if(pthread_join(threads[i][j],(void**)&status)==0)
 			{
 				printf("\nThread %d-%d joined!\n",i,j);
 				fin[i][j]=(int)status;
 			}
			else
				perror("\nThread not joined!\n");
		}
		
	printf("\nResultant matrix is:\n");	
	dispMat(fin,r1,c2);	
	exit(EXIT_SUCCESS);	
}
