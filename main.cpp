#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <signal.h>
#include "utils.h"

int idShm, idSem;
char *buf, tmp[20];
int pidFilsProd[NBPROD];
int pidFilsCons[NBCONS];
int ret1,ret2,ret3;

int pid = getpid();

int main(int argc, char *argv[])
{
	//sémaphore   0:buffer    1:elemDispo   2:placeDispo
	idSem = SemInit(IPC_CREAT|IPC_EXCL|0600);
	
	
	//Création de la mémoire partagée
	idShm = ShmInit(IPC_CREAT|IPC_EXCL|0600);
	buf = ShmAttach(idShm);
	
	//Initialisation du tableau
	initTab(buf);
	AfficheTab(buf);
	
	printf("Creation prod et cons \n");
	//Fork producteur 
	for(int i=0; i<NBPROD; i++)
	{
		if((pidFilsProd[i] = fork()))
		{
			sprintf(tmp,"%d", i);
			execlp("./producteur","producteur",tmp,NULL);
			printf("Erreur exec\n");
			exit(0);
		}
		if(pidFilsProd[i] == -1)
		{
			perror("Erreur fork !");
			exit(0);
		}
	}
	
	//Fork consommateur
	for(int i=0; i<NBCONS; i++)
	{
		if((pidFilsCons[i] = fork()) )
		{
			sprintf(tmp,"%d", i);
			execlp("./consommateur","consommateur",tmp,NULL);
			printf("Erreur exec\n");
			exit(0);
		}
		if(pidFilsCons[i] == -1)
		{
			perror("Erreur fork !");
			exit(0);
		}
	}
	
	
	
	//Attente pour fin processus
	printf("Attente fin fils !\n");
	for(int i=0; i<(NBCONS+NBPROD); i++)
	{
		if(wait(NULL) < 0)
		{
			printf("Erreur wait\n");
			perror("truc");
		}
		printf("%d fils mort\n", i+1);
	}
	
	
	
	//Liberation des IPCs
	printf("fin prog + suppression IPC\n");
	//shmctl(idShm, IPC_RMID,0);
	//semctl(idSem, IPC_RMID,0);

	exit(0);
}










































