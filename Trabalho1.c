#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

char S[101];


void rm_min(){
	char palavra[101];
	for(int i = 0; i < strlen(S); i++){
		if(S[i] >= 'A' && S[i] <= 'Z'){
			palavra[i] = S[i];
			printf("%c", palavra[i]);
		}
	}
	printf("\n");
}

void rm_mai(){
	char palavra[101];
	for(int i = 0; i < strlen(S); i++){
		if(S[i] >= 'a' && S[i] <= 'z'){
			palavra[i] = S[i];
			printf("%c", palavra[i]);
		}
	}
	printf("\n");
}

void rm_vogais(){
	char palavra[101];
	for(int i = 0; i < strlen(S); i++){
		if(S[i] >= 'b' && S[i] <= 'd' || S[i] >= 'f' && S[i] <= 'h' || S[i] >= 'j' && S[i] <= 'n' || S[i] >= 'p' && S[i] <= 't' || S[i] >= 'v' && S[i] <= 'z' ||
				S[i] >= 'B' && S[i] <= 'D' || S[i] >= 'F' && S[i] <= 'H' || S[i] >= 'J' && S[i] <= 'N' || S[i] >= 'P' && S[i] <= 'T' || S[i] >= 'V' && S[i] <= 'Z' ){
			palavra[i] = S[i];
			printf("%c", palavra[i]);
		}
	}
	printf("\n");
}

void op_p1003(){
	pid_t p1005;
	int y;
	p1005 = fork();
	if(p1005 == 0){//Esse eh o 1005
		exit(strlen(S));
	}else{//Eh o processo 1003
		wait(&y);
		exit(WEXITSTATUS(y));
	}
}


int main(){

	pid_t p1002, p1003, p1004, p1006, p1007;
	int string, ep1004, s1004, teste;

	scanf("%s", S);
	
	p1002 = fork();
	if(p1002 == 0){//Eh o processo 1002
		p1004 = fork();
		if(p1004 == 0){
			signal(SIGUSR1, rm_min);
			pause();
			return getpid();
		}else{
			p1006 = fork();
			if(p1006 == 0){
				signal(SIGUSR2, rm_mai);
				pause();
				return getpid();
			}else{
				p1007 = fork();
				if(p1007 == 0){
					signal(SIGINT, rm_vogais);
					pause();
					return getpid();
				}
				sleep(1);
				kill(p1006, SIGUSR2);
				sleep(1);
				kill(p1007, SIGINT);
				sleep(1);
				kill(p1004, SIGUSR1);
				sleep(1);
			}
		}
	}else{//Eh o processo Pai
		p1003 = fork();
		if(p1003 == 0){//Eh o processo 1003
			op_p1003();
		}else{//Eh o processo Pai
			wait(&string);
			printf("Tamanho da string: %d\n", WEXITSTATUS(string));
			wait(&s1004);
			sleep(1);
			kill(p1004,SIGUSR1);
			sleep(1);
		}
	}

	return 0;
}
