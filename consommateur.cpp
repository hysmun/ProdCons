#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include "utils.h"

char *buf;
int idSem;
int idShm;

int pid = getpid();

int main(int argc, char *argv[])
{
	printf("Consommateur ! \n");
	//sémaphore   1:buffer    2:elemDispo   3:placeDispo
	if((idSem = semget(KEY, 3 ,0)) == -1)
	{
		perror("Erreur sémaphore !");
		exit(0);
	}
	printf("Semaphore obtenue ! \n");
	
	
	//Création de la mémoire partagée
	if((idShm = shmget(KEY,(size_t)TAILLEBUF*sizeof(char),0)) == -1)
	{
		perror("Erreur de memoire partagee");
		exit(0);
	}
	printf("Shm obtenue");
	buf = (char*)shmat(idShm,NULL,0);
	if(buf == (char*)-1)
	{
		printf("Shm fail !\n");
	}
	printf("Shm ratacher! \n");
	
	
	for(int i=0; 1;i++)
	{
		SemWait(idSem, SEMELEM);
		//zone de traitement 
		
		SemSignal(idSem, SEMPLACE);
	}
	exit(0);
}






































