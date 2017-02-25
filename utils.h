#ifndef __UTILS_H__
#define __UTILS_H__

#define TAILLEBUF (20)
#define KEY (1337)


#define SEMBUF (1)
#define SEMELEM (2)
#define SEMPLACE (3)


void initTab(char *ptab);
void AfficheTab(char *ptab);
int SemInit(int idSem);
int SemWait(int idSem, int Sema);
int SemSignal(int idSem, int Sema);

int ShmInit(int flag);






























#endif // __UTILS_H__
