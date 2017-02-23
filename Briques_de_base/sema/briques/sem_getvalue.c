
/* ------------------------------------------------------------
	RECUPERER LA VALEUR D'UN SEMAPHORE
	IDENTIFICATEUR :	ptr_sema
	VALEUR :		ptr_sem_val.
   ------------------------------------------------------------ */

	ret_val = sem_getvalue ( ptr_sema, ptr_sem_val );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_getvalue failed !!!" ) ;

	printf ( "sem_val : %d\n\r", sem_val );

