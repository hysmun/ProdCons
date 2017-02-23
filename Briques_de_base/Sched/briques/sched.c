#include <sched.h>


/* DECLARATIONS POUR LES CHANGEMENTS DE SCHEDULING */

int		my_pid = 0 ;

int		ret_val ;

int		sched_policy ;



struct	sched_param	param ;


struct	timespec	interval_rr ;


