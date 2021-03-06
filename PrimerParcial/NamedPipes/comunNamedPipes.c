/*
Programa que comunica dos procesos donde uno escribe y otro lee
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#define MAX 26

int main(){
    int pid,*edo;
    char pipe1Nombre[MAX] = "fifo";//id de la tubería
    char mssg [MAX]= " ";
    int fifo1;
    
    //crea la tubería 
    int err = mknod(pipe1Nombre,S_IFIFO | 0666,0);

    if(err == 0){
        pid = fork();
        if(pid==0){
            printf("Codigo HIJO 1\n");
            fifo1 = open(pipe1Nombre,O_WRONLY);
            strcpy(mssg,"ENVIANDO");
            printf("H1 manda : %s\n",mssg);
            write(fifo1,mssg,strlen(mssg)+1);
            close(fifo1);
            exit(0);
        }else{
            printf("Soy el padre\n");
            wait(&pid);
        }
    }else{
        pid = fork();
        if(pid==0){
            printf("Codigo HIJO 2\n");
            fifo1 = open(pipe1Nombre,O_RDONLY);
            read(fifo1,mssg,MAX);
            printf("H2 recibe : %s\n",mssg);
            close(fifo1);
            exit(0);
        }
        else{
            printf("Soy el padre\n");
            wait(&pid);
        }
    }
    return 0;
}
