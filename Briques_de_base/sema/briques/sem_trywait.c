
/* ------------------------------------------------------------
	ATTENDRE SANS BLOCAGE UN SEMAPHORE
	IDENTIFICATEUR :	ptr_sema
   ------------------------------------------------------------ */

	ret_val = sem_trywait ( ptr_sema ) ;
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_trywait failed !!!" ) ;
