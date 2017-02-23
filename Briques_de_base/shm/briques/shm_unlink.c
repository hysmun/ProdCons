
/* -------------------------------------------------------------
	EFFACEMENT DE L'OBJET MEMOIRE PARTAGEE
	NOM :		 "/tmp/toto".
   ------------------------------------------------------------- */

	ret_val = shm_unlink ( "/tmp/toto" ); 
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : shm_unlink failed !!!" );

