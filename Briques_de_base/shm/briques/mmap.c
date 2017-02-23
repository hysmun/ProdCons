
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

