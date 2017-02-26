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
int numero;
int posActu;

int pid = getpid();

int main(int argc, char *argv[])
{
	numero = atoi(argv[1]);
	printf("\nConsommateur %d! %d\n", numero, pid);
	//sémaphore   0:buffer    1:elemDispo   2:placeDispo
	idSem = SemInit(0);
	
	
	//Création de la mémoire partagée
	idShm = ShmInit(0);
	buf = ShmAttach(idShm);
	
	posActu=0;
	for(int i=0; 1;i++)
	{
		//wait Elem dispo
		SemWait(idSem, SEMELEM);
		
		//zone de traitement 
		printf("\t\tCons %d -- %d\t\t", numero, i);
		
		//consomation carac
		consCarac(buf, numero, &posActu);
		
		//affiche buffer
		AfficheTab(buf);
		
		//signal Place dispo      + temps d'attente
		SemSignal(idSem, SEMPLACE);
		SleepRand(0, 5);
	}
	exit(1);
}






































