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
	short *array;
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
	arg_sem.val = 0;
	semctl(idSem, 0, SETALL, arg_sem);
}

int SemWait(int idSem, int Sema)
{
	struct sembuf SemOp;
	
	SemOp.sem_num = Sema;
	SemOp.sem_op = -1;
	SemOp.sem_flg = SEM_UNDO;
	
	return semop(idSem, &SemOp, 1);
}

int SemSignal(int idSem, int Sema)
{
	struct sembuf SemOp;
	
	SemOp.sem_num = Sema;
	SemOp.sem_op = +1;
	SemOp.sem_flg = SEM_UNDO;
	
	return semop(idSem, &SemOp, 1);
}














