#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/types.h>
#include "utils.h"

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
}arg_sem;

void initTab(char *ptab)
{
	for(int i=0; i < TAILLEBUF; i++)
	{
		ptab[i]='P';
	}
}

void AfficheTab(char *ptab)
{	
	printf("Buffer : ");
	for(int i=0; i < TAILLEBUF; i++)
	{
		printf("%c", ptab[i]);
	}
	printf("\n");
}

int SemInit(int idSem)
{
	unsigned short Val[] = {0,0,TAILLEBUF};
	arg_sem.array = Val;
	semctl(idSem, 0, SETALL, arg_sem);
}

int SemWait(int idSem, int Sema)
{
	struct sembuf SemOp[2];
	
	SemOp[0].sem_num = 0;
	SemOp[0].sem_op = -1;
	SemOp[0].sem_flg = SEM_UNDO;
	
	SemOp[1].sem_num = Sema;
	SemOp[1].sem_op = -1;
	SemOp[1].sem_flg = SEM_UNDO;
	
	return semop(idSem, SemOp, 1);
}

int SemSignal(int idSem, int Sema)
{
	struct sembuf SemOp[2];
	
	SemOp[0].sem_num = 0;
	SemOp[0].sem_op = +1;
	SemOp[0].sem_flg = SEM_UNDO;
	
	
	SemOp[1].sem_num = Sema;
	SemOp[1].sem_op = +1;
	SemOp[1].sem_flg = SEM_UNDO;
	
	return semop(idSem, SemOp, 1);
}

int ShmInit(int flag)
{
	int idShm;
	if((idShm = shmget(KEY,(size_t)TAILLEBUF*sizeof(char),IPC_CREAT|IPC_EXCL|0600)) == -1)
	{
		perror("Erreur de memoire partagee");
		exit(0);
	}
	
	printf("Shm cree !\n");
	return idShm;
}












