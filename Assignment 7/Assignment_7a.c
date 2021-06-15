#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main() 
{
   int pipefds1[2], pipefds2[2];
   int returnstatus1, returnstatus2;
   int pid;
   char filename[20],fileinfo[100];
   char readinfo[100];
   FILE *fp;
   int i=0;
   char ch;
   returnstatus1 = pipe(pipefds1);
   
   if (returnstatus1 == -1) 
   {
      printf("Unable to create pipe 1 \n");
      return 1;
   }
   returnstatus2 = pipe(pipefds2);
   
   if (returnstatus2 == -1) 
   {
      printf("Unable to create pipe 2 \n");
      return 1;
   }

   pid = fork();
   
   if (pid != 0) // Parent process 
   {
      close(pipefds1[0]); // Close the unwanted pipe1 read side
      close(pipefds2[1]); // Close the unwanted pipe2 write side
      printf("In parent:\nEnter file name to write:");
      gets(filename);
      printf("In Parent: Writing to pipe 1 – filename is %s\n", filename);
      write(pipefds1[1], filename, sizeof(filename));
      read(pipefds2[0], readinfo, sizeof(readinfo));
      printf("In Parent: Reading from pipe 2 – file info is %s\n", readinfo);
   } 
   else //child process 
   {
      sleep(1);
      close(pipefds1[1]); // Close the unwanted pipe1 write side
      close(pipefds2[0]); // Close the unwanted pipe2 read side
      read(pipefds1[0], readinfo, sizeof(readinfo));
      printf("In Child: Reading from pipe 1 – filename is %s\n", readinfo);
      fp=fopen(readinfo ,"r");
      while((ch=fgetc(fp))!=EOF)
      {
      	fileinfo[i]=ch;
      	i++;	
      }
      printf("In Child: Writing to pipe 2 – file info  is %s\n", fileinfo);
      write(pipefds2[1], fileinfo, sizeof(fileinfo));
   }
   return 0;
   }
