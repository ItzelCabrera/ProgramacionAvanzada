#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int varg = 14;
int main(){
	pid_t proc;
	
	printf("\n***************Proceso [%i] comienza ************\n",getpid());
	
	proc = fork();
	
	if(proc == -1){
		printf("ERROR");
	}else if(proc == 0){
		//printf("\nProceso [%i] ejecutandose, soy hijo de [%d]\n", getpid(),getppid());
		varg = 15;
	}else{
		//printf("\nProceso PAPA [%i] ejecutandose, BASH es [%d]\n", getpid(),getppid());
		varg = 45;
	}
	
	
	//printf("\nProceso [%i] ejecutandose\n", getpid());
	//wait(&proc);
	
	while(1){
		sleep(2);
		printf("\nProceso [%i], var [%d]\n", getpid(),varg);
	}
	
	return 0;
}
