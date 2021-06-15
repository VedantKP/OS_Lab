//Filename: fifoserver.c
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
	char readbuf[80];
	char end[10];
	int to_end;
	int read_bytes;
	int length,wc=1,lines;
	int state=0,state1=0;
	FILE * fp;
	//Create the FIFO if it does not exist
	mknod(FIFO_FILE, S_IFIFO|0640, 0);
	strcpy(end, "end");
	while(1)
	{
		fd = open(FIFO_FILE, O_RDONLY);
		read_bytes = read(fd, readbuf, sizeof(readbuf));
		readbuf[read_bytes] = '\0';
		printf("Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
		to_end = strcmp(readbuf, end);
		if(*readbuf==' '||*readbuf=='\n'||*readbuf=='\t')
		{
			state=1;
		}
		else
		{
			state=0;
			wc++;
		}
		if(*readbuf=='\n')
		{
			state1=1;
		}
		else
		{
			state=0;
			lines++;
		}
		length=length+strlen(readbuf);
		if (to_end == 0)
		{
			close(fd);
			break;
		}
	}
	fp=fopen("b12.txt","w");
	fprintf(fp,"\nThe length of string is %d\n",length);
	fprintf(fp,"The number of words are %d\n",wc);
	fclose(fp);
	fp=fopen("b12.txt","r");
	if(fp==NULL);
	printf("close");
   
	fd1=open(FIFO_FILE,O_WRONLY);
	char line[300];
	while(fgets(line,sizeof(line),fp))
	write(fd1,line,strlen(line));
	close(fd1);
	return 0;
}
