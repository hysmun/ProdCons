/*
	BRIQUES DE BASE POUR L'UTILISATION DES MESSAGES QUEUES 
	POSIX 1003.1b
*/

#include <unistd.h>
#include <sys/types.h>
#include <mqueue.h>
#include <sys/fcntl.h> 
#include <signal.h>
#include <errno.h>

/* DECLARATIONS POUR L'UTILISATION DES MESSAGES QUEUES */

int mq_fd;
int priority;          
char message[25]; 
struct sigevent event;  
struct mq_attr attr;   

int ret_val;      

/* -------------------------------------------------------------
      CREATION D'UNE FILE DE MESSAGES
      NOM :	      "/tmp/toto",
      IDENTIFICATEUR: mq_fd.
      FLAGS:		   O_CREATE|O_RDWR,
      MODE:		   0777.
      ATTRIBUTS mq_attr: attr
   ------------------------------------------------------------- */
      attr.mq_maxmsg = 20;
      attr.mq_msgsize = 10;
      attr.mq_flags = 0;
    
      mq_fd = mq_open ("/tmp/toto",O_CREATE|O_RDWR,0777,&attr);  
      if (mq_fd == -1)	
      perror ("\n\rMAIN : mq_open failed !!!");

/* -------------------------------------------------------------
      OUVERTURE D'UNE FILE DE MESSAGES
      NOM :	      "/tmp/toto",
      IDENTIFICATEUR: mq_fd.
      FLAGS:		   (O_RDWR),
      MODE:		   0777.
   ------------------------------------------------------------- */
      
      mq_fd = mq_open ("/tmp/toto",O_RDWR,0777);  
      if (mq_fd == -1)	
      perror ("\n\rMAIN : mq_open failed !!!");

/* -------------------------------------------------------------
      RECUPERATION DES ATTRIBUTS D'UNE MESSAGE QUEUE
      IDENTIFICATEUR : mq_fd
   ------------------------------------------------------------- */

      ret_val = mq_getattr (mq_fd,&attr);
      if (ret_val == -1)
         perror ("\n\rMAIN : mq_getattr failed !!!");


/* -------------------------------------------------------------
      MODIFICATION DES ATTRIBUTS D'UNE MESSAGE QUEUE
      IDENTIFICATEUR : mq_fd,
      ATTRIBUTS mq_attr : Nombre maximum des messages: 20
                          Taille maximum des messages: 10
                          Flags: 0 
   ------------------------------------------------------------- */

      attr.mq_maxmsg = 20;
      attr.mq_msgsize = 10;
      attr.mq_flags = 0;

      ret_val = mq_setattr (mq_fd,&attr,NULL);
      if (ret_val == -1)
         perror ("\n\rMAIN : mq_setattr failed !!!");

/* -------------------------------------------------------------
      NOTIFICATION D'UN MESSAGE
      IDENTIFICATEUR : mq_fd,
      SIGNAL	: SIGUSR1.
   ------------------------------------------------------------- */

      event.sigev_signo = SIGUSR1;

      ret_val = mq_notify (mq_fd,&event);
      if (ret_val == -1)
         perror ("\n\rMAIN : mq_notify failed !!!");

/* -------------------------------------------------------------
      ENVOI D'UN MESSAGE
      IDENTIFICATEUR : mq_fd
      BUFFER: message 
      LONGUEUR: 25
      PRIORITE : 1
   ------------------------------------------------------------- */

      ret_val = mq_send (mq_fd,message,25,1);
      if (ret_val == -1)
         perror ("\n\rMAIN : mq_send failed !!!");

 
/* -------------------------------------------------------------
      RECEPTION D'UN MESSAGE 
      IDENTIFICATEUR: mq_fd.
      BUFFER: message 
      LONGUEUR: 25
   ------------------------------------------------------------- */

      ret_val = mq_receive (mq_fd,message,25,&priority);
      if (ret_val == -1)
         perror ("\n\rMAIN : mq_receive failed !!!");

/* -------------------------------------------------------------
      FERMETURE D'UNE FILE DE MESSAGES
      DESCRIPTEUR : mq_fd
   ------------------------------------------------------------- */

      ret_val = mq_close (mq_fd);
      if (ret_val == -1)
         perror ("\n\rMAIN : mq_close failed !!!");

/* -------------------------------------------------------------
      EFFACEMENT DE LA FILE DE MESSAGES 
      NOM : "/tmp/toto". 
   ------------------------------------------------------------- */

      ret_val = mq_unlink ("/tmp/toto");
      if (ret_val == -1)
         perror ("\n\rMAIN : mq_unlink failed !!!");

