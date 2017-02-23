/*
	TRAME DE BASE POUR LA CREATION D'UN SEMAPHORE NON NOMME	
	POSIX 1003.1b
*/

#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>




/* DECLARATIONS POUR L'UTILISATION D'UN SEMAPHORE NON NOMME */

sem_t	sem, *ptr_sema=&sem ;
int	pshared = TRUE ;
unsigned	int	value = 0 ;
int	sem_val, *ptr_sem_val = &sem_val ;


int 	ret_val ;


/* DECLARATIONS POUR L'UTILISATION D'UNE MEMOIRE PARTAGEE */

caddr_t shm_sema;

 
/* -------------------------------------------------------------
        CREATION D'UNE MEMOIRE PARTAGEE LOCALE
        IDENTIFICATEUR :        -1,
        LONGUEUR :              sizeof(sem_t),
        PROTECTION :            PROT_WRITE | PROT_READ,
        FLAGS :                 MAP_ANONYMOUS | MAP_SHARED.
   ------------------------------------------------------------- */

 shm_sema = mmap ( 0, sizeof(sem_t), PROT_WRITE | PROT_READ , MAP_ANONYMOUS | MAP_SHARED , -1, 0);
 if ( *shm_sema == -1 )
 perror ( "\n\rMAIN : mmap failed !!!" );

 ptr_sema = (sem_t*)shm_sema;



/* ------------------------------------------------------------
	CREATION D'UN SEMAPHORE NON NOMME	
	IDENTIFICATEUR :	ptr_sema,
	SHARED :		pshared = TRUE,
	VALEUR INITIALE : 	value = 1.
   ------------------------------------------------------------ */

	ret_val = sem_init ( ptr_sema, pshared , value );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_init failed !!!" );
	



/* ------------------------------------------------------------
	DESTRUCTION D'UN SEMAPHORE NON NOMME
	IDENTIFICATEUR :	ptr_sema.
   ------------------------------------------------------------ */

	ret_val = sem_destroy ( ptr_sema );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_destroy failed !!!" ) ;

