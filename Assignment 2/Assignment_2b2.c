#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*program applies binary search to search for
an element from a sorted array of numbers.
*/

int main(int argc,char *argv[])
{
	int num[10],i,x,lb=0,ub=argc-1,mid,f;
	char str[10];
	printf("\nEnter number to be searched => ");
	scanf("%d",&x);
	for(i=0;i<argc;i++)
		num[i]=atoi(argv[i]);
	while(lb<=ub)
	{
		mid=(lb+ub)/2;
		if(x==num[mid])
		{
			printf("Number %d found at position => %d\n",x,mid);
			break;
		}
		else if(x>num[mid])
			lb=mid+1;
		else ub=mid-1;			
	}
	if(lb>ub)
		printf("\nNumber not found!\n");
	return 0;
}
