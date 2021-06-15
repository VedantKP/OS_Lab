#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

typedef struct
{
	char name[30], branch[10];
	int roll;
}employee;

void insert()
{
	int fd, num, i, wr, flag=1;
	employee s;
	fd = open("myfile.txt",O_CREAT, S_IRUSR|S_IWUSR);
	close(fd);
	
	fd = open("myfile.txt",O_WRONLY|O_APPEND, S_IRUSR|S_IWUSR);
	
	if(fd<0)
	{
		printf("\nError in opening the file. ");
		return;
	}
	
	printf("\nEnter the no. of records you want to insert:: ");
	scanf("%d",&num);
	
	for(i=0; i<num; i++)
	{
		printf("\nRecord %d: ",(i+1));
		printf("\nEnter Roll No. : ");
		scanf("%d",&s.roll);
		printf("\nEnter the Name : ");
		scanf("%s",s.name);
		printf("\nEnter the Branch:: ");
		scanf("%s",s.branch);
		
		wr = write(fd, &s, sizeof(s));
		if(wr<0)
		{
			printf("\nError in writing data to the file.");
			flag = 0;
		}
	}
	
	if(flag)								
	{
		printf("\nData has been inserted successfully!");
	}	
					
	close(fd);
	
	
}

void display()
{
	int fd, rd;
	employee s;
	
	fd = open("myfile.txt", O_RDONLY, S_IRUSR);
	
	if(fd<0)
	{
		printf("\nError in opening the file. ");
		return;
	}
	rd = read(fd, &s, sizeof(s));
	if(rd<=0)
	{
		printf("\nFile is empty!");
		return;
	}
	printf("\nRoll No. \t Name \t\t Branch ");
	while(rd>0)
	{
		printf("\n%d \t\t %s \t\t %s",s.roll,s.name,s.branch);
		rd = read(fd, &s, sizeof(s));
	}
	close(fd);
}

void modify()
{
	int fd1, fd2, rd, wr, r, flag=0;
	employee s;
		
	fd1 = open("myfile.txt", O_EXCL|O_RDONLY);
	fd2 = open("temp.txt", O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR);
	
	if(fd1<0 || fd2<0)
	{
		printf("\nError in opening the file.");
		return;
	}
	
	printf("\nEnter the roll no. of the record you want to modify: ");
	scanf("%d",&r);
	
	rd = read(fd1, &s, sizeof(s));
	if(rd<=0)
	{
		printf("\nFile is empty! Modification is not possible!");
		return;
	}
	while(rd>0)
	{
		if(s.roll == r)
		{
			flag = 1;
			
			printf("\nEnter the modified details: ");
			printf("\nEnter the roll no.:: ");
			scanf("%d",&s.roll);
			printf("\nEnter the name:: ");
			scanf("%s",s.name);
			printf("\nEnter the branch:: ");
			scanf("%s",s.branch);
			
			wr = write(fd2, &s, sizeof(s));
		}
		else
		{
			wr = write(fd2, &s, sizeof(s));
		}
		rd = read(fd1, &s, sizeof(s));
	}
	
	if(flag)
	{
		printf("\nModification was carried out successfully!");
	}
	else
	{
		printf("\nModification was unsuccessful!");
	}
	
	close(fd1);
	close(fd2);
	remove("myfile.txt");
	rename("temp.txt","myfile.txt");
}

void delete()
{
	int fd1, fd2, rd, wr, r, flag=0;
	employee s;
	
	fd1 = open("myfile.txt", O_EXCL|O_RDONLY);
	fd2 = open("temp.txt", O_CREAT|O_WRONLY);
	
	if(fd1<0 || fd2<0)
	{
		printf("\nError in opening the file!");
		return;
	}
	
	printf("\nEnter the roll no. of the record you want to delete:: ");
	scanf("%d",&r);
	
	rd = read(fd1, &s, sizeof(s));
	
	if(rd<=0)
	{
		printf("\nFile is empty! Deletion was unsuccessful!");
		return;
	}
	while(rd>0)
	{
		if(s.roll==r)
		{
			flag = 1;
		}
		else
		{
			wr = write(fd2, &s, sizeof(s));
		}
		rd = read(fd1, &s, sizeof(s));
	}
	close(fd1);
	close(fd2);
	if(flag)
	{	
		printf("\nDeletion was performed successfully!");
	}
	else
	{
		printf("\nDeletion operation was unsuccessful!");
	}
	remove("myfile.txt");
	rename("temp.txt","myfile.txt");
}

int main()
{
	int choice;
	
	do
	{
		printf("\n\n\t\tMENU\n\n\t1.Insert\n\t2.Display\n\t3.Modify\n\t4.Delete\n\t5.Exit\n\n\t\tEnter Choice :");
		scanf("%d",&choice);
		
		switch(choice)
		{
		case 1:
			printf("\nTo insert data into the file: ");
			insert();
			break;
			
		case 2:
			printf("\nDisplaying the contents of the file: ");
			display();
			break;
			
		case 3:
			printf("\nTo modify a record: ");
			modify();
			break;
			
		case 4:
			printf("\nTo delete a record: ");
			delete();
			break;
			
		case 5:
			printf("\nYou have chosen to exit!");
			return 0;
		}
	}while(1);
}

