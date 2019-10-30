#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int N, contador = 0, contador2 = 0;
int matriz1[2000][2000], matriz2[2000][2000], matriz3[2000][2000];
pid_t filho1, filho2;

void imprimir1(){
    int i, j;
    for(i = 0; i < N/2; i++){
        for(j = 0; j < N; j++){
            if(j)printf(" ");
            printf("%d", matriz3[i][j]);
        }
        printf("\n");
    }
}

void imprimir2(){
    int i, j;
    for(i = N/2; i < N; i++){
        for(j = 0; j < N; j++){
            if(j)printf(" ");
            printf("%d", matriz3[i][j]);
        }
        printf("\n");
    }
}

void fpronto(){
    contador++;
    //printf("contador = %d\n", contador);
}

void f2pronto(){
    contador2++;
    //printf("contador2 = %d\n", contador2);
}

int main(){

    int i, j, k, f1, f2;
    int aux1 = 0, aux2 = 0;
    
    scanf("%d", &N);

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            scanf("%d", &matriz1[i][j]);
        }
    }

    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            scanf("%d", &matriz2[i][j]);
        }
    }

    signal(SIGUSR1, fpronto);
    signal(SIGUSR2, f2pronto);

    filho1 = fork();
    if(filho1 == 0){

        for(i = 0; i < N/2; i++){
            for(j = 0; j < N; j++){
                for(k = 0; k < N; k++){
                    aux1 += matriz1[i][k]*matriz2[k][j];
                }
                matriz3[i][j] = aux1;
                aux1 = 0;
            }
        }
        signal(SIGUSR1, imprimir1);


        kill(getppid(), SIGUSR1);
        pause();
        //signal(SIGUSR1, imprimir1);
        //sleep(2);

    }else{
        filho2 = fork();
        if(filho2 == 0){
            
            for(i = N/2; i < N; i++){
            for(j = 0; j < N; j++){
                for(k = 0; k < N; k++){
                    aux2 += matriz1[i][k]*matriz2[k][j];
                }
                matriz3[i][j] = aux2;
                aux2 = 0;
            }
        }
            signal(SIGUSR2, imprimir2);

            kill(getppid(), SIGUSR2);
            pause();
            // signal(SIGUSR2, imprimir2);
            //sleep(2);

        }else{

            while(contador == 0 || contador2 == 0){
                pause();
            }
            //pause();
            
            
            if(contador == 1){
                kill(filho1, SIGUSR1);
                wait(&f1);
            }

            if(contador2 == 1){
                kill(filho2, SIGUSR2);
                wait(&f2);
            }
        }
        
    }

    return 0;
}
