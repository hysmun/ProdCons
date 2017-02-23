
/* ------------------------------------------------------------
	FERMETURE D'UN SEMAPHORE NOMME
	IDENTIFICATEUR :	ptr_sema
   ------------------------------------------------------------ */

	ret_val = sem_close ( ptr_sema );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_close failed !!!" ) ;

