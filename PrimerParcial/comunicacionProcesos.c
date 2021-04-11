#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void sobreescribir(FILE *fI,int v, char f[]);
void anexar(FILE *fI,int v, char f[]);
void leer(FILE *fO);

int main(){
	FILE *fP,*fI;
	pid_t proc;
	
	for(int i = 1; i<=4;i++){
		proc = fork();
		if(proc <0){
			printf("Ocurrio un error");
		}
		else if (proc == 0){
			printf("\nSoy el proceso[%i], mi papa es [%i] y me voy a registrar\n",getpid(),getppid());
			if(i%2==0){
				anexar(fP,getpid(),"filePares.txt");
			}else{
				anexar(fI,getpid(),"fileImpares.txt");
			}
			break;
		}
		else{
			//printf("\n<<%d>>\n",getpid());
			wait(&proc);
		}
	}
	
	return 0;
}


void sobreescribir(FILE *fI,int v,char file[]){
	fI = fopen(file,"w+");
	if(fI == NULL){
		printf("ERROR AL ABRIR ARCHIVOS");
		exit(1);
	}
	fprintf(fI,"%d\n",v);
	fclose(fI);
}
void anexar(FILE *fI,int v,char file[]){
	fI = fopen(file,"a");
	if(fI == NULL){
		printf("ERROR AL ABRIR ARCHIVOS");
		exit(1);
	}
	fprintf(fI,"%d\n",v);
	fclose(fI);
}

void leer(FILE *fO){
	fO = fopen("file.txt","r");
	if(fO == NULL){
		printf("Error al intentar abrir los archivos");
		exit(1);
	}
	char c = ' ';
	while(feof(fO) == 0){
		c = fgetc(fO);
		printf("%c",c);
	}
}

