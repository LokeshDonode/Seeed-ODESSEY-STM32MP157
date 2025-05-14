#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
pid_t p;
printf("before fork\n");
p = fork();

if(p==0){
	printf("This is Child Process id %d\n",getpid());
	printf("The Parent id is %d\n",getpid());
}
else{
	printf("Child id is %d\n",p);
	printf("Parent id is %d\n",getpid());
}
return 0;
}
	
