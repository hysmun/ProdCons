#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include "utils.h"


void AfficheTab(char *ptab)
{	
	printf("Buffer : ");
	for(int i=0; i < TAILLEBUF; i++)
	{
		printf("%c", ptab[i]);
	}
	printf("\n");
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














