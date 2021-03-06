#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include "utils.h"

char *buf, caracActu;
int idSem;
int idShm;

int pid = getpid();
int numero;
int posActu;

int main(int argc, char *argv[])
{
	numero = atoi(argv[1]);
	printf("\nProducteur numero %d! %d \n", numero, pid);
	//sémaphore   0:buffer    1:elemDispo   2:placeDispo
	idSem = SemInit(0);
	
	
	//Création de la mémoire partagée
	idShm = ShmInit(0);
	buf = ShmAttach(idShm);
	(numero%2) == 0 ? caracActu ='a' : caracActu='A';
	
	posActu=0;
	for(int i=0; 1;i++)
	{
		//wait Place dispo
		SemWait(idSem, SEMPLACE);
		
		//zone de traitement
		printf("\tProd %d -- %d\t\t\t", numero, i);
		
		//production carac
		caracActu = prodCarac(buf, numero, caracActu, &posActu);
		
		//affichage Buffer
		AfficheTab(buf);
		
		//signal Elem dispo     + temps d'attente
		SemSignal(idSem, SEMELEM);
		SleepRand(0, 5);
	}
	exit(1);
}






































