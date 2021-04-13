#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

void *funcion_hilo(void *argumento);
char mensaje[]="Este es un mensaje";

int main(){
	printf("\nMensaje original: %s\n",mensaje);
	
	pthread_t id_hilo;
	void *valor_retorno; //valor que retornará cuando el papá espera al hijo hilo
	
	if(pthread_create(&id_hilo,NULL,funcion_hilo,(void *)mensaje)){
	/*
	si pthread_create regresa un valor != 0 --> hubo un errror
	NULL--> es un joinable
	en el caso que sí se pueda crear el hilo, se ejecuta la funcion_hilo
	el argumento de la funcion se debe castear a void*
	*/
		printf("\nProblema en la creación del hilo\n");
		exit(EXIT_FAILURE);
	}
	printf("\nPROCESO PAPA [%ld]\n",pthread_self());
	
	if(pthread_join(id_hilo,&valor_retorno)){//el papa entra en espera de su hijo
		printf("\nEsperando a que termine el hilo hijo\n");
		exit(EXIT_FAILURE);
	}
	printf("\nEl hilo que estaba esperando paá regresó--> %s\n",(char *)valor_retorno);
	printf("\nNuevo mensaje: %s\n",mensaje);

	exit(EXIT_SUCCESS);
}

void *funcion_hilo(void*argumento){
	printf("\nEjecutando 'funcion_hilo(%s)'.\n",(char *)argumento);
	printf("\nPROCESO HIJO [%ld]\n",pthread_self());
	sleep(2);
	printf("\nCambiando el mensaje\n");
	strcpy(mensaje,"mensaje cambiado");
	pthread_exit("{HIJO RETORNA 'GRACIAS'}");//retorna cuando el papa termine de esperarlo
}
