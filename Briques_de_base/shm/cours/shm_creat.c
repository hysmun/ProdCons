/*
	TRAME DE BASE POUR LA CREATION ET
	L'UTILISATION D'UNE MEMOIRE PARTAGEE
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
/* int	*shm_ptr; */
caddr_t   shm_ptr;




int	ret_val;




/* -------------------------------------------------------------
	CREATION D'UNE MEMOIRE PARTAGEE
	NOM :			"/tmp/toto",
	IDENTIFICATEUR :	shm_fd.
	FLAGS :			(O_CREAT | O_RDWR),
	MODE :			0.
   ------------------------------------------------------------- */

	shm_fd = shm_open ( "/tmp/toto", (O_CREAT | O_RDWR), 0 );  
	if ( shm_fd == -1 )
	perror ( "\n\rMAIN : shm_open failed !!!" );



/* -------------------------------------------------------------
	MODIFICATION DES PRIVILEGES D'ACCES
	 D'UNE MEMOIRE PARTAGEE
	IDENTIFICATEUR :	shm_fd.
	MODE :			S_IRRWXG | S_IRWXU | S_IRWXO.
   ------------------------------------------------------------- */

	ret_val = fchmod ( shm_fd , (mode_t) S_IRWXG | S_IRWXU | S_IRWXO );
	if ( ret_val == -1)
	perror ( "\n\rMAIN : fchmod failed !!!" );



/* -------------------------------------------------------------
	MODIFICATION DE LA TAILLE D'UNE MEMOIRE PARTAGEE
	IDENTIFICATEUR :	shm_fd.
  	TAILLE :		250. 
   ------------------------------------------------------------- */

	ret_val = ftruncate (shm_fd, 250);
	if (ret_val == -1)
	perror ( "\n\rMAIN : shm_open failed !!!" );




/* -------------------------------------------------------------
	MAPPING D'UNE PAGE DANS LA MEMOIRE PARTAGEE
	IDENTIFICATEUR :	shm_fd,
	LONGUEUR :		250,
	PROTECTION :		PROT_WRITE | PROT_READ,
	FLAGS :			MAP_SHARED.	
   ------------------------------------------------------------- */

	shm_ptr = mmap ( 0, 250, PROT_WRITE|PROT_READ, MAP_SHARED, shm_fd, 0 );
	if ( *shm_ptr == -1 )
	perror ( "\n\rMAIN : mmap failed !!!" );





	/* utilisation de la memoire partagee */





/* -------------------------------------------------------------
	DE-ALLOCATION D'UNE PAGE DE LA MEMOIRE PARTAGEE
	IDENTIFICATEUR :	shm_fd,
	LONGUEUR :		250.
   ------------------------------------------------------------- */

	ret_val = munmap ( shm_ptr, 250 );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : munmap failed !!!" );



/* -------------------------------------------------------------
	FERMETURE DE LA MEMOIRE PARTAGEE
	IDENTIFICATEUR :	shm_fd.
   ------------------------------------------------------------- */

	ret_val = close ( shm_fd );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : close failed !!!" );



/* -------------------------------------------------------------
	EFFACEMENT DE L'OBJET MEMOIRE PARTAGEE
	NOM :		 "/tmp/toto".
   ------------------------------------------------------------- */

	ret_val = shm_unlink ( "/tmp/toto" ); 
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : shm_unlink failed !!!" );

