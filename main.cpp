#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include "utils.h"


int idShm, idSem;
char *buf, *ptr;

int main()
{
	//sémaphore
	if((idSem = semget(KEY, 1 ,IPC_CREAT|IPC_EXCL|0600)) == -1)
	{
		perror("Erreur sémaphore");
		exit(0);
	}
	printf("Semaphore cree ! \n");
	
	
	//Création de la mémoire partagée
	if((idShm = shmget(KEY,(size_t)TAILLEBUF*sizeof(char),IPC_CREAT | IPC_EXCL|0600)) == -1)
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
	
	
	
	shmctl(idShm, IPC_RMID,0);
	semctl(idSem, IPC_RMID,0);
	exit(0);
}










































