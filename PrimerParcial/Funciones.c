#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *funcion_suma(void *args);
void *funcion_resta(void *args);
void *funcion_multi(void *args);
void *funcion_div(void *args);

int resultado = 3;

int main (){
    pthread_t id_hilo1;
    pthread_t id_hilo2;
    pthread_t id_hilo3;
    pthread_t id_hilo4;

    void *valor_retorno;

    if(pthread_create(&id_hilo1, NULL, funcion_suma, NULL)){
        printf("Problema en la creacion del hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&id_hilo2, NULL, funcion_resta, (void*)resultado)){
        printf("Problema en la creacion del hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&id_hilo3, NULL, funcion_multi, (void*)resultado)){
        printf("Problema en la creacion del hilo\n");
        exit(EXIT_FAILURE);
    }
    if(pthread_create(&id_hilo4, NULL, funcion_div, (void*)resultado)){
        printf("Problema en la creacion del hilo\n");
        exit(EXIT_FAILURE);
    }
    printf("Esperando que termine el hilo hijo\n");
    printf("proceso papa %i \n", pthread_self());
    
    if (pthread_join(id_hilo1, &valor_retorno)){
        printf("Problema al crear enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if (pthread_join(id_hilo2, &valor_retorno)){
        printf("Problema al crear enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if (pthread_join(id_hilo3, &valor_retorno)){
        printf("Problema al crear enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }
    if (pthread_join(id_hilo4, &valor_retorno)){
        printf("Problema al crear enlace con otro hilo\n");
        exit(EXIT_FAILURE);
    }

    printf("El hilo que espera papa, regreso!!\n");
    printf("Nuevo resultado: %i \n", resultado);
    exit(EXIT_SUCCESS);
    
}

void *funcion_suma(void *args){
    printf("Entro el hilo: %i a sumar.\n",pthread_self());
    
    for (int i = 0; i < 10; i++)
    {
        printf("Sumando...\n");
        sleep(3);
        resultado += 2;
        printf("Resultado: %i\n",resultado);
    }
    pthread_exit(NULL);
}

void *funcion_resta(void *args){
    printf("Entro el hilo: %i a restar.\n",pthread_self());
    
    for (int i = 0; i < 10; i++)
    {
        printf("Restando...\n");
        sleep(3);
        resultado -= 1;
        printf("Resultado: %i\n",resultado);
    }
    pthread_exit(NULL);
}

void *funcion_multi(void *args){
    printf("Entro el hilo: %i a multiplicar.\n",pthread_self());
    
    for (int i = 0; i < 10; i++)
    {
        printf("Multiplicando...\n");
        sleep(3);
        resultado *= 2;
        printf("Resultado: %i\n",resultado);
    }
    pthread_exit(NULL);
}

void *funcion_div(void *args){
    printf("Entro el hilo: %i a dividir.\n",pthread_self());
    
    for (int i = 0; i < 10; i++)
    {
        printf("Dividiendo...\n");
        sleep(3);
        resultado /= 3;
        printf("Resultado: %i\n",resultado);
    }
    pthread_exit(NULL);
}