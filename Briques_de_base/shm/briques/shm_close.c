
/* -------------------------------------------------------------
	FERMETURE DE LA MEMOIRE PARTAGEE
	IDENTIFICATEUR :	shm_fd.
   ------------------------------------------------------------- */

	ret_val = close ( shm_fd );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : close failed !!!" );

