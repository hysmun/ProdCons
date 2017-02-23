
/* ------------------------------------------------------------
	ATTENDRE UN SEMAPHORE
	IDENTIFICATEUR :	ptr_sema
   ------------------------------------------------------------ */

	ret_val = sem_wait ( ptr_sema ) ;
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_wait failed !!!" ) ;

