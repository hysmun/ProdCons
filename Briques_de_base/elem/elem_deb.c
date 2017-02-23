/* ************************************************************


	TEST POSIX.
	==========

	TRAME DE BASE D'UN PROGRAMME POSIX.
	----------------------------------


	Programme elementaire
	pour l'appentissage du debugging.



	IN.PR.E.S.
	LABORATOIRE D'INFORMATIQUE INDUSTRIELLE.

	Digital UNIX 3.2c	
		POSIX 1003.1
		POSIX 1003.1b.


	DATE DE CREATION	: 14/11/1994.
	DATE DE REVISION	: 31/01/1997.

	AUTEUR	: STARZAK Richard.

   ************************************************************ */




#include <sys/types.h>



int	ret_val;



/* ============================================================
	DEBUT DU MAIN.
   ============================================================ */

main ()

{



/* ------------------------------------------------------------
	QUELQUES DEFINITIONS DE VARIABLES.
   ------------------------------------------------------------ */


int	var_int = 0 ;

int	*ptr_var_int ;


int	vect_int [5] ;


char	car = 'A', chaine_car [10] ;


struct	element
	{
	int	val ;
	char	cap ;
	}
	element_1, *ptr_el ;





/* ------------------------------------------------------------
	QUELQUES INITIALISATIONS DE VARIABLES.
   ------------------------------------------------------------ */

	ptr_var_int = &var_int ;

	strcpy ( chaine_car , "BONJOUR !" );

	vect_int [2] = 129 ;

	element_1.val = 120 ;
	element_1.cap = 'Z' ;

	ptr_el = &element_1 ;





	while ( 1 )
	{

	/* on boucle indefiniment */

	};

}

/* =============================================================
	FIN DU MAIN.
   ============================================================= */



