//Cabrera Vazquez Itzel Berenice 2020640576
//Programa de 4 consumidores y 3 productores, mediante el uso de mutex y variables de condicion
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>
#define TAM_BUFFER 10

void *Productor(void *arg);
void *Consumidor(void *arg);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//acceso a RC
pthread_cond_t lleno = PTHREAD_COND_INITIALIZER; //var de condicion
pthread_cond_t vacio = PTHREAD_COND_INITIALIZER; //var de condicion

int n_datos = 0; //datos en el buffer
int buffer[TAM_BUFFER] = {};
int iP = 0;
int iC = 0;
bool vC = true;
bool vP = true;

int main(){ 
    printf("\nPrograma de un 4 consumidores y 3 productores, con un buffer de tamano %d\n\n",TAM_BUFFER);
    pthread_t prod[3];
    pthread_t cons[4];
    
    if(pthread_create(&prod[0],NULL,&Productor,(void*)(intptr_t)0)){
        printf("Problema en la creacion del hilo\n");
        exit(EXIT_FAILURE);    
    }
    if(pthread_create(&prod[1],NULL,&Productor,(void*)(intptr_t)1)){
        printf("Problema en la creacion del hilo\n");
        exit(EXIT_FAILURE);    
    }
    if(pthread_create(&prod[2],NULL,&Productor,(void*)(intptr_t)2)){
        printf("Problema en la creacion del hilo\n");
        exit(EXIT_FAILURE);    
    }
    
    if(pthread_create(&cons[0],NULL,&Consumidor,(void*)(intptr_t)0)){
        printf("Problema en la creacion del hilo\n");
        exit(EXIT_FAILURE); 
    }
    if(pthread_create(&cons[1],NULL,&Consumidor,(void*)(intptr_t)1)){
        printf("Problema en la creacion del hilo\n");
        exit(EXIT_FAILURE); 
    }
    if(pthread_create(&cons[2],NULL,&Consumidor,(void*)(intptr_t)2)){
        printf("Problema en la creacion del hilo\n");
        exit(EXIT_FAILURE); 
    }
    if(pthread_create(&cons[3],NULL,&Consumidor,(void*)(intptr_t)3)){
        printf("Problema en la creacion del hilo\n");
        exit(EXIT_FAILURE); 
    }

    if(pthread_join(prod[0],NULL)){
        printf("P0 Problema al esperar a hijo\n");
        exit(EXIT_FAILURE);    
    }else printf("Prod 1 Termina \n");
    if(pthread_join(prod[1],NULL)){
        printf("P1 Problema al esperar a hijo\n");
        exit(EXIT_FAILURE);    
    }else printf("Prod 2 Termina\n");
    if(pthread_join(prod[2],NULL)){
        printf("P2 Problema al esperar a hijo\n");
        exit(EXIT_FAILURE);    
    }else printf("Prod 3 Termina\n");
    if(pthread_join(cons[0],NULL)){
        printf("C0 Problema al esperar a hijo\n");
        exit(EXIT_FAILURE);    
    }else printf("Cons 1 Termina\n");
    if(pthread_join(cons[1],NULL)){
        printf("C1 Problema al esperar a hijo\n");
        exit(EXIT_FAILURE);    
    }else printf("Cons 2 Termina\n");
    if(pthread_join(cons[2],NULL)){
        printf("C2 Problema al esperar a hijo\n");
        exit(EXIT_FAILURE);    
    }else printf("Cons 3 Termina\n");
    if(pthread_join(cons[3],NULL)){
        printf("C3 Problema al esperar a hijo\n");
        exit(EXIT_FAILURE);    
    }else printf("Cons 4 Termina\n");

    pthread_mutex_destroy(&mutex); /* Destruir */
    pthread_cond_destroy(&lleno);
    pthread_cond_destroy(&vacio);

    return 0;
}

void *Productor(void *arg){
    int dato = 0;
    printf("Prod {%ld}\tSoy el proceso con pid%ld\n",(intptr_t)arg,pthread_self());

    while(vP){
        //printf("\t\tENTRA P%ld\n",(intptr_t)arg);
        pthread_mutex_lock(&mutex); //accede al buffer
            if(iP<15){
                while(n_datos == TAM_BUFFER){ //buffer lleno
                    printf("Esperando a que se desocupe un lugar\n");
                    pthread_cond_wait(&lleno,&mutex);
                    if(iP == 15) {
                        break;                    
                    }
                }
                if(iP < 15){
                    buffer[iP % TAM_BUFFER]=iP; //posProductor = i %TAM_BUFFER
                    printf("Dato colocado =  %i, pos[%d]; producido por Productor:%ld\n",buffer[iP % TAM_BUFFER],iP % TAM_BUFFER,(intptr_t)arg);
                    n_datos++;//se ocupó un luga del buffer
                    if(n_datos == 1){ //si ya existe por lo menos un dato a consumir
                        printf("Se ha creado un espacio que puede ser consumido!\n");                
                        pthread_cond_signal(&vacio);
                    }
                    iP++; 
                    //printf("IP=%d\n",iP);
                }
            }if(iP == 15){
                pthread_cond_broadcast(&lleno);//libera los posibles productores interrumpidos por no haber más espacios disponibles
                vP = false;
            }
        pthread_mutex_unlock(&mutex); //permite que otro acceda al buffer 
        sleep(1);
    }
    //printf("\tSale P%ld\n",(intptr_t)arg); 
    pthread_exit(NULL); 
}

void *Consumidor(void *arg){
    int dato = 0; //var para recopilar datos consumidos
    printf("Cons {%ld}\tSoy el proceso con pid%ld\n",(intptr_t)arg,pthread_self());

    while(vC){
        //printf("\t\tENTRA C%ld\n",(intptr_t)arg);
        pthread_mutex_lock(&mutex); //accede al buffer
            if(iC<15){
                while(n_datos == 0){//buffer vacío
                    printf("Esperando datos para consumir\n");
                    pthread_cond_wait(&vacio,&mutex);
                    if(iC == 15) {
                        break;                    
                    }
                }
                if(iC<15){
                    dato= buffer[iC%TAM_BUFFER];//pos = i %TAM_BUFFER
                    printf("Dato consumido = %i , pos [%d], consumido por Consumidor: %ld\n",dato,iC % TAM_BUFFER,(intptr_t)arg);
                    n_datos--;//se desocupó un lugar del buffer
                    if(n_datos == ((TAM_BUFFER)-1)) {//ya hay por lo menos un lugar por ocupar
                        printf("Se ha liberado un espacio, se puede seguir produciendo!\n");          
                        pthread_cond_signal(&lleno);
                    }            
                    iC++;
                    //printf("IC=%d\n",iC);
                }
            }
            if(iC == 15){
                pthread_cond_broadcast(&vacio);//libera los posibles consumidores interrupidos por no haber datos por consumir
                vC = false;
            }
        pthread_mutex_unlock(&mutex); 
        sleep(1);    
    }
    //printf("\tSale C%ld\n",(intptr_t)arg);
    pthread_exit(NULL); 
}

