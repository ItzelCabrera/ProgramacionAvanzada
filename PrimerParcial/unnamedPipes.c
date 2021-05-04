#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int fd[2],fd2[2],nbytes;
    pid_t proc;
    char saludo[] = "Hola. Este es un mensaje";
    char respuesta[] = "Hola. Esta es una respuesta";
    char readbuffer[80];
    
    if(pipe(fd)==-1){
        printf("Hubo error al crear la tubería 1\n");
        exit(1);
    }if(pipe(fd2)==-1){
        printf("Hubo error al crear la tubería 2\n");
        exit(1);
    }
    if((proc = fork()) == -1){
        printf("Ocurrión un error\n");
        exit(1);
    }
    if(proc == 0){//hijo
        printf("Entra hijo\n");
        //cierra el descriptor de lectura
        close(fd[0]);
        //envía el saludo por el descriptor de escritura
        printf("Hijo escribe\n");
        write(fd[1],saludo,strlen(saludo));
        //cierra el descriptor de escritura
        close(fd2[1]);
        //lee mediante el descritor de lectura
        nbytes = read(fd2[0],readbuffer,sizeof(readbuffer));
        printf("Hijo lee [%d carac]: %s\n",nbytes,readbuffer);
        exit(0);
    }else{
        printf("Entra padre\n");
        //Cierra el descritor de escritura
        close(fd[1]);
        //lee desde el decriptor de lectura
        nbytes = read(fd[0],readbuffer,sizeof(readbuffer));
        printf("Padre lee [%d] carac: %s\n",nbytes,readbuffer);
        //cierra el descriptor de lectura
        close(fd2[0]);
        //escribe mediante el descriptor de escritura
        printf("Padre responde\n");
        write(fd2[1],respuesta,strlen(respuesta)); 

        wait(&proc);
    }
    
    return 0;
        

}
