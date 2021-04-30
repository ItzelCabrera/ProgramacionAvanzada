//Cabrera Vazquez Itzel Berenice 2020640576

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>

sem_t fC;
sem_t fP;
sem_t fT;
sem_t a;

void *Fumadores(void *arg);
void *Agente(void *arg);

int main(){
    pthread_t FC;
    pthread_t FP;
    pthread_t FT;
    pthread_t A;

    sem_init(&fC,0,0);
    sem_init(&fP,0,0);
    sem_init(&fT,0,0);
    sem_init(&a,0,1);;

    pthread_create(&FC,0,&Fumadores,(void*)(intptr_t)1);
    pthread_create(&FP,0,&Fumadores,(void*)(intptr_t)2);
    pthread_create(&FT,0,&Fumadores,(void*)(intptr_t)3);
    pthread_create(&A,0,&Agente,NULL);
    
    pthread_join(FC,NULL);
    pthread_join(FP,NULL);
    pthread_join(FT,NULL);
    pthread_join(A,NULL);

    sem_destroy(&fC);
    sem_destroy(&fP);
    sem_destroy(&fT);
    sem_destroy(&a);

}

void *Fumadores(void *arg){
    int f = (intptr_t)arg;
    
    while(1){
        switch(f){
            case 1:
                sleep(2);
                printf("\tFumador con cerillo espera a que le asignen su turno\n");
                sem_wait(&fC); //espera a que el agente le de permiso
                printf("...FUMADOR CERILLO FUMA...\tPID = %ld\n",pthread_self());
                break;
            case 2:
                printf("\tFumador con papel espera a que le asignen su turno\n");
                sem_wait(&fP);//espera a que el agente le de permiso
                printf("...FUMADOR PAPEL FUMA...\tPID = %ld\n",pthread_self());
                break;
            case 3:
                printf("\tFumador con tabaco espera a que le asignen su turno\n");
                sem_wait(&fT);//espera a que el agente le de permiso
                printf("...FUMADOR TABACO FUMA...\tPID = %ld\n",pthread_self());
                break;
            default:
                printf("Error con el fumador\n");
        }
        sem_post(&a); //permite el paso al agente para que vuelva a generar dos ingredientes
    }
    pthread_exit(NULL);
}

void *Agente(void *arg){  
    int aleat = 0;  
    int c = 0; //validacion para cuando entra por primera vez al agente
    srand(time(0));

    while(1){
        //sleep(4);
        if(c==0)sem_wait(&a);//cuando el agente entra por primera vez, se actualiza su valor a cero, para poder pausar y renaudar al agente
        aleat = rand()%3; 
        //0 --> paso al fumador con cerillo 
        //1 --> paso al fumador con papel 
        //2 --> paso al fumador con tabaco 
    
        switch(aleat){
            case 0:
                printf("¡Ingredientes generados [Papel] y [Tabaco]!\n");
                sem_post(&fC); //permite que fume el fumador con cerillo
                break;
            case 1:
                printf("¡Ingredientes generados [Cerillo] y [Tabaco]!\n");
                sem_post(&fP);//permite que fume el fumador con papel
                break;
            case 2:
                printf("¡Ingredientes generados [Cerillo] y [Papel]!\n");
                sem_post(&fT);//permite que fume el fumador con tabaco
                break;
            default:
                printf("Error al generar ingredientes\n");
                break;
        }
        printf("\tAgente detiene la produccion de recursos\n");
        sem_wait(&a);
        c=1; //el agente ya entró por primera vez
    }
    pthread_exit(NULL);
}
