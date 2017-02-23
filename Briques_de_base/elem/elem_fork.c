/* ***********************************************************

APPLICATION POSIX ELEMENTAIRE.

*********************************************************** */

#include <sys/types.h>


void	code_process_1 (),
	code_process_2 (),
	code_process_3 ();



/* ============================================================
	DEBUT DU MAIN.
   ============================================================ */

main ()

{

pid_t	pid_process_1,
	pid_process_2,
	pid_process_3;


/* ------------------------------------------------------------
	CREATION DU PROCESSUS process_1.
   ------------------------------------------------------------ */


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
	CREATION DU PROCESSUS process_2.
   ------------------------------------------------------------ */

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
	CREATION DU PROCESSUS process_3.
   ------------------------------------------------------------ */

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


	while ( 1 )
	{

	/* on boucle indefiniment */

	};

}

/* =============================================================
	FIN DU MAIN.
   ============================================================= */




/* ============================================================
	CODE DU PROCESSUS process_1.
   ============================================================ */

void	code_process_1 ()

{

int	var_process_1 ;


	while ( 1 )
	{

		write ( 2, "AAAAAAAAAA\n\r", 12 ) ;

	};

}

/* ============================================================
	FIN DU CODE DU PROCESSUS process_1.
   ============================================================ */


/* ============================================================
	CODE DU PROCESSUS process_2.
   ============================================================ */

void	code_process_2 ()

{

int	var_process_2 ;


	while ( 1 )
	{

		write ( 2, "BBBBBBBBBB\n\r", 12 ) ;

	};

}

/* ============================================================
	FIN DU CODE DU PROCESSUS process_2.
   ============================================================ */


/* ============================================================
	CODE DU PROCESSUS process_3.
   ============================================================ */

void	code_process_3 ()

{

int	var_process_3 ;


	while ( 1 )
	{

		write ( 2, "CCCCCCCCCC\n\r", 12 ) ;

	};

}

/* ============================================================
	FIN DU CODE DU PROCESSUS process_3.
   ============================================================ */


