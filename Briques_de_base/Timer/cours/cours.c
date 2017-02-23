/* ***********************************************************

LES TIMERS : trame de base.

*********************************************************** */

#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

#define	ABSOLUTE_TIMER	1
#define RELATIVE_TIMER	0


struct	sigaction	sig_act;
void	handler_signaux();


int		ret_val;


timer_t	timer_id ;
struct	itimerspec	timer_def ;



/* ------------------------------------------------------------
	DEFINITION DU COMPORTEMEMT DU PROCESSUS
	POUR LE SIGNAL : SIGALARM.
   ------------------------------------------------------------ */
	
	sig_act.sa_handler = handler_signaux ;
	sig_act.sa_flags = SA_SIGINFO ;
	ret_val = sigaction ( SIGALRM, &sig_act, 0 );
	if ( ret_val == -1 )
	perror ( "\n\rMain !!! ERREUR sigaction" );


/* ------------------------------------------------------------
	SET A REPETITIVE TIMER timer_id.
   ------------------------------------------------------------ */

	timer_id = timer_create ( CLOCK_REALTIME, 0, ... );
	if ( timer_id == -1 )
	perror ( "\n\rMain !!! ERREUR timer_create" );

	timer_def.it_value.tv_sec = 2 ;
	timer_def.it_value.tv_nsec = 0 ;
	timer_def.it_interval.tv_sec = 1 ;
	timer_def.it_interval.tv_nsec = 0 ;

	ret_val = timer_settime ( timer_id, RELATIVE_TIMER, &timer_def, 0);
	if ( ret_val == -1 )
	perror ( "\n\rMain !!! ERREUR timer_settime" );

