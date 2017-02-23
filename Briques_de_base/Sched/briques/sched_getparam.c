
/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			my_pid,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */
	
	ret_val = sched_getparam ( my_pid, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_getparam failed !!!" ) ;

	printf ( "\n\rMAIN : priority = %d", param.sched_priority );

