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

void* funcion(void* argumento);
void *suma(int res);
void *resta(int res);
void *division(int res);
void *multiplicacion(int res);

int main(){
	pthread_t id[N_THREADS]; //array de id's
    int j = 0;
	printf("PROCESO MAIN---%ld",pthread_self());

     //Los procesos son lanzados en orden de pila
	for(j = 0; j<4;j++){
		if(pthread_create(&id[j],NULL,&funcion,(void*)(intptr_t)j)){
			printf("\nError al crear el hilo\n");
			exit(EXIT_FAILURE);
		}else{
			printf("\n{%ld}\n",pthread_self());
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

	/*pthread_t id1;
	pthread_t id2;
	pthread_t id3;
	pthread_t id4;

    void*valor_retorno;
	
	
	if(pthread_create(&id2,NULL,&funcion,(void*)(intptr_t)1)){
			printf("\nError al crear el hilo\n");
			exit(EXIT_FAILURE);
	}else{
        printf("\n{%ld}\n",pthread_self());
    }
	if(pthread_create(&id3,NULL,&funcion,(void*)(intptr_t)2)){
			printf("\nError al crear el hilo\n");
			exit(EXIT_FAILURE);
	}else{
        printf("\n{%ld}\n",pthread_self());
    }
	if(pthread_create(&id4,NULL,&funcion,(void*)(intptr_t)3)){
			printf("\nError al crear el hilo\n");
			exit(EXIT_FAILURE);
	}else{
        printf("\n{%ld}\n",pthread_self());
    }
    if(pthread_create(&id1,NULL,&funcion,(void*)(intptr_t)0)){
			printf("\nError al crear el hilo\n");
			exit(EXIT_FAILURE);
	}else{     
        printf("\n{%ld}\n",pthread_self());
    }
	
    //Se espera que termine dependiendo del orden de las funciones pthread_join
	if(pthread_join(id1,&valor_retorno)){
		printf("\nError al esperar al hilo hijo\n");
		exit(EXIT_FAILURE);
	}else{
        printf("%s SUMA",(char*)valor_retorno);
    }
	if(pthread_join(id2,&valor_retorno)){
		printf("\nError al esperar al hilo hijo\n");
		exit(EXIT_FAILURE);
	}else{
        printf("%s RESTA",(char*)valor_retorno);
    }
	if(pthread_join(id3,&valor_retorno)){
		printf("\nError al esperar al hilo hijo\n");
		exit(EXIT_FAILURE);
	}else{
        printf("%s MULT",(char*)valor_retorno);
    }
	if(pthread_join(id4,&valor_retorno)){
		printf("\nError al esperar al hilo hijo\n");
		exit(EXIT_FAILURE);
	}else{
        printf("%s DIVISION",(char*)valor_retorno);
    }
	*/
	return 0;
}

void* funcion(void* i){
	int hilo = (intptr_t)i;
	int res = resultado;
	printf("\n(%ld)\n",pthread_self());
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
    pthread_exit("Proceso terminado");		
}

void *suma(int res){
    //printf("\n-%ld-\n",pthread_self());
	for(int k = 0; k<10;k++){
		int res = resultado;
		resultado +=1;
	    printf("[%d]",res);
		printf("\nHilo #%ld => (%d)+1 = %d\n",pthread_self(),res,resultado);
		sleep(2);
	}
}

void *resta(int res){
    //printf("\n-%ld-\n",pthread_self());
	for(int k = 0; k<10;k++){
		int res = resultado;
		resultado -=1;
        printf("[%d]",res);
		printf("\nHilo #%ld => (%d)-1 = %d\n",pthread_self(),res,resultado);
		sleep(1);
	}
}

void *multiplicacion(int res){
    //printf("\n-%ld-\n",pthread_self());
	for(int k = 0; k<10;k++){
		int res = resultado;
		resultado *=4;
        printf("[%d]",res);
		printf("\nHilo #%ld => (%d)*4 = %d\n",pthread_self(),res,resultado);
		//sleep(1);
	}
}

void *division(int res){
    //printf("\n-%ld-\n",pthread_self());
	for(int k = 0; k<10;k++){
		int res = resultado;
		resultado /=4;
	    printf("[%d]",res);
		printf("\nHilo #%ld => (%d)/4 = %d\n",pthread_self(),res,resultado);
		sleep(3);
	}
}
