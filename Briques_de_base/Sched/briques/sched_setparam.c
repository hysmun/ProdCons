
/* ------------------------------------------------------------
	SPECIFIER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			my_pid,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */
	param.sched_priority = 40 ;
	
	ret_val = sched_setparam ( my_pid, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_setparam failed !!!" ) ;

