#include "dosdef.h"

#ifdef __cplusplus
extern "C" {
#endif


void *farmalloc(int s);
void farfree(void *p);
#define farcoreleft() (600*1024)

#ifdef __cplusplus
}
#endif
