
/* ------------------------------------------------------------
	DESTRUCTION D'UN SEMAPHORE NON NOMME
	IDENTIFICATEUR :	ptr_sema.
   ------------------------------------------------------------ */

	ret_val = sem_destroy ( ptr_sema );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_destroy failed !!!" ) ;

