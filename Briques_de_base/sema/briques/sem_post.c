
/* ------------------------------------------------------------
	VALIDER UN SEMAPHORE
	IDENTIFICATEUR : 	ptr_sema
   ------------------------------------------------------------ */

	ret_val = sem_post ( ptr_sema ) ;
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_post failed !!!" ) ;

