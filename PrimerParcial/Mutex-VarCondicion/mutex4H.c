//Cabrera Vazquez Itzel Berenice 2020640576
//Programa de operaciones aritmeticas protegiendo con MUTEX
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>

int resultado = 3;
int N_THREADS = 4; //numero de hilos
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* funcion(void* argumento);
void *suma(int res);
void *resta(int res);
void *division(int res);
void *multiplicacion(int res);

int main(){
    printf("\nPrograma de operaciones aritmeticas protegiendo con MUTEX\n");
	pthread_t id[N_THREADS]; //array de id's
    int j = 0;
	printf("PROCESO MAIN---%ld",pthread_self());

     //Los procesos son lanzados en orden de pila
	for(j = 0; j<4;j++){
		if(pthread_create(&id[j],NULL,&funcion,(void*)(intptr_t)j)){
			printf("\nError al crear el hilo\n");
			exit(EXIT_FAILURE);
		}
	}
    
    //Se espera que termine dependiendo del orden de las funciones pthread_join
    for(j = 0; j<4;j++){		
		if(pthread_join(id[j],NULL)){
			printf("\nError al esperar al hilo hijo\n");
			exit(EXIT_FAILURE);
		}else{
            printf("\nProceso terminado\t");
            switch(j){
                case 0:
                    printf("SUMA\n");
                    break;
                case 1:
                    printf("RESTA\n");
                    break;
                case 2:
                    printf("MULT\n");
                    break;
                case 3:
                    printf("DIVISION\n");
                    break;
                default:
                    printf("error");            
            }        
        }
	}

	return 0;
}

void* funcion(void* i){
    int hilo = (intptr_t)i;
	int res = resultado;
	//printf("\n(%ld)\n",pthread_self());
	switch(hilo){
		case 0:
			suma(res);
			break;
		case 1:
			resta(res);
			break;
		case 2:
			multiplicacion(res);
			break;
		case 3:
			division(res);
			break;
		default:
			printf("\nError: funcion no encontrada\n");
			break;
	}
}

void *suma(int res){
	for(int k = 0; k<10;k++){
        pthread_mutex_lock(&mutex);
		int res = resultado;
		resultado +=1;
		printf("\nHilo #%ld => (%d)+1 = %d\n",pthread_self(),res,resultado);
        pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void *resta(int res){
	for(int k = 0; k<10;k++){
	    pthread_mutex_lock(&mutex);
		int res = resultado;
		resultado -=1;
		printf("\nHilo #%ld => (%d)-1 = %d\n",pthread_self(),res,resultado);
        pthread_mutex_unlock(&mutex);
		sleep(3);
	}
}

void *multiplicacion(int res){
	for(int k = 0; k<10;k++){
        pthread_mutex_lock(&mutex);
		int res = resultado;
		resultado *=4;
		printf("\nHilo #%ld => (%d)*4 = %d\n",pthread_self(),res,resultado);
        pthread_mutex_unlock(&mutex);
		//sleep(2);
	}
}

void *division(int res){
	for(int k = 0; k<10;k++){
        pthread_mutex_lock(&mutex);
		int res = resultado;
		resultado /=4;
		printf("\nHilo #%ld => (%d)/4 = %d\n",pthread_self(),res,resultado);
        pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}
