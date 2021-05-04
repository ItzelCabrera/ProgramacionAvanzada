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
sem_t s;
int c  = 0;

void *F3(void *arg){
    printf("F3 en sem\n");
    sem_wait(&fC);
    printf("Desperto 3\n");
}

void *F2(void *arg){
    printf("F2 en sem\n");
    sem_wait(&fC);
    printf("Desperto 2\n");
}

void *F4(void *arg){ 
    //printf("F4 en sem\n");
    //sem_wait(&fC);
    //printf("Desperto 4\n");
    int value = 0;
    sem_getvalue(&fC,&value);
    printf("Valor = %d\n",value);
    sem_post_np(fC,3);
    sem_getvalue(&fC,&value);
    printf("Valor = %d\n",value);
}

int main(){
    sem_init(&fC,0,1);    
    sem_init(&s,0,0);

    pthread_t FC;
    pthread_t FP;
    pthread_t FT;    
    pthread_t A;
    
    sem_wait(&fC);

    pthread_create(&FC,0,&F4,NULL);
    pthread_create(&FP,0,&F2,NULL);
    pthread_create(&FT,0,&F3,NULL);

    pthread_join(FC,NULL);
    pthread_join(FP,NULL);
    pthread_join(FT,NULL);
    pthread_join(A,NULL);

    sem_destroy(&fC);
    sem_destroy(&s);

}
