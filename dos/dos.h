#include "dosdef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FA_NORMAL 0x00
#define FA_RDONLY 0x01
#define FA_HIDDEN 0x02
#define FA_SYSTEM 0x04
#define FA_LABEL 0x08
#define FA_DIREC 0x10
#define FA_ARCH 0x20

unsigned _dos_getfileattr(const char *filename, unsigned *attrib);
unsigned _dos_setfileattr(const char *filename, unsigned attrib);

void delay(int ms);

#ifdef __cplusplus
}
#endif
