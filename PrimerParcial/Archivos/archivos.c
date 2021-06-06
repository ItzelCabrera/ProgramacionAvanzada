#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>
#include<sys/types.h>
#include<sys/wait.h>

void escribir(FILE *fI,char v[]){
	fI = fopen("file.txt","a");
	if(fI == NULL){
		printf("ERROR AL ABRIR ARCHIVOS");
		exit(1);
	}
	fprintf(fI,"%s\n",v);
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


int main(){
	FILE * fI, *fO;
	escribir(fI,"hola");
	leer(fO);
	return 0;
}

