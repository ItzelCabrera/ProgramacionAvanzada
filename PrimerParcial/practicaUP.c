#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<pthread.h>
#include <semaphore.h>
#define NH 3

int main(){
    int fd[2],fd2[2],nbytes;
    pid_t proc;
    char saludo[] = "/Hola. Este es un mensaje-";
    char readbuffer[80] = " ";
    int c = 0;

    //CREAN TUBERÍAS
    if(pipe(fd)==-1){
        printf("Hubo error al crear la tubería 1\n");
        exit(1);
    }if(pipe(fd2)==-1){
        printf("Hubo error al crear la tubería 2\n");
        exit(1);
    }
    
    //CREAN LOS HIJOS
    int i = 0;
    int j = 0;
    for(i = 0; i<NH;i++){
		proc = fork();
		if(proc <0){
			printf("Ocurrio un error");
		}if(proc == 0){//hijo
			//printf("\nSoy el proceso[%i], mi papa es [%i]\n",getpid(),getppid());
            j = i;
            break;
        }else{
           //printf("Entra padre %d\n",getpid());
           // wait(&proc);
            j = 3;
        }
	}

    //if (j == 0)printf("Soy el primer hijo : %d\n",getpid());
    //if (j == 1)printf("Soy el segundo hijo hijo : %d\n",getpid());
    //if (j == 2)printf("Soy el tercer hijo : %d\n",getpid());
    //if (j == 3)printf("Soy el padre : %d\n",getpid());
    
    char dest [40] = " ";
    char delimitador [2] = "/";
    char *key = " ";
    int aleat = 0;
    int x = 0;
    char rb[80] = " ";
    int k = 0;

    while(1){
        if(proc == 0){
            //ESCRIBE POR P1
            close(fd[0]);//cierra el descriptor de lectura
            //envía el saludo por el descriptor de escritura
            do{
                aleat = rand()%3;//genera un destinatario (distinto a sí mismo)
            }while(aleat == j);
            //printf("J = %d\tAleat = %d\n",j,aleat);
            sprintf(dest,"%d",aleat); //convierto el aleat a string
            strcat(dest,saludo); //concateno el numero de proceso con el mensaje
            printf("E DE : %d Mensaje = %s\n",j,dest);
            write(fd[1],dest,strlen(dest));
            //LEE POR P2
            close(fd2[1]);//Cierra el descritor de escritura
            strcpy(readbuffer,"");
            fflush(stdin);
            nbytes = read(fd2[0],readbuffer,sizeof(readbuffer));//lee desde el decriptor de lectura
            printf("L Hijo %d lee [%d carac] = %s\n",j,nbytes,readbuffer);
        }else{
            strcpy(readbuffer,"");
            fflush(stdin);
            close(fd[1]);//Cierra el descritor de escritura
            nbytes = read(fd[0],readbuffer,sizeof(readbuffer));//lee desde el decriptor de lectura 
            close(fd2[0]); //cierra el descriptor de lectura
            write(fd2[1],readbuffer,strlen(readbuffer));
            printf("El padre lee [%d carac] y devuelve el mensaje :%s\n",nbytes,readbuffer);
        }
    } 
    return 0;
}
