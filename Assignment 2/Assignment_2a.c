#include <stdio.h>
#include <stdlib.h>

void input(int* num,int n)
{
	int i;
	printf("\nINPUT");
	for(i=0;i<n;i++)
	{
		printf("\nEnter num[%d] : ",i);
		scanf("%d",&num[i]);
	}
	printf("\n\nInput over!\n");
}

void swap(int* a,int* b)   
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  

int partition(int *arr,int low,int high)  
{  
    int pivot = arr[high]; // pivot  
    int i = (low - 1); // Index of smaller element  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is SL2 smaller than or  
        // equal to pivot  
        if (arr[j] <= pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
  
void quickSort(int *arr, int low, int high)  
{  
    if (low < high)  
    {  
     
        int pi = partition(arr, low, high);  

        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}  

void sel_sort(int *num,int n)
{
	int i,j,min,temp;
	for(i=0;i<n;i++)
	{
		min=i;
		for(j=i+1;j<n;j++)
		{
			if(num[j]<num[min])
				min=j;
		}
		if(min!=i)
		{
			temp=num[i];
			num[i]=num[min];
			num[min]=temp;
		}
	}
	printf("Sorting over\n");
	printf("\n");
}

int main()
{
	int *num1,*num2,n,i;
	printf("\n\n***SORTING***\n");
	printf("\nEnter total numbers you wish to enter => ");
	scanf("%d",&n);
	num1=(int*)malloc(n*sizeof(int));
	num2=(int*)malloc(n*sizeof(int));
	input(num1,n);
	printf("\nArray1 is => ");
	for(i=0;i<n;i++)
		printf("%d, ",num1[i]);
	printf("\n");
	input(num2,n);
	printf("\nArray2 is => ");
	for(i=0;i<n;i++)
		printf("%d, ",num2[i]);
	printf("\n");
	int pid;
	pid=fork();
	if(pid==0)
	{
		printf("\nIn child!\n");
		printf("\nID of process : %d\n",getpid());
		printf("\nID of process' parent : %d\n",getppid());
		printf("\nSorting in child process using quick sort\n");
		quickSort(num1,0,n-1);
		printf("\nSorted array is => ");
		for(i=0;i<n;i++)
			printf("%d, ",num1[i]);
		printf("\n");
		printf("\nSorting in child process finished\n");
		printf("\nExiting child process\n");
	}
	else
	{
		printf("\nIn parent!\n");
		printf("\nID of process : %d\n",getpid());
		printf("\nID of process' parent : %d\n",getppid());
		printf("\nSorting in parent process using selection sort\n");
		sel_sort(num2,n);
		printf("\nsorted array is => ");
		for(i=0;i<n;i++)
			printf("%d, ",num2[i]);
		printf("\n");
		printf("\nSorting in parent process finished\n");
		printf("\nEntering wait state\n");
		wait();
		printf("\nchild finished execution\n");
		printf("\nExit\n");	
		exit(0);
	}
	printf("\n");
	return 0;	
}
