
/* -------------------------------------------------------------
	DE-ALLOCATION D'UNE PAGE DE LA MEMOIRE PARTAGEE
	IDENTIFICATEUR :	shm_fd,
	LONGUEUR :		250.
   ------------------------------------------------------------- */

	ret_val = munmap ( shm_ptr, 250 );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : munmap failed !!!" );

