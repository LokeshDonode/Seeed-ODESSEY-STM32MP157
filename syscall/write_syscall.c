#include<stdio.h>
#include<unistd.h>

int main()
{
int count;
count = write(1,"hello\n",6); // 1 is a file descriptor ,"hello\n" is the data,6 
		      // is the count of characters of data
printf("Total bytes written: %d\n",count);
}
