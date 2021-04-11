#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/wait.h>

void sobreescribir(FILE *fI,char v[], char f[]);
void anexar(FILE *fI,char v[], char f[]);
void leer(FILE *fO);

int main(){
	FILE *fP,*fI;
	pid_t proc;
	int i = 0;
	int w[2] = {0,0};
	
	printf("\nCREACION DE PROCESOS\n");
	for(i = 1; i<=4;i++){
		proc = fork();
		if(proc <0){
			printf("Ocurrio un error");
		}
		else if (proc == 0){
			printf("\nREGISTRO #{%i}: Soy el proceso[%i], mi papa es [%i]\n",i,getpid(),getppid());
			break;
		}
		else{
			printf("\n---\n");
		}
	}
	
	
	while(1){
		if(proc == 0){
			if(i == 1){
				if(w[0] == 0){//le toca primero escribir 
					anexar(fI,"[1]\t{3}\tPrimer mensaje\n","fileImpares.txt");
					printf("\n[1] le escribe por primera vez a {3}\n");
					w[0] = 1;//escribió 1
					break;
				}else if(w[0] == 1){//la ultima vez escribió "1", pero "3" no ha leido --> espera
					break;
				}else{//w[0] = 3 --> le toca leer
					printf("\n{1} lee lo que le escribió [3] y le responde\n");
					anexar(fI,"[1]\t{3}\tLee y responde ...\n","fileImpares.txt");
					w[0] = 1;
				}	
				
			}	
			else if(i == 3){
				if(w[0] == 0){//le toca primero escribir 
					anexar(fI,"[3]\t{1}\tPrimer mensaje\n","fileImpares.txt");
					printf("\n[3] le escribe por primera vez a {1}\n");
					w[0] = 3;//escribió 3
					break;
				}else if(w[0] == 3){//la ultima vez escribió "3", pero "1" no ha leido --> espera
					break;
				}else{//w[0] = 1 --> le toca leer
					printf("\n{3} lee lo que le escribió [1] y le responde\n");
					anexar(fI,"[3]\t{1}\tLee y responde ...\n","fileImpares.txt");
					w[0] = 3;
				}
			}
			else if(i == 2){
				if(w[1] == 0){//le toca primero escribir 
					anexar(fI,"[2]\t{4}\tPrimer mensaje\n","filePares.txt");
					printf("\n[2] le escribe por primera vez a {4}\n");
					w[1] = 2;//escribió 2
					break;
				}else if(w[1] == 2){//la ultima vez escribió "2", pero "4" no ha leido --> espera
					break;
				}else{//w[1] = 4 --> le toca leer
					printf("\n{2} lee lo que le escribió [4] y le responde\n");
					anexar(fI,"[2]\t{4}\tLee y responde ...\n","filePares.txt");
					w[1] = 2;
				}
			}
			else if(i == 4){
				if(w[1] == 0){//le toca primero escribir 
					anexar(fI,"[4]\t{2}\tPrimer mensaje\n","filePares.txt");
					printf("\n[4] le escribe por primera vez a {2}\n");
					w[1] = 4;//escribió 4
					break;
				}else if(w[1] == 4){//la ultima vez escribió "2", pero "4" no ha leido --> espera
					break;
				}else{//w[1] = 2 --> le toca leer
					printf("\n{4} lee lo que le escribió [2] y le responde\n");
					anexar(fI,"[4]\t{2}\tLee y responde ...\n","filePares.txt");
					w[1] = 4;
				}	
			}
		}
		sleep(3);
	}
	
	return 0;
}


void sobreescribir(FILE *fI,char v[],char file[]){
	fI = fopen(file,"w+");
	if(fI == NULL){
		printf("ERROR AL ABRIR ARCHIVOS");
		exit(1);
	}
	fprintf(fI,"%s\n",v);
	fclose(fI);
}
void anexar(FILE *fI,char v[],char file[]){
	fI = fopen(file,"a");
	if(fI == NULL){
		printf("ERROR AL ABRIR ARCHIVOS");
		exit(1);
	}
	fprintf(fI,"%s",v);
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

