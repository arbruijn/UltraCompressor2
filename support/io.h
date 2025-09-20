#ifndef IO_H_
#define IO_H_

#include "dosdef.h"

#ifdef __cplusplus
extern "C" {
#endif

#define pipe unixpipe
#include <unistd.h>
#undef pipe

#define _read read
#define _write write
#define _open open
#define chsize ftruncate
#define tell(fd) lseek(fd,0,SEEK_CUR)
#define O_BINARY 0
inline int _chmod(const char *path, int b, ...) { return 0; }
long filelength(int fd);

#define SH_DENYWR 0
#define SH_DENYRW 0

struct ftime {
    unsigned ft_tsec  : 5;
    unsigned ft_min   : 6;
    unsigned ft_hour  : 5;
    unsigned ft_day   : 5;
    unsigned ft_month : 4;
    unsigned ft_year  : 7;
};

#ifdef __cplusplus
}
#endif

#endif
