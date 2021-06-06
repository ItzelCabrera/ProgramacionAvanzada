//Programa que simula un lector y un escritor mediante señales
//El escritor y el lector son hilos, se comuncian mediante archivos de texto
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/wait.h>
#define _OPEN_THREADS
#include <pthread.h>
#include <signal.h>

sem_t sE;
sem_t sL;
FILE * fI, *fO;
long int pid[2];//pid[0]-->lector pid[1]-->escritor

void escribir(FILE *fI,char v[]){
	fI = fopen("file.txt","w");
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

void signal_handler(){
    //printf("signal_handler\tLeyendo\n");
    printf("\tMensaje recibido por %ld:",pid[0]);leer(fO);
    sem_post(&sE);
}

void *pLector(void *arg){
    //printf("Llego el lector %ld\n",pid[0]);//==printf("Llego el lector %ld\n",pthread_self());
    while(1){
        printf("Lector [%ld]va a mimir en lo que el escritor termina\n",pid[0]);
        sem_wait(&sL);//en lo que el escritor termina 
    } 
    
}

void *pEscritor(void *arg){
    //printf("Llego el escritor %ld\n",pid[1]);//==printf("Llego el escrtor %ld\n",pthread_self());
    char mssg[50]= "Mensaje para el lector <3\n";
    while(1){
        sleep(2);
        //El escritor escribe en el archivo, despierta al lector y le manda la señal para que pueda leer
        escribir(fI,mssg);
        sem_post(&sL);//despierta al lector
        pthread_kill(pid[0],SIGUSR1);//manda la señal al lector, para que pueda leer 
        printf("Escritor [%ld] va a mimir en lo que el lector termina\n",pid[1]);
        sem_wait(&sE);
    }
}

int main(){
    sem_init(&sE,0,0);
    sem_init(&sL,0,0);

    pthread_t tLector;
    pthread_t tEscritor;
    
    pthread_create(&tLector,0,&pLector,NULL);
    pthread_create(&tEscritor,0,&pEscritor,NULL);  
    
    //Almacena los pid
    pid[0] = tLector;
    pid[1] = tEscritor;
    
    //Prepara a los hilos para recibir la señal
    signal(SIGUSR1,signal_handler);
    
    pthread_join(tLector,NULL);
    pthread_join(tEscritor,NULL);

    sem_destroy(&sE);
    sem_destroy(&sL);
    
    return 0;
}
