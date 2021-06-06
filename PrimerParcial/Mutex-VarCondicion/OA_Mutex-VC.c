//Cabrera Vazquez Itzel Berenice 2020640576
//Programa de operaciones aritmeticas protegiendo con MUTEX y VCond
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
int operacion = 0; //0 suma 1 resta 2 mult 3 division

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//Variables condionales
pthread_cond_t s = PTHREAD_COND_INITIALIZER;
pthread_cond_t r = PTHREAD_COND_INITIALIZER;
pthread_cond_t m = PTHREAD_COND_INITIALIZER;
pthread_cond_t d = PTHREAD_COND_INITIALIZER;

void* funcion(void* argumento);
void *suma(int res);
void *resta(int res);
void *division(int res);
void *multiplicacion(int res);

int main(){
    printf("\nPrograma de operaciones aritmeticas protegiendo con MUTEX y VCond\n");
    printf("PROCESO MAIN---%ld\n",pthread_self());

	pthread_t id[N_THREADS]; //array de id's

     //Los procesos son lanzados en orden de pila
	for(int j = 0; j<N_THREADS;j++){
		if(pthread_create(&id[j],NULL,&funcion,(void*)(intptr_t)j)){
			printf("\nError al crear el hilo\n");
			exit(EXIT_FAILURE);
		}
	}
    
    for(int j = 0; j<N_THREADS;j++){
		if(pthread_join(id[j],NULL)){
			printf("\nError al crear el hilo\n");
			exit(EXIT_FAILURE);
		}
	}
    

	return 0;
}

void* funcion(void* i){
    int hilo = (intptr_t)i;
	int res = resultado;
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
            while(operacion != 0){
                //printf("La suma se espera\n");
                pthread_cond_wait(&s,&mutex);             
            }
		    res = resultado;
		    resultado +=1;
		    printf("Hilo #%ld => (%d)+1 = %d\n",pthread_self(),res,resultado);
            if(operacion == 0){
                //printf("Terminó la suma, le da el turno a resta\n");
                pthread_cond_signal(&r);
                operacion = 1;
            }
        pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void *resta(int res){
	for(int k = 0; k<10;k++){
	    pthread_mutex_lock(&mutex);
            while(operacion != 1){
                //printf("La resta se espera\n");
                pthread_cond_wait(&r,&mutex);      
            }
		    res = resultado;
		    resultado -=1;
		    printf("Hilo #%ld => (%d)-1 = %d\n",pthread_self(),res,resultado);
            if(operacion == 1){
                    //printf("Terminó la resta, le da el turno a mult\n");
                    pthread_cond_signal(&m);
                    operacion = 2;
             }        
        pthread_mutex_unlock(&mutex);
		sleep(3);
	}
}

void *multiplicacion(int res){
	for(int k = 0; k<10;k++){
        pthread_mutex_lock(&mutex);
            while(operacion != 2){
                //printf("La mult se espera\n");
                pthread_cond_wait(&m,&mutex);      
            }
		    res = resultado;
		    resultado *=4;
		    printf("Hilo #%ld => (%d)*4 = %d\n",pthread_self(),res,resultado);
            if(operacion == 2){
                    //printf("Terminó la mult, le da el turno a div\n");
                    pthread_cond_signal(&d);
                    operacion = 3;
             }         
        pthread_mutex_unlock(&mutex);
		sleep(2);
	}
}

void *division(int res){
	for(int k = 0; k<10;k++){
        pthread_mutex_lock(&mutex);
            while(operacion != 3){
                //printf("La div se espera\n");
                pthread_cond_wait(&d,&mutex);      
            }		    
            res = resultado;
		    resultado /=4;
		    printf("Hilo #%ld => (%d)/4 = %d\n",pthread_self(),res,resultado);
            if(operacion == 3){
                    //printf("Terminó la div, le da el turno a sum\n");
                    pthread_cond_signal(&s);
                    operacion = 0;
             }         
        pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}
