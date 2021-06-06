#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	/*
	PROGRAMA QUE USA UN FOR PARA CREAR TRES ROCESOS HIJOS
	*/
	pid_t proc[3];
	for(int i = 0; i<3; i++){
		proc[i] = fork();
		printf("[%i]Soy el proceso [%i], y mi papá es [%i]",i,getpid(),getppid());
		if(proc[i]< 0) printf("\nerror");
		if(proc[i] == 0) printf("\n(%i)soy el proceso hijo [%i]->mi papa es [%i]--> mi hijo es [%i]",i,getpid(),getppid(),proc[i]);
		else {
			printf("\n(%i)soy el proceso papa [%i]->mi papa es [%i]--> mi hijo es [%i]",i,getpid(),getppid(),proc[i]);
					
		}
		wait(&proc[i]);
		printf("\n{%i}Todos los procesos hijos han terminado",i);
	}
	
	exit(0);
}
