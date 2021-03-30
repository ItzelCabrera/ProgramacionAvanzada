#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	pid_t proc;
	proc = fork();
	printf("Soy el proceso [%i], y mi papá es [%i]",getpid(),getppid());
	if(proc < 0) printf("\nerror");
	if(proc == 0) printf("\nsoy el proceso hijo [%i]->mi papa es [%i]--> mi hijo es [%i]",getpid(),getppid(),proc);
	else {
		printf("\nsoy el proceso papa [%i]->mi papa es [%i]--> mi hijo es [%i]",getpid(),getppid(),proc);
				
	}
	wait(&proc);
	exit(0);
}
