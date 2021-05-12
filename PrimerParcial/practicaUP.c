#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<pthread.h>
#include <semaphore.h>
#define NH 3

void LeerP1(char[]readbuffer,int j,int nbytes,char*key,char[]delimitador,int x,int fd2,int fd);
void LeerP2(char[]readbuffer,int j,int nbytes,char*key,char[]delimitador,int x,int fd2,int fd);
void EscribirP1(int fd,int aleat,int j,char[] dest,char[]saludo);
void EscribirP2(int fd2,int aleat,int j,char[] dest,char[]saludo);

int main(){
    int fd[2],fd2[2],nbytes;
    pid_t proc;
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
            if(j%2 == 0){
                EscribirP1(fd,aleat,j,dest,saludo);
                LeerP2(readbuffer, j,nbytes,key,delimitador,x,fd2,fd);
            }else{
                EscribirP2(fd2,aleat,j,dest,saludo);
                LeerP1(readbuffer, j,nbytes,key,delimitador,x,fd2,fd);
            }
        }
    } 
    return 0;
}

void LeerP2(char readbuffer,int j,int nbytes,char*key,char delimitador,int x,int fd2,int fd){
    nbytes = read(fd2[0],readbuffer,sizeof(readbuffer));
    printf("Hijo %d lee [%d] carac: %s\n",j,nbytes,readbuffer);
    if(nbytes == -1)printf("No había nada que leer");
    else{
        key = strtok(readbuffer,delimitador);//separa el destinatario
        x = atoi(key); //key a integer
        if(key != NULL) printf("Key = %s\n",key); 
        if(x == j)printf("\t%d.-Mensaje Recibido! [%s]\n",j,readbuffer);   
        else {//Devuelve el mensaje en p1
            close(fd[0]);//cierra el descriptor de lectura
            //envía el saludo por el descriptor de escritura
            printf("Hijo %d DEVUELVE el mensaje\n",j);
            printf("Mensaje DEVUELTO = %s\n",readbuffer);
            write(fd[1],readbuffer,strlen(readbuffer));         
        }              
    }
}

void LeerP1(char readbuffer,int j,int nbytes,char*key,char delimitador,int x,int fd2,int fd){
    nbytes = read(fd[0],readbuffer,sizeof(readbuffer));
    printf("Hijo %d lee [%d] carac: %s\n",j,nbytes,readbuffer);
    if(nbytes == -1)printf("No había nada que leer");
    else{
        key = strtok(readbuffer,delimitador);//separa el destinatario
        x = atoi(key); //key a integer
        if(key != NULL) printf("Key = %s\n",key); 
        if(x == j)printf("\t%d.-Mensaje Recibido! [%s]\n",j,readbuffer);   
        else {//Devuelve el mensaje en p2
            close(fd2[0]);//cierra el descriptor de lectura
            //envía el saludo por el descriptor de escritura
            printf("Hijo %d DEVUELVE el mensaje\n",j);
            printf("Mensaje DEVUELTO = %s\n",readbuffer);
            write(fd2[1],readbuffer,strlen(readbuffer));         
        }              
    }

}

void EscribirP1(int fd,int aleat,int j,char dest,char saludo){
    close(fd[0]);//cierra el descriptor de lectura
    //envía el saludo por el descriptor de escritura
    printf("Hijo %d escribe\n",j);
    do{
        aleat = rand()%3;//genera un destinatario (distinto a sí mismo)
    }while(aleat == j);
    //printf("J = %d\tAleat = %d\n",j,aleat);
    sprintf(dest,"%d",aleat); //convierto el aleat a string
    strcat(dest,saludo); //concateno el pid con el mensaje
    printf("Mensaje enviado = %s\n",dest);
    write(fd[1],dest,strlen(dest));
    sleep(3); 
}

void EscribirP2(int fd2,int aleat,int j,char dest,char saludo){
    close(fd2[0]);//cierra el descriptor de lectura
    //envía el saludo por el descriptor de escritura
    printf("Hijo %d escribe\n",j);
    do{
        aleat = rand()%3;//genera un destinatario (distinto a sí mismo)
    }while(aleat == j);
    //printf("J = %d\tAleat = %d\n",j,aleat);
    sprintf(dest,"%d",aleat); //convierto el aleat a string
    strcat(dest,saludo); //concateno el pid con el mensaje
    printf("Mensaje enviado = %s\n",dest);
    write(fd2[1],dest,strlen(dest));
    sleep(3);
}