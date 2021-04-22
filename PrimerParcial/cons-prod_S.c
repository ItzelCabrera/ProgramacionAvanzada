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
#define TAM_BUFFER 10
#define DATOS_A_PRODUCIR 20

void *Productor(void *arg);
void *Consumidor(void *arg);

sem_t elementosC; //semaforo para elementos consumidos
sem_t huecos;     //semaforo para espacios donde se puede producir
int buffer[TAM_BUFFER];

int main(){ 
    printf("\nPrograma de un consumidor y un productor, con un buffer de tamano %d\n\n",TAM_BUFFER);
    pthread_t prod;
    pthread_t cons;
    
    sem_init(&elementosC,0,0);
    sem_init(&huecos,0,TAM_BUFFER);
    
    pthread_create(&prod,NULL,&Productor,NULL);
    pthread_create(&cons,NULL,&Consumidor,NULL);

    pthread_join(prod,NULL);
    pthread_join(cons,NULL);
    sem_destroy(&huecos);
    sem_destroy(&elementosC);    
    
    return 0;
}

void *Productor(void *arg){
    int dato = 0;
    int i = 0;
    printf("Soy el proceso con pid%ld\n",pthread_self());
    
    for(i = 0;i<DATOS_A_PRODUCIR;i++){
        //dato+=1; //produce un dato
        //printf("Dato producido: %d\n",dato);
        sem_wait(&huecos);        
        buffer[i%TAM_BUFFER] = i;
        printf("Dato colocado %d\n",buffer[i%TAM_BUFFER]);
        sem_post(&elementosC);
        //sleep(2);
    }
    pthread_exit(NULL);
}

void *Consumidor(void *arg){
    int dato = 0; //var para recopilar datos consumidos
    int i = 0;
    printf("Soy el proceso con pid%ld\n",pthread_self());
    
    for(i = 0;i<DATOS_A_PRODUCIR;i++){
        sem_wait(&elementosC);
        dato = buffer[i%TAM_BUFFER];
        printf("Dato consumido %d\n",dato);
        sem_post(&huecos);  
        //sleep(2);   
    }
    pthread_exit(NULL);
}

