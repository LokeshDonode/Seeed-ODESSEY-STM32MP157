//  opensystem call
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
int n,fd;
char buff[50];

fd = open("lokesh.txt",O_RDONLY); //opens in read only mode and the file descriptor saved in integer fd
printf("The file descriptor is %d\n",fd); //prints the value of file descriptor
n = read(fd,buff,50); //read 10 characters from the file
write(1,buff,n);//writes on screen
printf("\n");
 
return 0;
}
