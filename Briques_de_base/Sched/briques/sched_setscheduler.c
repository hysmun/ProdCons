
/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			my_pid,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */
	
	ret_val = sched_getparam ( my_pid, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_getparam failed !!!" ) ;



/* ------------------------------------------------------------
	SPECIFIER LA POLITIQUE DE SCHEDULING D'UN PROCESSUS
	ET EVENTUELLEMENT LA PRIORITE
	PID :			my_pid,
	POLICE :		SCHED_RR,
	PARAMETRES :		param.
   ------------------------------------------------------------ */

	ret_val = sched_setscheduler ( my_pid, SCHED_RR, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_setscheduler failed !!!" ) ;

