#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>
#include<semaphore.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<pthread.h>
#define n_clientes 20

sem_t sE;
//semaforo para cada empleado
sem_t sC1;
sem_t sC2;
sem_t sP1;
sem_t sP2;
sem_t sD;
sem_t sM;
int na = 0; //num de asientos ocupados

void *Empleado(void *arg){
    int k = ((intptr_t)arg)+1;
    int n;
    switch(k){
        case 1:
            printf("Empleado 1 que corta cabello llegó\n");
            sem_getvalue(&sC1,&n);
            if(n == 3){
                sem_wait(&sC1);            
            }
            break;
        case 2:
            printf("Empleado 2 que corta cabello llegó\n");
            sem_getvalue(&sC2,&n);
            if(n == 3){
                sem_wait(&sC2);            
            }
            break;
        case 3:
            printf("Empleado 1 que pinta cabello llegó\n");
            sem_getvalue(&sP1,&n);
            if(n == 3){
                sem_wait(&sP1);            
            }
            break;
        case 4:
            printf("Empleado 2 que pinta cabello llegó\n");
            sem_getvalue(&sP2,&n);
            if(n == 3){
                sem_wait(&sP2);            
            }
            break;
        case 5:
            printf("Empleado que hace pedicure llegó\n");
            sem_getvalue(&sD,&n);
            if(n == 3){
                sem_wait(&sD);            
            }
            break;
        case 6:
            printf("Empleado que hace manicure llegó\n");
            sem_getvalue(&sM,&n);
            if(n == 3){
                sem_wait(&sM);            
            }
            break;
        default:
            printf("Error :c\n");
    }
}

void *Cliente(void *arg){
    int c = ((intptr_t)arg)+1; //numero del cliente
    int serv[4] = {0,0,0,0};
    int ns = (rand()%4)+1; //numero de servicios
    int aleat = 0;
    bool v = true;

    printf("Cliente #%d llegó!\n",c);
    printf("Cliente #%d requiere %d servicios\n",c,ns);
    //Generan los servicios
    if(ns <4){
        aleat = rand()%4;
        if(ns == 3){
            //escojo el unico servicio que no se hará
            for(int k = 0; k<4;k++){
                if(k!=aleat)serv[k] = 1;
            }
        }else if(ns == 2){
            int n_aleat = 0;
            do{
                n_aleat = rand()%4;
            }while(aleat == n_aleat);
            for(int k = 0; k<4;k++){
                if(k==aleat)serv[k] = 1;
                if(k==n_aleat)serv[k] = 1;
            }
        }else{
            //escojo el unico servicio que se hará
            serv[aleat] = 1;
        }
    }else{
        for(int k = 0; k<4;k++){
            serv[k] = 1;
        }
    }
    printf("Servicios del cliente-->[%d,%d,%d,%d]\n",serv[0],serv[1],serv[2],serv[3]);
    
    int n1,n2=0;
    while(v){
        if(na == 5){
            printf("Asientos ocupados, no se puede atender al cliente #%d\n",c);
            sem_wait(&sE);        
        }    
        if(ns == 0){
            printf("Ya se terminó de atender al cliente #%d\n",c);
            v = false;        
        }else{
            if(serv[0] == true){
                sem_getvalue(&sC1,&n1);
                sem_getvalue(&sC2,&n2);
                if(n1 == 2){
                    sem_wait(&sC1);//se ocupa un empleado
                    na++; //se ocupa un asiento
                    printf("El cortador 1, le está cortando el pelo al cliente #%d\n",c);
                    serv[0] = false;
                    ns--;//ya se realizó un servicio
                    sem_post(&sC1);//se desocupa un empleado
                    na--; //desocupa un asiento
                    sem_post(&sE); //los clientes esperando pueden competir por ser atendidos
                }else if(n2 == 2){
                    sem_wait(&sC2);//se ocupa un empleado
                    na++; //se ocupa un asiento
                    printf("El cortador 2, le está cortando el pelo al cliente #%d\n",c);
                    serv[0] = false;
                    ns--;//ya se realizó un servicio
                    sem_post(&sC2);//se desocupa un empleado
                    na--; //desocupa un asiento
                    sem_post(&sE); //los clientes esperando pueden competir por ser atendidos
                }
            }else if(serv[1] == true){
                sem_getvalue(&sP1,&n1);
                sem_getvalue(&sP2,&n2);
                if(n1 == 2){
                    sem_wait(&sP1);//se ocupa un empleado
                    na++; //se ocupa un asiento
                    printf("El pintador 1, le está pintando el pelo al cliente #%d\n",c);
                    serv[1] = false;
                    ns--;//ya se realizó un servicio
                    sem_post(&sP1);//se desocupa un empleado
                    na--; //desocupa un asiento
                    sem_post(&sE); //los clientes esperando pueden competir por ser atendidos
                }else if(n2 == 2){
                    sem_wait(&sP2);//se ocupa un empleado
                    na++; //se ocupa un asiento
                    printf("El pintador 2, le está pintando el pelo al cliente #%d\n",c);
                    serv[1] = false;
                    ns--;//ya se realizó un servicio
                    sem_post(&sP2);//se desocupa un empleado
                    na--; //desocupa un asiento
                    sem_post(&sE); //los clientes esperando pueden competir por ser atendidos
                }
            }else if(serv[2] == true){
                sem_getvalue(&sD,&n1);
                if(n1 == 2){
                    sem_wait(&sD);//se ocupa un empleado
                    na++; //se ocupa un asiento
                    printf("Le están haciendo pedicure al cliente #%d\n",c);
                    serv[2] = false;
                    ns--;//ya se realizó un servicio
                    sem_post(&sD);//se desocupa un empleado
                    na--; //desocupa un asiento
                    sem_post(&sE); //los clientes esperando pueden competir por ser atendidos
                }
            }else if(serv[3] == true){
                sem_getvalue(&sM,&n1);
                if(n1 == 2){
                    sem_wait(&sM);//se ocupa un empleado
                    na++; //se ocupa un asiento
                    printf("Le están haciendo manicure al cliente #%d\n",c);
                    serv[3] = false;
                    ns--;//ya se realizó un servicio
                    sem_post(&sM);//se desocupa un empleado
                    na--; //desocupa un asiento
                    sem_post(&sE); //los clientes esperando pueden competir por ser atendidos
                }
            }
        }
    }

}

int main(){
    int k = 0;

    pthread_t cliente[n_clientes];  
    pthread_t empleado[6]; 
    
    sem_init(&sE,0,0);
    sem_init(&sC1,0,3);
    sem_init(&sC2,0,3);
    sem_init(&sP1,0,3);
    sem_init(&sP2,0,3);
    sem_init(&sD,0,3);
    sem_init(&sM,0,3);
    
    for(k = 0; k<n_clientes;k++){
        pthread_create(&cliente[k],0,&Cliente,(void*)(intptr_t)k);
    }
    
    for(k = 0; k<6;k++){
        pthread_create(&empleado[k],0,&Empleado,(void*)(intptr_t)k);
    }
    
    for(k=0;k<n_clientes;k++){
        pthread_join(cliente[k],NULL);    
    }

    sem_destroy(&sE);
    sem_destroy(&sC1);
    sem_destroy(&sC2);
    sem_destroy(&sP1);
    sem_destroy(&sP2);
    sem_destroy(&sD);
    sem_destroy(&sM);
    
    return 0;
}
