/*
	TRAME DE BASE POUR L'UTILISATION D'UNE MEMOIRE PARTAGEE
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

int	shm_fd;
caddr_t   shm_ptr;




int	ret_val;




/* -------------------------------------------------------------
	OUVERTURE D'UNE MEMOIRE PARTAGEE
	NOM :			"/tmp/toto",
	IDENTIFICATEUR :	shm_fd.
	FLAGS :			(O_RDWR),
	MODE :			0.
   ------------------------------------------------------------- */

	shm_fd = shm_open ( "/tmp/toto", (O_RDWR), 0 );  
	if ( shm_fd == -1 )
	perror ( "\n\rMAIN : shm_open failed !!!" );

