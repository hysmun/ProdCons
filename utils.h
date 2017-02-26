#ifndef __UTILS_H__
#define __UTILS_H__

#define TAILLEBUF (20)
#define KEY (1337)


#define SEMBUF (0)
#define SEMELEM (1)
#define SEMPLACE (2)

#define NBCONS (10)
#define NBPROD (10)

void initTab(char *ptab);
void AfficheTab(char *ptab);

int SemWait(int idSem, int Sema);
int SemSignal(int idSem, int Sema);

int ShmInit(int flag);
int SemInit(int flag);
char *ShmAttach(int idShm);

char prodCarac(char *buf, int numero, char Actu);
int consCarac(char *buf, int numero);

int SleepRand(int min, int max);
























#endif // __UTILS_H__
