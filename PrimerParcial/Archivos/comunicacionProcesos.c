//Programa para comunicar procesos mediante archivs txt
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/wait.h>

void sobreescribir(FILE *fI,char v[]);
void anexar(FILE *fI,char v[]);
void leer(FILE *fO);
int SIZE  = 4;

int main(){

	FILE *fP,*fI;
	fP = fopen("3-4.txt","a+");
	fI = fopen("1-2.txt","a+");
	FILE *control = fopen("control.txt","w+");
	if((control == NULL) || (fP == NULL) || (fI == NULL)){printf("\nError al intentar abrir archivo");}
	fprintf(control,"%i %i",0,0);
	rewind(control);
	
	pid_t proc;
	int i = 0;
	int c[SIZE/2];

	printf("\nCREACION DE PROCESOS\n");
	for(i = 1; i<=SIZE;i++){
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
	
	int z = 0;
	while(1){
		fscanf(control,"%i %i",&c[0],&c[1]);
		rewind(control);
		printf("c1: %i c2: %i",c[0],c[1]);
		if (proc == 0){
			if(i == 1){
				printf("\nProceso 1, pid: %i\n",getpid());
				if(c[0] == 0){
					printf("\nP1 escribe por primera vez a P2\n");
					z = fprintf(control,"%i %i",1,c[1]);
					rewind(control);
					//printf("\n%i\n",z);
					sobreescribir(fI,"P1->P2: escribe por primera vez");
					break;
				}
				else if(c[0] == 1){
					printf("\nP1 espera a que P2 lea y responda\n");
					break;
					
				}
				else{
					printf("\nP1 lee mensaje de P2 y responde\n");
					z = fprintf(control,"%i %i",1,c[1]);
					rewind(control);
					//printf("\n%i\n",z);
					sobreescribir(fI,"P1->P2: responde");
					break;
				}	
			}
			else if(i == 2){
				printf("\nProceso 2, pid: %i\n",getpid());
				if(c[0] == 0){
					printf("\nP2 escribe por primera vez a P1\n");
					z = fprintf(control,"%i %i",2,c[1]);
					rewind(control);
					//printf("\n%i\n",z);
					sobreescribir(fI,"P2->P1: escribe por primera vez");
					break;
				}
				else if(c[0] == 2){
					printf("\nP2 espera a que P1 lea y responda\n");
					break;
				}
				else{
					printf("\nP2 lee mensaje de P1 y responde\n");
					z = fprintf(control,"%i %i",2,c[1]);
					rewind(control);
					//printf("\n%i\n",z);
					sobreescribir(fI,"P2->P1: responde");
					break;
				}		
			}
			else if(i == 3){
				printf("\nProceso 3, pid: %i\n",getpid());
				if(c[1] == 0){
					printf("\nP3 escribe por primera vez a P4\n");
					z = fprintf(control,"%i %i",c[0],3);
					rewind(control);
					//printf("\n%i\n",z);
					sobreescribir(fP,"P3->P4: escribe por primera vez");
					break;
				}
				else if(c[1] == 3){
					printf("\nP3 espera a que P4 lea y responda\n");
					break;
				}
				else{
					printf("\nP3 lee mensaje de P4 y responde\n");
					z = fprintf(control,"%i %i",c[0],3);
					rewind(control);
					//printf("\n%i\n",z);
					sobreescribir(fP,"P3->P4: responde");
					break;
				}		
			}
			else{
				printf("\nProceso 4, pid: %i\n",getpid());	
				if(c[1] == 0){
					printf("\nP4 escribe por primera vez a P3\n");
					z = fprintf(control,"%i %i",c[0],4);
					rewind(control);
					//printf("\n%i\n",z);
					sobreescribir(fP,"P4->P3: escribe por primera vez");
					break;
				}
				else if(c[1] == 4){
					printf("\nP4 espera a que P3 lea y responda\n");
					break;
				}
				else{
					printf("\nP4 lee mensaje de P3 y responde\n");
					z = fprintf(control,"%i %i",c[0],4);
					rewind(control);
					//printf("\n%i\n",z);
					sobreescribir(fP,"P4->P3: responde");
					break;
				}	
			}
		}
		sleep(3);
	}
		
	fclose(fI);
	fclose(fP);
	fclose(control);
	return 0;
}


void sobreescribir(FILE *fI,char v[]){
	fprintf(fI,"%s\n",v);
}
void anexar(FILE *fI,char v[]){
	fprintf(fI,"%s",v);
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

