#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <string.h>
#include "utils.h"

int idShm, idSem;
char *buf, *ptr;
int pidFils[3];
int ret1,ret2,ret3;


int pid = getpid();

int main(int argc, char *argv[])
{
	//sémaphore   1:buffer    2:elemDispo   3:placeDispo
	if((idSem = semget(KEY, 3 ,IPC_CREAT|IPC_EXCL|0600)) == -1)
	{
		perror("Erreur sémaphore");
		exit(0);
	}
	printf("Semaphore cree ! \n");
	
	
	//Création de la mémoire partagée
	if((idShm = shmget(KEY,(size_t)TAILLEBUF*sizeof(char),IPC_CREAT|IPC_EXCL|0600)) == -1)
	{
		perror("Erreur de memoire partagee");
		exit(0);
	}
	printf("Shm cree\n");
	buf = (char*)shmat(idShm,0,0);
	if(buf == (char*)-1)
	{
		printf("Shm fail\n");
	}
	printf("Shm rattachee\n");
	
	//Initialisation du tableau
	initTab(buf);
	AfficheTab(buf);

	//Fork producteur 1
	pidFils[0] = fork();
	if(!pidFils[0])
	{
		execl("producteur","producteur",NULL);
	}
	//Fork producteur 2
	pidFils[1] = fork();
	if(!pidFils[1])
	{
		execl("producteur","producteur",NULL);
	}
	//Fork consommateur
	pidFils[2] = fork();
	if(!pidFils[2])
	{
		execl("consommateur","consommateur",NULL);
	}
	
	
	
	//Attente pour fin processus
	ret1 = wait(NULL);
	ret2 = wait(NULL);
	ret3 = wait(NULL);
	
	
	
	//Liberation des IPCs
	shmctl(idShm, IPC_RMID,0);
	semctl(idSem, IPC_RMID,0);

	exit(0);
}










































