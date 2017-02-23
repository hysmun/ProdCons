/*******************************************************************/
/* Description: Mise en oeuvre des memoires partagees locales      */
/* Auteur: Jean-Yves Hercot                                        */
/* Date: 01/06/2003                                                */
/*******************************************************************/

#include<unistd.h>
#include<semaphore.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>

void Process_Fils(void);

void Handler_SigInt(int sig);

int fils;

char car;

/* DECLARATIONS POUR L'UTILISATION D'UN SEMAPHORE NON NOMME */

sem_t *ptr_sema;
int	pshared = 1;
unsigned int value = 1;
int sem_val,*ptr_sem_val = &sem_val; 

/* DECLARATIONS POUR L'UTILISATION D'UNE MEMOIRE PARTAGEE */

caddr_t	shm_ptr,shm_sema;


int ret_val;

struct sigaction sig_act;

main()
{
 struct timespec Time;
 char lettre = 'A';

 sig_act.sa_handler = Handler_SigInt;
 ret_val = sigaction (SIGINT,&sig_act, 0);
 if (ret_val == -1)
 perror("\n\rMAIN : sigaction failed !!!");

/* -------------------------------------------------------------
        CREATION D'UNE MEMOIRE PARTAGEE LOCALE
        IDENTIFICATEUR :        -1,
        LONGUEUR :              sizeof(sem_t),
        PROTECTION :            PROT_WRITE | PROT_READ,
        FLAGS :                 MAP_ANONYMOUS | MAP_VARIABLE.
   ------------------------------------------------------------- */

 shm_sema = mmap ( 0, sizeof(sem_t), PROT_WRITE | PROT_READ , MAP_ANONYMOUS | MAP_SHARED , -1, 0 );
 if ( *shm_sema == -1 )
 perror ( "\n\rMAIN : mmap failed !!!" );

 ptr_sema = (sem_t*)shm_sema;

/* ------------------------------------------------------------
        CREATION D'UN SEMAPHORE NON NOMME
        IDENTIFICATEUR :        ptr_sema,
        SHARED :                pshared = TRUE,
        VALEUR INITIALE :       value = 1.
   ------------------------------------------------------------ */

 ret_val = sem_init (ptr_sema, pshared, value);
 if (ret_val == -1)
 perror("\n\rMAIN : sem_open failed !!!");

/* -------------------------------------------------------------
	CREATION D'UNE MEMOIRE PARTAGEE LOCALE	
	IDENTIFICATEUR :	-1,
	LONGUEUR :		1,
	PROTECTION :		PROT_WRITE | PROT_READ,
	FLAGS :			MAP_ANONYMOUS | MAP_VARIABLE.	
   ------------------------------------------------------------- */

 shm_ptr = mmap ( 0, 1, PROT_WRITE | PROT_READ , MAP_ANONYMOUS | MAP_SHARED , -1, 0 );
 if ( *shm_ptr == -1 )
 perror ( "\n\rMAIN : mmap failed !!!" );

 fils = fork();
 if (!fils)
    {
     Process_Fils();
    }
 while (1)
    {
/* ------------------------------------------------------------
	ATTENDRE UN SEMAPHORE
	IDENTIFICATEUR :	ptr_sema
   ------------------------------------------------------------ */

     ret_val = sem_wait (ptr_sema);
     if (ret_val == -1)
     perror ("\n\rMAIN : sem_wait failed !!!");

     *shm_ptr = lettre;
     if (lettre == 'Z')
        {
         lettre = 'A';
        }
     else
        {
         lettre++;
        } 

/* ------------------------------------------------------------
	VALIDER UN SEMAPHORE
	IDENTIFICATEUR : 	ptr_sema
   ------------------------------------------------------------ */

     ret_val = sem_post (ptr_sema);
     if ( ret_val == -1)
     perror ("\n\rMAIN : sem_post failed !!!");

     Time.tv_sec = 5;
     Time.tv_nsec = 0;
     nanosleep(&Time,NULL);
    }
}


void Process_Fils (void)
{
 struct timespec Time;
 signal(SIGINT,SIG_IGN);
 while (1)
    {
     Time.tv_sec = 1;
     Time.tv_nsec = 0;
     nanosleep(&Time,NULL);

/* ------------------------------------------------------------
	ATTENDRE UN SEMAPHORE
	IDENTIFICATEUR :	ptr_sema
   ------------------------------------------------------------ */

     ret_val = sem_wait (ptr_sema);
     if (ret_val == -1)
     perror ("\n\rMAIN : sem_wait failed !!!");

     car = *shm_ptr;

/* ------------------------------------------------------------
	VALIDER UN SEMAPHORE
	IDENTIFICATEUR : 	ptr_sema
   ------------------------------------------------------------ */

     ret_val = sem_post (ptr_sema);
     if ( ret_val == -1)
     perror ("\n\rMAIN : sem_post failed !!!");

     printf("(PROCESS_FILS) Lettre lue : %c\n",car);
     
    }
}

void Handler_SigInt(int sig)
{

/* ------------------------------------------------------------
	DESTRUCTION D'UN SEMAPHORE NON NOMME
	IDENTIFICATEUR :	ptr_sema.
   ------------------------------------------------------------ */

 ret_val = sem_destroy (ptr_sema);
 if ( ret_val == -1)
 perror("\n\rMAIN : sem_unlink failed !!!");

/* -------------------------------------------------------------
	DE-ALLOCATION D'UNE PAGE DE LA MEMOIRE PARTAGEE
	IDENTIFICATEUR :	shm_fd,
	LONGUEUR :		1.
   ------------------------------------------------------------- */

 ret_val = munmap(shm_ptr,1);
 if ( ret_val == -1)
 perror("\n\rMAIN : munmap failed !!!");

 kill(fils,SIGKILL);
 exit(0); 
}
