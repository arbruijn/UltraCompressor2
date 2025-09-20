#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <fnmatch.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include "dos.h"
#include "dir.h"

void bdos() {}
void _chmod() {}
void chsize() {}
void ctrlbrk() {}
void dosexterr() {}
unsigned _dos_getfileattr(const char *filename, unsigned *attrib) { return 0; }
unsigned _dos_setfileattr(const char *path, unsigned attr) { return 0; }
long filelength(int fd) {
    off_t l, c;
    if ((c = lseek(fd,0,SEEK_CUR)) == -1)
        return -1;
    if ((l = lseek(fd,0,SEEK_END)) == -1)
        return -1;
    if (lseek(fd,c,SEEK_SET) == -1)
        return -1;
    return (long)l;
}
int flushall() { return 0; }

void fnsplit(const char *pathname, char *drive, char *dir, char *name, char *ext) {
    const char *p, *p1, *p2, *e;
    if (*pathname && pathname[1] == ':') {
        if (drive) {
            memcpy(drive, pathname, 2);
            drive[3] = 0;
        }
        pathname += 2;
    } else if (drive)
        *drive = 0;

    p1 = strrchr(pathname, '/');
    p2 = strrchr(pathname, '\\');
    if (p1 && p2)
        p = (p1 > p2 ? p1 : p2) + 1;
    else
        p = p1 ? p1 + 1 : p2 ? p2 + 1: pathname;

    if (dir) {
        memcpy(dir, pathname, p - pathname);
        dir[p - pathname] = 0;
    }

    if (!(e = strrchr(p, '.')) || e == p)
        e = pathname + strlen(pathname);

    if (name) {
        memcpy(name, p, e - p);
        name[e - p] = 0;
    }

    if (ext)
        strcpy(ext, e);
}
void fnmerge(char *pathname, const char *drive, const char *dir, const char *name, const char *ext) {
    if (drive && *drive) {
        strcpy(pathname, drive);
        pathname += strlen(pathname);
    }
    if (dir && *dir) {
        strcpy(pathname, dir);
        pathname += strlen(pathname);
    }
    if ((name && *name) || (ext && *ext)) {
        if (dir && *dir && pathname[-1] != '/' && pathname[-1] != '\\')
            *pathname++ = '/';
        strcpy(pathname, name);
        pathname += strlen(pathname);
        if (ext && *ext) {
            if (*ext != '.')
                *pathname++ = '.';
            strcpy(pathname, ext);
            pathname += strlen(ext);
        }
    }
    *pathname = 0;
}
int _getdcwd(int d, char *cwd, int len) { getcwd(cwd, len); return 0; }
void _harderr() {}
void _hardresume() {}
char *searchpath(const char *file) { return NULL; }
void setcbrk() {}
int xsystem(const char *cmd) { return system(cmd); }


char *strupr(char *s) {
    for (char *p = s; *p; p++)
        *p = toupper(*p);
    return s;
}

char *strlwr(char *s) {
    for (char *p = s; *p; p++)
        *p = tolower(*p);
    return s;
}

char **_argv;
int _argc;

void delay(int ms) {
    fflush(stdout);
    struct timeval tv;
    tv.tv_sec = ms / 1000;
    tv.tv_usec = (ms % 1000) * 1000;
    select(0, NULL, NULL, NULL, &tv);
}

int getdisk() { return 0; }
int setdisk(int d) { return 0; }

DIR *curdir = NULL;
char curdirpath[PATH_MAX];

static void mkdostime(time_t t, unsigned *date, unsigned *time) {
    struct tm *tm = localtime(&t);
    *date = ((tm->tm_year - 80) << 9) | ((tm->tm_mon + 1) << 5) | tm->tm_mday;
    *time = (tm->tm_hour << 11) | (tm->tm_min << 5) | (tm->tm_sec >> 1);
}

int  _dos_setftime(int fd, int date, int time) {
    struct tm tm;
    struct timeval tv[2];
    tm.tm_year = (date >> 9) + 80;
    tm.tm_mon = ((date >> 5) & 15) - 1;
    tm.tm_mday = date & 31;
    tm.tm_hour = time >> 11;
    tm.tm_min = (time >> 5) & 63;
    tm.tm_sec = (time & 31) << 1;
    tm.tm_isdst = -1;
    tv[0].tv_sec = tv[1].tv_sec = mktime(&tm);
    tv[0].tv_usec = tv[1].tv_usec = 0;
    return futimes(fd, tv);
}

static int findfill(struct ffblk *ffblk, const char *name, struct stat *st) {
    if (strlen(name) >= sizeof(ffblk->ff_name))
        return 1;
    strcpy(ffblk->ff_name, name);
    ffblk->ff_fsize = st->st_size;
    ffblk->ff_attrib = S_ISDIR(st->st_mode) ? FA_DIREC : FA_ARCH;
    mkdostime(st->st_mtime, &ffblk->ff_fdate, &ffblk->ff_ftime);
    return 0;
}

int findfirst(const char *path, struct ffblk *ffblk, int attr) {
    const char *p;
    if (!(p = (const char *)strrchr(path, '/'))) {
        strcpy(curdirpath, ".");
        p = path;
    } else {
        if (snprintf(curdirpath, sizeof(curdirpath), "%.*s", (int)(p - path), path) >= sizeof(curdirpath))
            return 1;
        p++;
    }

    struct stat st;
    if (!strchr(p, '?') && !strchr(p, '*')) {
        ffblk->ff_reserved[0] = 0;
        if (stat(path, &st))
            return 1;
        return findfill(ffblk, p, &st);
    }

    if (snprintf(ffblk->ff_reserved, sizeof(ffblk->ff_reserved), "%s", p) >= sizeof(ffblk->ff_reserved))
        return 1;
    if (curdir)
        closedir(curdir);
    if (!(curdir = opendir(curdirpath)))
        return 1;
    return findnext(ffblk);
}
int findnext(struct ffblk *ffblk) {
    struct dirent *ent;
    char path[PATH_MAX];
    struct stat st;
    if (!ffblk->ff_reserved[0] || !curdir)
        return 1;
    for (;;) {
        if (!(ent = readdir(curdir))) {
            closedir(curdir);
            curdir = NULL;
            return 1;
        }
        int m = fnmatch(ffblk->ff_reserved, ent->d_name, 0);
        if (m == FNM_NOMATCH)
            continue;
        if (m)
            return 1;
        if (snprintf(path, sizeof(path), "%s/%s", curdirpath, ent->d_name) >= sizeof(path))
            return 1;
        if (stat(path, &st))
            return 1;
        return findfill(ffblk, ent->d_name, &st);
    }
}

void *farmalloc(int s) {
    return malloc(s);
}

void farfree(void *p) {
    free(p);
}
