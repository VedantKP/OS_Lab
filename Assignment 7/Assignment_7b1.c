//Filename: fifoclient.c
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "MYFIFO"

int main()
{
	int fd,fd1;
	int end_process;
	int stringlen;
	char readbuf[80];
	char end_str[5];
	int length,wc,lines;
	printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");
	fd = open(FIFO_FILE, O_CREAT|O_WRONLY);
	strcpy(end_str, "end");
	while(1)
	{
		printf("Enter string: ");
		fgets(readbuf, sizeof(readbuf), stdin);
		stringlen = strlen(readbuf);
		readbuf[stringlen - 1] = '\0';
		end_process = strcmp(readbuf, end_str);
		//printf("end_process is %d\n", end_process);
		if (end_process != 0)
		{
			write(fd, readbuf, strlen(readbuf));
			printf("Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
		}
		else
		{
			write(fd, readbuf, strlen(readbuf));
			printf("Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));
			close(fd);
			break;
		}
	}
	fd1=open(FIFO_FILE,O_RDONLY);
	while(1)
	{
		int num;
		char s[300];
		while(num=read(fd1,s,sizeof(s))>0)
		printf("%s\n",s);
	}
	close(fd1);
	return 0;
}
