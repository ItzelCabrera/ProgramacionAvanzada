#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	pid_t proc;
	proc = fork();
	printf("1.-Soy el proceso [%i], y mi papá es [%i]",getpid(),getppid());
	if(proc < 0) printf("\nerror");
	if(proc == 0) printf("\n1)soy el proceso hijo [%i]->mi papa es [%i]--> mi hijo es [%i]",getpid(),getppid(),proc);
	else {
		printf("\n1)soy el proceso papa [%i]->mi papa es [%i]--> mi hijo es [%i]",getpid(),getppid(),proc);
				
	}
	wait(&proc);
	printf("\n*******************************************");
	
	
	pid_t proc2;
	proc2 = fork();
	printf("2.-Soy el proceso [%i], y mi papá es [%i]",getpid(),getppid());
	if(proc2 < 0) printf("\nerror");
	if(proc2 == 0) printf("\n2)soy el proceso hijo [%i]->mi papa es [%i]--> mi hijo es [%i]",getpid(),getppid(),proc2);
	else {
		printf("\n2)soy el proceso papa [%i]->mi papa es [%i]--> mi hijo es [%i]",getpid(),getppid(),proc2);
				
	}
	wait(&proc2);
	printf("\n------------------------------------------");
	
	
	pid_t proc3;
	proc3 = fork();
	printf("3.-Soy el proceso [%i], y mi papá es [%i]",getpid(),getppid());
	if(proc3 < 0) printf("\nerror");
	if(proc3 == 0) printf("\n3)soy el proceso hijo [%i]->mi papa es [%i]--> mi hijo es [%i]",getpid(),getppid(),proc3);
	else {
		printf("\n3)soy el proceso papa [%i]->mi papa es [%i]--> mi hijo es [%i]",getpid(),getppid(),proc3);
				
	}
	wait(&proc3);
	printf("\nTodos los procesos hijos han terminado");
	
	exit(0);
}
