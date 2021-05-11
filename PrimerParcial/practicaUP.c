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
    int pid[NH];
    char saludo[] = "\tHola. Este es un mensaje";
    char respuesta[] = "\tHola. Esta es una respuesta";
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
			printf("\nSoy el proceso[%i], mi papa es [%i]\n",getpid(),getppid());
            j = i;
            pid[i] = getpid();
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
    char delimitador [] = "\t";
    char *key;
    int aleat = 0;
    int x = 0;

    while(1){
        strcpy(dest,""); //vacio el string que se manda como mensaje
        if (proc == 0){
            //cierra el descriptor de lectura
            close(fd[0]);
            //envía el saludo por el descriptor de escritura
            printf("Hijo %d escribe\n",getpid());
            //genera un numero aleatorio, el destinatario
            do{
               aleat = rand()%3;
            }while(aleat == j);
            printf("J = %d\tAleat = %d\n",j,aleat);
            sprintf(dest,"%d",aleat); //convierto el pid a string
            strcat(dest,saludo); //concateno el pid con el mensaje
            //printf("Mensaje = %s\n",dest);
            write(fd[1],dest,strlen(dest));
            //sleep(3);
            
        }else{
            /*
            //Cierra el descritor de escritura
            close(fd[1]);
            //lee desde el decriptor de lectura
            nbytes = read(fd[0],readbuffer,sizeof(readbuffer));
            printf("Padre lee [%d] carac: %s\n",nbytes,readbuffer);
            key = strtok(readbuffer,delimitador);
            if(key != NULL) printf("Key = %s\n",key);
            x = atoi(key); //key a integer
            switch(x){
                case 0:
                    printf("Mensaje para el primer hijo\n");
                    sem_wait(&s1); //disminuye el sem a 1
                    break;
                case 1:
                    printf("Mensaje para el segundo hijo\n");
                    sem_wait(&s2); //disminuye el sem a 1
                    break;
                case 2:
                    printf("Mensaje para el tercer hijo\n");
                    sem_wait(&s3); //disminuye el sem a 1
                    break;
                default:
                    printf("Error\n");
            }
        */
        }
    }
    
    sem_destroy(&s1);
    sem_destroy(&s2); 
    sem_destroy(&s3); 
    return 0;
        

}
