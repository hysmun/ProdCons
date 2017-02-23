
/* ------------------------------------------------------------
	ENVOI D'UN SIGNAL DONNE A UN PROCESSUS DONNE	
	SIGNAL		: SIGUSR1,
	PROCESSUS	: pid_process_1,
	VALEUR		: 2008.	
   ------------------------------------------------------------ */
	sigval_appl.sival_int = 2008L ;

	ret_val = sigqueue( pid_process_1, SIGUSR1 , sigval_appl );
	if ( ret_val == -1 )
	perror ( "\n\rMain !!! ERREUR sigqueue" );
