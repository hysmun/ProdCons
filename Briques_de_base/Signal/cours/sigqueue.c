/*
	TRAME DE BASE POUR L'UTILISATION DES SIGNAUX :
	UTILISATION DE sigqueue,
	RECCUPERATION des informations du signal.
*/



#include <sys/types.h>
#include <errno.h>
#include <signal.h>



/* DECLARATIONS POUR L'UTILISATION DE SIGNAUX */


struct	sigaction	sig_act;
void	handler_signaux();

union	sigval	sigval_appl ;

int	ret_val;




/* ------------------------------------------------------------
	DEFINIR LE COMPORTEMENT DU PROCESSUS COURANT
	POUR UN SIGNAL DONNE
	COMPORTEMENT	: HANDLER
		        	handler_signaux,
	SIGNAL		: SIGUSR1,
	FLAGS		: SA_SIGINFO.
   ------------------------------------------------------------ */

	sig_act.sa_handler = handler_signaux ;
	sig_act.sa_flags = SA_SIGINFO ;

	ret_val = sigaction ( SIGUSR1 , &sig_act, 0 );
	if ( ret_val == -1 )
	perror ( "\n\rMain !!! ERREUR sigaction" );







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



/* ------------------------------------------------------------
	GESTIONNAIRE DE SIGNAUX.
   ------------------------------------------------------------ */

void	handler_signaux ( int signal, siginfo_t *siginfo_hdler , int *val )
{
printf ("\n\rHandler, signal : %d ", signal );

printf ("\n\rHandler, si_signo : %d ", siginfo_hdler->si_signo );
printf ("\n\rHandler, si_code : %d ", siginfo_hdler->si_code );
printf ("\n\rHandler, si_value : %d ", siginfo_hdler->si_value.sival_int );
}

