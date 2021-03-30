#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	pid_t proc;
	//FOR I
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
	}
	/*FOR 2
	for(int i = 0; i<3;i++){
		proc = fork();
		if(proc <0){
			printf("Ocurrio un error");
		}
		if (proc == 0){
			printf("\nSoy el proceso[%i], mi papa es [%i]\n",getpid(),getppid());
			break;
		}
		else{
			wait(&proc);
		}
	}
	*/
	/*FOR 3
	for(int i = 0; i<3;i++){
		proc = fork();
		if(proc <0){
			printf("Ocurrio un error");
		}
		if (proc == 0){
			printf("\nSoy el proceso[%i], mi papa es [%i]\n",getpid(),getppid());
		}
		else{
			break;
			wait(&proc);
			}
	}*/
	return 0;
}
