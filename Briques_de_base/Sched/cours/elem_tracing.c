/* ************************************************************

	TEST POSIX 1003.1b
	==================

	EXPERIMENTATION DE SCHEDULING.

	SCHED_FIFO, fifo, rr, fifo, rr.

	pri : 40,40,40,40,40.

	On a 4 processus
	qui affichent respectivement
		des AAA ...


	IN.PR.E.S.
	LABORATOIRE D'INFORMATIQUE INDUSTRIELLE.

	DATE DE CREATION	: 29/01/1996.
	DATE DE REVISION	: 15/11/2001.
	REVISION TraceEvent	: 1/2/2015

	AUTEUR	: STARZAK Richard.

   ************************************************************ */

#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <sys/mman.h>
#include<sys/neutrino.h>
#include<sys/trace.h>



/* DECLARATION POUR LE CHANGEMENT DE SCHEDULING */


int	my_pid = 0 ;

int	i, ret_val ;

int	sched_policy ;



struct	sched_param	param ;


void	code_process_1 (),
	code_process_2 (),
	code_process_3 (),
	code_process_4 ();




/* ============================================================
	DEBUT DU MAIN.
   =========================================================== */

main ()

{

pid_t	pid_process_1,
	pid_process_2,
	pid_process_3,
	pid_process_4;

/*
 * Just in case, turn off all filters, since we
 * don't know their present state - go to the
 * known state of the filters.
 */


TraceEvent(_NTO_TRACE_DELALLCLASSES);
TraceEvent(_NTO_TRACE_CLRCLASSPID, _NTO_TRACE_KERCALL);
TraceEvent(_NTO_TRACE_CLRCLASSTID, _NTO_TRACE_KERCALL);
TraceEvent(_NTO_TRACE_CLRCLASSPID, _NTO_TRACE_USER);
TraceEvent(_NTO_TRACE_CLRCLASSTID, _NTO_TRACE_USER);

TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_SYSTEM);
TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_COMM);
TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_INT_HANDLER_ENTER);
TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_INT_HANDLER_EXIT);

TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_USER);
TraceEvent(_NTO_TRACE_ADDCLASS, _NTO_TRACE_CONTROL); //I ADDED THIS

/*
 * Intercept only user events
 */

TraceEvent(_NTO_TRACE_START);

TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_controller, begin");

/* ------------------------------------------------------------
	VERROUILLE EN MEMOIRE TOUTES LES PAGES D'UN PROCESSUS
	FLAGS		: MCL_CURRENT | MCL_FUTURE.
   ------------------------------------------------------------ */

	ret_val = mlockall( MCL_CURRENT | MCL_FUTURE );
	if ( ret_val == -1)
	perror ( "\n\rMAIN : mlockall failed !!!" ) ;



/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			0.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( 0 );
	if ( sched_policy == -1 )
	perror ( "\n\rMAIN : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rMAIN : la police de depart est : %d", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			0,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( 0, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_getparam failed !!!" ) ;

	printf ( "\n\rMAIN : priorite depart : %d", param.sched_priority );

/* ------------------------------------------------------------
	SPECIFIER LA POLICE DE SCHEDULING D'UN PROCESSUS
	ET EVENTUELLEMENT LA PRIORITE
	PID :			0,
	POLICE :		SCHED_FIFO,
	PARAMETRES :		param.
   ------------------------------------------------------------ */

	param.sched_priority = 40 ;

	ret_val = sched_setscheduler ( my_pid, SCHED_FIFO, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_setscheduler failed !!!" ) ;



/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			0.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( 0 );
	if ( sched_policy == -1 )
	perror ( "\n\rMAIN : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rMAIN : la police specifiee est : %d", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			0,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( 0 , &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_getparam failed !!!" ) ;

	printf ( "\n\rMAIN : priorite specifiee : %d", param.sched_priority );






/* ------------------------------------------------------------
	CREATION DU PROCESSUS process_1.
   ------------------------------------------------------------ */

	TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_controller, create PS_1");


	pid_process_1 = fork () ;
	if ( pid_process_1 == -1 )
		perror ( "fork : process_1 !!!" ), _exit ( 1 ) ;

	if ( pid_process_1 == 0 )
		{
		/* execution du processus fils */

		code_process_1 () ;

		_exit ( 1 ) ;
		};

	/* execution du processus pere */




/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			pid_process_1.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( pid_process_1 );
	if ( sched_policy == -1 )
	perror ( "\n\rMAIN : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rMAIN : police PS_1 : %d", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			pid_process_1,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( pid_process_1, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_getparam failed !!!" ) ;

	printf ( "\n\rMAIN : priorite depart : %d", param.sched_priority );


/* ------------------------------------------------------------
	CREATION DU PROCESSUS process_2.
   ------------------------------------------------------------ */

	TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_controller, create PS_2");


	pid_process_2 = fork () ;
	if ( pid_process_2 == -1 )
		perror ( "fork : process_2 !!!" ), _exit ( 1 ) ;

	if ( pid_process_2 == 0 )
		{
		/* execution du processus fils */

		code_process_2 () ;

		_exit ( 1 ) ;
		};


	/* execution du processus pere */


/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			pid_process_2.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( pid_process_2 );
	if ( sched_policy == -1 )
	perror ( "\n\rMAIN : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rMAIN : police PS_2 : %d", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			pid_process_2,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( pid_process_2, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_getparam failed !!!" ) ;

	printf ( "\n\rMAIN : priorite depart : %d", param.sched_priority );

/* ------------------------------------------------------------
	CREATION DU PROCESSUS process_3.
   ------------------------------------------------------------ */

	TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_controller, create PS_3");

	pid_process_3 = fork () ;
	if ( pid_process_3 == -1 )
		perror ( "fork : process_3 !!!" ), _exit ( 1 ) ;

	if ( pid_process_3 == 0 )
		{
		/* execution du processus fils */

		code_process_3 () ;

		_exit ( 1 ) ;
		};

	/* execution du processus pere */


/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			pid_process_3.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( pid_process_3 );
	if ( sched_policy == -1 )
	perror ( "\n\rMAIN : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rMAIN : police PS_3 : %d", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			pid_process_3,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( pid_process_3, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_getparam failed !!!" ) ;

	printf ( "\n\rMAIN : priorite depart : %d", param.sched_priority );

/* ------------------------------------------------------------
	CREATION DU PROCESSUS process_4.
   ------------------------------------------------------------ */

	TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_controller, create PS_4");

	pid_process_4 = fork () ;
	if ( pid_process_4 == -1 )
		perror ( "fork : process_4 !!!" ), _exit ( 1 ) ;

	if ( pid_process_4 == 0 )
		{
		/* execution du processus fils */

		code_process_4 () ;

		_exit ( 1 ) ;
		};

	/* execution du processus pere */

sleep (1);


/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			pid_process_4.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( pid_process_4 );
	if ( sched_policy == -1 )
	perror ( "\n\rMAIN : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rMAIN : police PS_4 : %d", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			pid_process_4,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( pid_process_4, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_getparam failed !!!" ) ;

	printf ( "\n\rMAIN : priorite depart : %d", param.sched_priority );







/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			0.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( 0 );
	if ( sched_policy == -1 )
	perror ( "\n\rMAIN : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rMAIN : la police de depart est : %d", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			0,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( 0, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_getparam failed !!!" ) ;

	printf ( "\n\rMAIN : priorite depart : %d", param.sched_priority );









/* ------------------------------------------------------------
	DE-VERROUILLE TOUTES LES PAGES D'UN PROCESSUS
   ------------------------------------------------------------ */

	ret_val = munlockall( );
	if ( ret_val == -1)
	perror ( "\n\rMAIN : munlockall failed !!!" ) ;


	TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_controller, end");


	 TraceEvent(_NTO_TRACE_STOP);



exit ( 1) ;


}

/* =============================================================
	FIN DU MAIN.
   ============================================================= */




/* ============================================================
	CODE DU PROCESSUS process_1.
   ============================================================ */

void	code_process_1 ()

{

int	i, j ;

TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_begin PS_1");

/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			0.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( 0 );
	if ( sched_policy == -1 )
	perror ( "\n\rPS_1 : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rPS_1 : la police de depart est : %d", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			0,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( 0, &param );
	if ( ret_val == -1 )
	perror ( "\n\rPS_1 : sched_getparam failed !!!" ) ;

	printf ( "\n\rPS_1 : priorite depart : %d", param.sched_priority );



/* ------------------------------------------------------------
	SPECIFIER LA POLICE DE SCHEDULING D'UN PROCESSUS
	ET EVENTUELLEMENT LA PRIORITE
	PID :			0,
	POLICE :		SCHED_FIFO,
	PARAMETRES :		param.
   ------------------------------------------------------------ */

	ret_val = sched_setscheduler ( my_pid, SCHED_FIFO, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_setscheduler failed !!!" ) ;



/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			0.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( 0 );
	if ( sched_policy == -1 )
	perror ( "\n\rPS_1 : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rPS_1 : la police est : %d", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			0,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( 0, &param );
	if ( ret_val == -1 )
	perror ( "\n\rPS_1 : sched_getparam failed !!!" ) ;

	printf ( "\n\rPS_1 : priorite specifiee : %d", param.sched_priority );

for ( i=0 ; i<10 ; i++ ){

	TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_1, running");

	write( 1, "AAAAAAAAAA\n", 11);

	for ( j=0; j<100; j++);

	};

TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_end PS_1");

}

/* ============================================================
	FIN DU CODE DU PROCESSUS process_1.
   ============================================================ */


/* ============================================================
	CODE DU PROCESSUS process_2.
   ============================================================ */

void	code_process_2 ()

{

int	i, j ;

TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_begin PS_2");

/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			0.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( 0 );
	if ( sched_policy == -1 )
	perror ( "\n\rPS_2 : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rPS_2 : la police de depart est %d : ", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			0,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( 0, &param );
	if ( ret_val == -1 )
	perror ( "\n\rPS_2 : sched_getparam failed !!!" ) ;

	printf ( "\n\rPS_1 : prioritee depart : %d", param.sched_priority );



/* ------------------------------------------------------------
	SPECIFIER LA POLICE DE SCHEDULING D'UN PROCESSUS
	ET EVENTUELLEMENT LA PRIORITE
	PID :			0,
	POLICE :		SCHED_FIFO,
	PARAMETRES :		param.
   ------------------------------------------------------------ */

	ret_val = sched_setscheduler ( my_pid, SCHED_FIFO, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_setscheduler failed !!!" ) ;


/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			0.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( 0 );
	if ( sched_policy == -1 )
	perror ( "\n\rPS_2 : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rPS_2 : la police est %d : ", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			0,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( 0, &param );
	if ( ret_val == -1 )
	perror ( "\n\rPS_2 : sched_getparam failed !!!" ) ;

	printf ( "\n\rPS_2 : priorite specifiee : %d", param.sched_priority );



	for ( i=0 ; i<10 ; i++ ){

		TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_2, running");

		write( 1, "BBBBBBBBBB\n", 11);

		for ( j=0; j<100; j++);

		};


TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_end PS_2");

}

/* ============================================================
	FIN DU CODE DU PROCESSUS process_2.
   ============================================================ */


/* ============================================================
	CODE DU PROCESSUS process_3.
   ============================================================ */

void	code_process_3 ()

{

int	i, j ;

TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_begin PS_3");

/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			0.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( 0 );
	if ( sched_policy == -1 )
	perror ( "\n\rPS_3 : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rPS_3 : la police de depart est %d : ", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			0,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( 0, &param );
	if ( ret_val == -1 )
	perror ( "\n\rPS_3 : sched_getparam failed !!!" ) ;

	printf ( "\n\rPS_3 : priorite depart : %d", param.sched_priority );




/* ------------------------------------------------------------
	SPECIFIER LA POLICE DE SCHEDULING D'UN PROCESSUS
	ET EVENTUELLEMENT LA PRIORITE
	PID :			0,
	POLICE :		SCHED_FIFO,
	PARAMETRES :		param.
   ------------------------------------------------------------ */

	ret_val = sched_setscheduler ( my_pid, SCHED_FIFO, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_setscheduler failed !!!" ) ;


/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			0.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( 0 );
	if ( sched_policy == -1 )
	perror ( "\n\rPS_3 : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rPS_3 : la police est %d : ", sched_policy );

/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			0,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( 0, &param );
	if ( ret_val == -1 )
	perror ( "\n\rPS_3 : sched_getparam failed !!!" ) ;

	printf ( "\n\rPS_3 : priorite specifiee : %d", param.sched_priority );


	for ( i=0 ; i<10 ; i++ ){

		TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_3, running");

		write( 1, "CCCCCCCCCC\n", 11);

		for ( j=0; j<100; j++);

		};


TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_end PS_3");

}

/* ============================================================
	FIN DU CODE DU PROCESSUS process_3.
   ============================================================ */


/* ============================================================
	CODE DU PROCESSUS process_4.
   ============================================================ */

void	code_process_4 ()

{

int	i, j ;

TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_begin PS_4");

/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			0.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( 0 );
	if ( sched_policy == -1 )
	perror ( "\n\rPS_4 : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rPS_4 : la police de depart est %d : ", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			0,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( 0, &param );
	if ( ret_val == -1 )
	perror ( "\n\rPS_4 : sched_getparam failed !!!" ) ;

	printf ( "\n\rPS_4 : priorite depart : %d", param.sched_priority );



/* ------------------------------------------------------------
	SPECIFIER LA POLICE DE SCHEDULING D'UN PROCESSUS
	ET EVENTUELLEMENT LA PRIORITE
	PID :			0,
	POLICE :		SCHED_FIFO,
	PARAMETRES :		param.
   ------------------------------------------------------------ */

	ret_val = sched_setscheduler ( my_pid, SCHED_FIFO, &param );
	if ( ret_val == -1 )
	perror ( "\n\rMAIN : sched_setscheduler failed !!!" ) ;



/* ------------------------------------------------------------
	RECUPERER LA POLICE DE SCHEDULING D'UN PROCESSUS
	PID :			0.
   ------------------------------------------------------------ */

	sched_policy = sched_getscheduler ( 0 );
	if ( sched_policy == -1 )
	perror ( "\n\rPS_4 : sched_getscheduler failed !!!" ) ;

	printf ( "\n\rPS_4 : la police est %d : ", sched_policy );


/* ------------------------------------------------------------
	RECUPERER LES PARAMETRES DE SCHEDULING D'UN PROCESSUS
	PID :			0,
	PARAMETRES : 		param.
   ------------------------------------------------------------ */

	ret_val = sched_getparam ( 0, &param );
	if ( ret_val == -1 )
	perror ( "\n\rPS_4 : sched_getparam failed !!!" ) ;

	printf ( "\n\rPS_4 : priorite specifiee : %d", param.sched_priority );


	for ( i=0 ; i<10 ; i++ ){

		TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_4, running");

		write( 1, "DDDDDDDDDD\n", 11);

		for ( j=0; j<100; j++);

		};


TraceEvent(_NTO_TRACE_INSERTUSRSTREVENT, _NTO_TRACE_USERFIRST, "PROCESS_end PS_4");

}

/* ============================================================
	FIN DU CODE DU PROCESSUS process_4.
   ============================================================ */


