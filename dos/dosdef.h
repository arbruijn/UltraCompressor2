#ifndef DOSDEF_H_
#define DOSDEF_H_

#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define pascal
#define far
#define near
#define cdecl
#define _fastcall
#define huge

#define strnicmp(a, b, n) strncasecmp(a, b, n)
#define stricmp(a, b) strcasecmp(a, b)

char *strupr(char *);
char *strlwr(char *);

extern char **_argv;
extern int _argc;

int flushall();
//#define random(x) ((rand() * (long long)x) / ((long long)RAND_MAX + 1))

#define _fsopen(a, b, c) fopen(a, b)

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
inline int random(int n) { return(int)(((long)rand()*n)/((long)RAND_MAX+1)); }
inline void randomize(void) { srand((unsigned) time(NULL)); }
#endif

#endif
