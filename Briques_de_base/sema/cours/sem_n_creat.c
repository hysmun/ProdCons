/*
	TRAME DE BASE POUR LA CREATION D'UN SEMAPHORE NOMME	
	POSIX 1003.1b
*/

#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>




/* DECLARATIONS POUR L'UTILISATION D'UN SEMAPHORE NOMME */

sem_t	*ptr_sema ;
int	oflag = O_CREAT ;
mode_t	mode = 0644 ;
const	char	semname [] = "/tmp/sema" ;
unsigned	int	value = 0 ;


int 	ret_val ;






/* ------------------------------------------------------------
	CREATION D'UN SEMAPHORE NOMME	
	IDENTIFICATEUR :	ptr_sema
	NOM : 			semname [] = "/tmp/sema",
	FLAGS :			oflags = O_CREAT,
	MODE : 			mode = 644,
	VALEUR INITIALE : 	value = 1.
   ------------------------------------------------------------ */

	ptr_sema = sem_open ( semname, oflag, mode, value );
	if ( ptr_sema == (void *) -1 )
	perror ( "\n\rMAIN : sem_open failed !!!" );
	





/* ------------------------------------------------------------
	DESTRUCTION D'UN SEMAPHORE NOMME
	NOM : 			semname [] = "/tmp/sema",
   ------------------------------------------------------------ */

	ret_val = sem_unlink ( semname );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_unlink failed !!!" ) ;

