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
#define I1 'Cerillo'
#define I2 'Papel'
#define I3 'Tabaco'

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
    sem_init(&A,0,1);

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

/*void *FumadorCerillo(void *arg){
    pthread_exit(NULL);
}

void *FumadorPapel(void *arg){
    pthread_exit(NULL);
}

void *FumadorTabaco(void *arg){
    pthread_exit(NULL);
}*/

void *Fumadores(void *arg){
    int f = (intptr_t)arg;
    printf("Entra fumador%d\tPID = %ld\n",f,pthread_self());

    while(1){
        switch(f){
            case 1:
                printf("\tFC a mimir\n");
                sem_wait(&fC);   
                printf("...FUMADOR CERILLO FUMA...\n");
                break;
            case 2:
                printf("\tFP a mimir\n");
                sem_wait(&fP);
                printf("...FUMADOR PAPEL FUMA...\n");
                break;
            case 3:
                printf("\tFT a mimir\n");
                sem_wait(&fT);
                printf("...FUMADOR TABACO FUMA...\n");
                break;
            default:
                printf("Error con el fumador\n");
        }
        sem_post(&a);
    }
    pthread_exit(NULL);
}

void *Agente(void *arg){  
    int aleat = 0;  
    printf("Entra agente\tPID = %ld\n",pthread_self());
    while(1){
        sem_wait(&a);
        //genera un numero aleatorio entre 1 y 3
        aleat = rand()%3;        
        switch(aleat){
            case 1:
                printf("¡Ingredientes generados [%s] y [%s]!\n",I2,I3);
                sem_wait(&a);
                printf("\tA a mimir\n");
                sem_post(&fC);
                break;
            case 2:
                printf("¡Ingredientes generados [%s] y [%s]!\n",I1,I3);
                sem_wait(&a);
                printf("\tA a mimir\n");
                sem_post(&fP);
                break;
            case 3:
                printf("¡Ingredientes generados [%s] y [%s]!\n",I1,I2);
                sem_wait(&a);
                printf("\tA a mimir\n");
                sem_post(&fT);
                break;
            default:
                printf("Error al generar ingredientes\n");
        }
    }
    pthread_exit(NULL);
}
