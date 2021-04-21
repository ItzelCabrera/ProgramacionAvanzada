//Cabrera Vazquez Itzel Berenice 2020640576

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>
#define TAM_BUFFER 10
#define MIN_ESP 1 //minimo de espacios disp que debe tener para seguir consumiendo
#define MAX_ESP 9 //máximo de espacios ocup que debe tener para seguir produciendo

void *Productor(void *arg);
void *Consumidor(void *arg);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//acceso a RC
pthread_cond_t lleno = PTHREAD_COND_INITIALIZER; //var de condicion
pthread_cond_t vacio = PTHREAD_COND_INITIALIZER; //var de condicion

int n_datos = 0; //datos en el buffer
int buffer[TAM_BUFFER] = {};

int main(){ 
    printf("\nPrograma de un consumidor y un productor, con un buffer de tamano %d\n\n",TAM_BUFFER);
    pthread_t prod;
    pthread_t cons;
    
    pthread_create(&prod,NULL,&Productor,NULL);
    pthread_create(&cons,NULL,&Consumidor,NULL);

    pthread_join(prod,NULL);
    pthread_join(cons,NULL);
    return 0;
}

void *Productor(void *arg){
    int dato = 0;
    int i = 0;
    printf("Soy el proceso con pid%ld\n",pthread_self());
    
    for(;;){
        dato+=1; //produce un dato
        printf("Dato producido: %d\n",dato);
        pthread_mutex_lock(&mutex); //accede al buffer
            while(n_datos == TAM_BUFFER){ //buffer lleno
                printf("[n_datos  %d]P:Esperando a que se desocupe un lugar\n",n_datos);
                pthread_cond_wait(&lleno,&mutex);
            }
            buffer[i % TAM_BUFFER]=dato; //pos = i %TAM_BUFFER
            printf("El dato colocado es %i en %d \n",buffer[i % TAM_BUFFER],i % TAM_BUFFER);
            n_datos++;//se ocupó un luga del buffer
            if(n_datos == MIN_ESP){ //si ya existe por lo menos un dato a consumir
                printf("Se ha creado un espacio que puede ser consumido!\n");                
                pthread_cond_signal(&vacio);
            }
        pthread_mutex_unlock(&mutex); //permite que otro acceda al buffer 
        sleep(1);   
        i++; 
    }
}

void *Consumidor(void *arg){
    int dato = 0; //var para recopilar datos consumidos
    int i = 0;
    printf("Soy el proceso con pid%ld\n",pthread_self());
    
    for(;;){
        pthread_mutex_lock(&mutex); //accede al buffer
            while(n_datos == 0){//buffer vacío
                printf("[nE_enArray  %d]C:Esperando datos para consumir\n",n_datos);
                pthread_cond_wait(&vacio,&mutex);
            }
            dato= buffer[i%TAM_BUFFER];//pos = i %TAM_BUFFER
            printf("El dato consumido es %i de %d\n",dato,i % TAM_BUFFER);
            n_datos--;//se desocupó un lugar del buffer
            if(n_datos == MAX_ESP) {//ya hay por lo menos un lugar por ocupar
                printf("Se ha liberado un espacio, se puede seguir produciendo!\n");          
                pthread_cond_signal(&lleno);
            }
        pthread_mutex_unlock(&mutex);   
        sleep(3); 
        i++;    
    }
}

