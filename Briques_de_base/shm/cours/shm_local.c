/*
	TRAME DE BASE POUR L'UTILISATION D'UNE MEMOIRE PARTAGEE LOCALE
	POSIX 1003.1b
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mode.h> 
 



/* DECLARATIONS POUR POUR L'UTILISATION D'UNE MEMOIRE PARTAGEE */

caddr_t   shm_ptr;



int	ret_val;




/* -------------------------------------------------------------
	CREATION D'UNE MEMOIRE PARTAGEE LOCALE	
	IDENTIFICATEUR :	-1,
	LONGUEUR :		25,
	PROTECTION :		PROT_WRITE | PROT_READ,
	FLAGS :			MAP_ANONYMOUS | MAP_SHARED.	
   ------------------------------------------------------------- */

	shm_ptr = mmap ( 0, 25, PROT_WRITE | PROT_READ , MAP_ANONYMOUS | MAP_SHARED , -1, 0 );
	if ( *shm_ptr == -1 )
	perror ( "\n\rMAIN : mmap failed !!!" );


	/* utilisation de la memoire partagee */




/* -------------------------------------------------------------
	DE-ALLOCATION D'UNE PAGE DE LA MEMOIRE PARTAGEE
	IDENTIFICATEUR :	shm_fd,
	LONGUEUR :		250.
   ------------------------------------------------------------- */

	ret_val = munmap ( shm_ptr , 25 );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : munmap failed !!!" );

