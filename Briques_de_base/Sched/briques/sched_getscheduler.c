
/* ------------------------------------------------------------
	RECUPERER LA POLITIQUE DE SCHEDULING D'UN PROCESSUS
	PID :			my_pid.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( my_pid );
	if ( sched_policy == -1 )
	perror ( "\n\rMAIN : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rMAIN : politique = %d", sched_policy ) ;
