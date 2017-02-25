#ifndef __UTILS_H__
#define __UTILS_H__


#define TAILLEBUF (20)
#define KEY (1337)


void AfficheTab(char *ptab);

int SemInit(int idSem);
int SemWait(int idSem, int Sema);
int SemSignal(int idSem, int Sema);
































#endif // __UTILS_H__
