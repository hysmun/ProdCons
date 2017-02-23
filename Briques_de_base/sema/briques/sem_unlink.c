
/* ------------------------------------------------------------
	DESTRUCTION D'UN SEMAPHORE NOMME
	NOM : 			semname [] = "/tmp/sema",
   ------------------------------------------------------------ */

	ret_val = sem_unlink ( semname );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_unlink failed !!!" ) ;

