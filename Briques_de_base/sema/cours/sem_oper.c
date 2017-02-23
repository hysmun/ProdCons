/*
	TRAME DE BASE POUR LES OPERATIONS SUR LES SEMAPHORES
	POUR POSIX 1003.1b
*/

int	sem_val, *ptr_sem_val = &sem_val ;




/* ------------------------------------------------------------
	RECUPERER LA VALEUR D'UN SEMAPHORE
	IDENTIFICATEUR :	ptr_sema
	VALEUR :		ptr_sem_val.
   ------------------------------------------------------------ */

	ret_val = sem_getvalue ( ptr_sema, ptr_sem_val );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_getvalue failed !!!" ) ;

	printf ( "sem_val : %d\n\r", sem_val );




/* ------------------------------------------------------------
	VALIDER UN SEMAPHORE
	IDENTIFICATEUR : 	ptr_sema
   ------------------------------------------------------------ */

	ret_val = sem_post ( ptr_sema ) ;
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_post failed !!!" ) ;




/* ------------------------------------------------------------
	ATTENDRE UN SEMAPHORE
	IDENTIFICATEUR :	ptr_sema
   ------------------------------------------------------------ */

	ret_val = sem_wait ( ptr_sema ) ;
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_wait failed !!!" ) ;




/* ------------------------------------------------------------
	ATTENDRE SANS BLOCAGE UN SEMAPHORE
	IDENTIFICATEUR :	ptr_sema
   ------------------------------------------------------------ */

	ret_val = sem_trywait ( ptr_sema ) ;
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sem_trywait failed !!!" ) ;
