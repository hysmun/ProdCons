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

int shmKey = 1337;
int shmId;
char *buf, *ptr;

int main()
{
	//Création de la mémoire partagée
	if(shmId = shmget(shmKey,TAILLEBUF,0644 | IPC_CREAT | IPC_EXCL) == -1)
	{
		perror("Erreur de memoire partagee");
		exit(0);
	}
	buf = (char*)shmat(shmId,NULL,0);
	printf("%p",buf);
	//Initialisation du tableau
	
	exit(0);
}










































