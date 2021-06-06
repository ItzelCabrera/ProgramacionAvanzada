//Programa que simula una pila mediante semaforos
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>
#define NE 20

sem_t s0;
sem_t s1;
sem_t s2;
sem_t s3;
int a[NE];
int j = 0;

void f(){
    sem_post(&s0);
    sem_post(&s1);
    sem_post(&s2);
    sem_post(&s3);
}

void *Funcion0(void *arg){
    printf("Proceso #1\n");
    while(j<NE){
        if(j==0)sem_wait(&s0);
        if((j%4) != 0) {
            printf("Proceso 1: a mimir\n");
            sem_wait(&s0);
        }
        if(j>=NE)break;
        printf("Colocando dato-->1\n");
        a[j] = 1;
        printf("a[%d] = %d\n",j,a[j]);
        j++;
        sem_post(&s1);
    }
    f();
}

void *Funcion1(void *arg){
    printf("Proceso #2\n");
    while(j<NE){
        if((j%4) != 1) {
            printf("Proceso 2: a mimir\n");
            sem_wait(&s1);
        }
        if(j>=NE)break;
        printf("Colocando dato-->2\n");
        a[j] = 2;
        printf("a[%d] = %d\n",j,a[j]);
        j++;
        sem_post(&s2);
    }
    f();
}

void *Funcion2(void *arg){
    printf("Proceso #3\n");
    while(j<NE){
        if((j%4) != 2) {
            printf("Proceso 3: a mimir\n");
            sem_wait(&s2);
        }
        if(j>=NE)break;
        printf("Colocando dato-->3\n");
        a[j] = 3;
        printf("a[%d] = %d\n",j,a[j]);
        j++;
        sem_post(&s3);
    }
    f();
}

void *Funcion3(void *arg){
   printf("Proceso #4\n");
    while(j<NE){
        if((j%4) != 3) {
            printf("Proceso 4: a mimir\n");
            sem_wait(&s3);
        }
        if(j>=NE)break;
        printf("Colocando dato-->4\n");
        a[j] = 4;
        printf("a[%d] = %d\n",j,a[j]);
        j++;
        sem_post(&s0);
    }
    f();
}

int main(){
    pthread_t proc0;
    pthread_t proc1;
    pthread_t proc2;
    pthread_t proc3;

    sem_init(&s0,0,1);
    sem_init(&s1,0,0);
    sem_init(&s2,0,0);
    sem_init(&s3,0,0);

    pthread_create(&proc0,0,&Funcion0,NULL);
    pthread_create(&proc1,0,&Funcion1,NULL);
    pthread_create(&proc2,0,&Funcion2,NULL);
    pthread_create(&proc3,0,&Funcion3,NULL);

    pthread_join(proc0,NULL);
    pthread_join(proc1,NULL);
    pthread_join(proc2,NULL);
    pthread_join(proc3,NULL);   

    sem_destroy(&s0);
    sem_destroy(&s1);
    sem_destroy(&s2);
    sem_destroy(&s3);
    
    for(int k = 0; k<NE;k++){
        printf("[%d]:%d\n",k,a[k]);   
    }
    
    return 0;
}
