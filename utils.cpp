#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <ctype.h>
#include "utils.h"

//union necessaire pour l'init de semaphore
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
}arg_sem;

void initTab(char *ptab)
{
	if(ptab == NULL)
	{
		printf("tab vide \n");
		return;
	}
	//initialisation de TAILLEBUF carac de ptab
	printf("init tab\n");
	for(int i=0; i < TAILLEBUF; i++)
	{
		ptab[i]='P';
	}
}

void AfficheTab(char *ptab)
{	
	if(ptab == NULL)
	{
		printf("tab vide \n");
		return;
	}
	
	//on affiche TAILLEBUF carac du buffer
	printf("Buffer : ");
	for(int i=0; i < TAILLEBUF; i++)
	{
		printf("%c", ptab[i]);
	}
	printf("\n");
}

int SemWait(int idSem, int Sema)
{
	struct sembuf SemOp[2];
	
	//pour l'acces buf
	SemOp[0].sem_num = 0;
	SemOp[0].sem_op = -1;
	SemOp[0].sem_flg = 0;
	
	// soit PLACEDISPO soit ELEMDISPO
	SemOp[1].sem_num = Sema;
	SemOp[1].sem_op = -1;
	SemOp[1].sem_flg = 0;
	if(semop(idSem, SemOp, 2) == -1)
	{
		perror("Erreur wait !!");
		return -1;
	}
	return 1;
}

int SemSignal(int idSem, int Sema)
{
	struct sembuf SemOp[2];
	
	//pour l'acces buf
	SemOp[0].sem_num = 0;
	SemOp[0].sem_op = +1;
	SemOp[0].sem_flg = 0;
	
	// soit PLACEDISPO soit ELEMDISPO
	SemOp[1].sem_num = Sema;
	SemOp[1].sem_op = +1;
	SemOp[1].sem_flg = 0;
	
	if(semop(idSem, SemOp, 2) == -1)
	{
		perror("Erreur signal !!");
		return -1;
	}
	return 1;
}

int ShmInit(int flag)
{
	int idShm;
	//on cree ou recupere l'idShm
	if((idShm = shmget(KEY,(size_t)TAILLEBUF*sizeof(char),flag)) == -1)
	{
		perror("Erreur de memoire partagee");
		exit(0);
	}
	
	printf("Shm cree !\n");
	return idShm;
}

int SemInit(int flag)
{
	int idSem;
	//on cree ou recupere l'idSem
	if((idSem = semget(KEY, 3 ,flag)) == -1)
	{
		perror("Erreur sémaphore !");
		exit(0);
	}
	printf("Semaphore obtenue ! \n");
	if(flag != 0)
	{
		// si il n'y a pas de flag donc pas de construction alors on init les semaphore
		printf("Semaphore init val\n");
		// 0:buffer    1:ELEMDISPO      2:PLACEDISPO
		unsigned short Val[] = {1,TAILLEBUF,0};
		arg_sem.array = Val;
		semctl(idSem, 0, SETALL, arg_sem);
	}
	return idSem;
}

char *ShmAttach(int idShm)
{
	char *buf;
	// on attach le Shm a buf
	buf = (char *)shmat(idShm,NULL,0);
	if(buf == (char *)-1)
	{
		perror("Shm fail !");
	}
	printf("Shm ratacher! \n");
	return buf;
}

char prodCarac(char *buf, int numero, char Actu, int *posActu)
{
	if(buf == NULL)
		return -1;
	
	char carac=Actu;
	
	numero = numero%2;// 0 = minuscule     1 = MAJUSCULE
	if(carac == 'z' || carac == 'Z')
			numero==0 ? carac = 'a' : carac = 'A';
	for(int i=0; i<TAILLEBUF; i++)
	{
		if(*posActu == TAILLEBUF)
			*posActu = 0;
		// si non alphabetique on peut produire a cette place
		if(!isalpha((int)buf[*posActu]))
		{
			buf[*posActu] = carac;
			carac = (carac+1);//pour que le carac change au prochain
			(*posActu)++; 
			return carac;
		}
		(*posActu)++;
	}
	return carac;
}

int consCarac(char *buf, int numero, int *posActu)
{
	if(buf == NULL)
		return -1;
		
	for(int i=0; i<TAILLEBUF; i++)
	{
		if(*posActu == TAILLEBUF)
			*posActu = 0;
		//si c'est alphabetique on peut le consommer
		if(isalpha((int)buf[*posActu]))
		{
			buf[*posActu]='&';
			(*posActu)++;
			return 1;
		}
		(*posActu)++;
	}
	//on a rien trouver a consommer
	return -1;
}

int SleepRand(int min, int max)
{
	int temps = (rand()%(max-min))+min; // temps E [min, max-1]
	sleep(temps);
	return 1;
}
































