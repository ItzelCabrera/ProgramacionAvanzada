#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	FILE *fO, *fI;

	pid_t proc;
	
	//FOR 2: crea mi arbol de un solo nivel
	for(int i = 0; i<3;i++){
		proc = fork();
		if(proc <0){
			printf("Ocurrio un error");
		}
		if (proc == 0){
			printf("\nSoy el proceso[%i], mi papa es [%i]\n",getpid(),getppid());
			exit(0);
		}
		else{
			wait(&proc);
		}
	}
	
	return 0;
}

/*FOR I
	for(int i = 0; i<3;i++){
		proc = fork();
		if(proc <0){
			printf("Ocurrio un error");
		}
		if (proc == 0){
			printf("\nSoy el proceso[%i], mi papa es [%i]\n",getpid(),getppid());
		}
		else{
			wait(&proc);
			printf("\nSoy el proceso PAPA [%i], mi papa es [%i]\n",getpid(),getppid());
			
		}
	}*/
	
/*FOR 3: crea una lista de procesos 
	for(int i = 0; i<3;i++){
		proc = fork();
		if(proc <0){
			printf("Ocurrio un error");
		}
		if (proc == 0){
			printf("\nSoy el proceso[%i], mi papa es [%i]\n",getpid(),getppid());
		}
		else{
			wait(&proc);
			break;
			
		}
	}*/
