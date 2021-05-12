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
    char respuesta[] = "/Hola. Esta es una respuesta-";
    char readbuffer[80] = " ";

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
    char delimitador2[2] = "-";
    char *key;
    int aleat = 0;
    int x = 0;
    char rb[80] = " ";
    char *mssg;

    while(1){
        strcpy(readbuffer,"");
        //printf("new readbuffer = %s\n",readbuffer);
        strcpy(rb,"");
        //printf("new rb = %s\n",rb);
        fflush(stdin);
        if (proc == 0){
            //ESCRIBE POR PIPE 1
            close(fd[0]);//cierra el descriptor de lectura
            //envía el saludo por el descriptor de escritura
            do{
                aleat = rand()%3;//genera un destinatario (distinto a sí mismo)
            }while(aleat == j);
            //printf("J = %d\tAleat = %d\n",j,aleat);
            sprintf(dest,"%d",aleat); //convierto el aleat a string
            strcat(dest,saludo); //concateno el numero de proceso con el mensaje
            printf("E1 DE : %d Mensaje = %s\n",j,dest);
            write(fd[1],dest,strlen(dest));
            sleep(3);
            //LEE POR PIPE 2
            close(fd2[1]);//Cierra el descritor de escritura
            nbytes = read(fd2[0],readbuffer,sizeof(readbuffer));//lee desde el decriptor de lectura
            if(nbytes = -1) printf("No hay mensaje\n");
            else{
                printf("L2 Hijo %d lee [%d] carac: %s\n",j,nbytes,readbuffer);
                strcpy(rb,readbuffer);
                printf(" rb = %s\n",rb);
                key = strtok(readbuffer,delimitador);
                if(key != NULL) printf("Key = %s\n",key);
                x = atoi(key); //key a integer
                if(x == j){
                    printf("%d.-Mensaje recibido! %s",j,rb);
                }else{
                    //DEVUELVE EL MENSAJE POR PIPE1
                    close(fd[0]);//cierra el descriptor de lectura
                    //devuelve el saludo por el descriptor de escritura
                    printf("D1 Mensaje DEVUELTO por %d= %s\n",j,rb);
                    write(fd[1],rb,strlen(rb));
                }
            }
        }else{
            //LEE POR PIPE 1
            close(fd[1]);//Cierra el descritor de escritura
            nbytes = read(fd[0],readbuffer,sizeof(readbuffer));//lee desde el decriptor de lectura
            printf("L1 Padre lee [%d] carac: %s\n",nbytes,readbuffer);
            mssg = strtok(readbuffer,delimitador2);
            while(mssg != NULL){
                printf("\t%s\n",mssg);
                strcpy(rb,mssg);
                printf(" rb = %s\n",rb);
                key = strtok(mssg,delimitador2);
                if(key != NULL) printf("Key = %s\n",key);
                x = atoi(key); //key a integer
                switch(x){
                    case 0:
                        printf("Mensaje para el primer hijo\n");
                        break;
                    case 1:
                        printf("Mensaje para el segundo hijo\n");
                        break;
                    case 2:
                        printf("Mensaje para el tercer hijo\n");
                        break;
                    default:
                        printf("Error\n");
                }
                //DEVUELVE EL MENSAJE POR PIPE2
                close(fd2[0]);//cierra el descriptor de lectura
                printf("Padre DEVUELVE el mensaje = %s\n",rb);//escribe mediante el descriptor de escritura
                write(fd2[1],rb,strlen(rb));  
                sleep(3);
                mssg = strtok(NULL,delimitador2);
            } 
        }
    } 
    return 0;
}
