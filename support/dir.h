#ifdef __cplusplus
extern "C" {
#endif

#define MAXPATH 260
#define MAXDRIVE 3
#define MAXDIR 256
#define MAXFILE 256
#define MAXEXT 256

int  _dos_setftime(int fd, int date, int time);
void fnsplit(const char *pathname, char *drive, char *dir, char *name, char *ext);
void fnmerge(char *pathname, const char *drive, const char *dir, const char *name, const char *ext);

struct ffblk {
    char ff_reserved[MAXFILE+MAXEXT-1];
    char ff_attrib;
    unsigned ff_ftime;
    unsigned ff_fdate;
    long ff_fsize;
    char ff_name[MAXFILE+MAXEXT-1];
};

int findfirst(const char *path, struct ffblk *ffblk, int attrib);
int findnext(struct ffblk *ffblk);

#define mkdir(a) mkdir(a, 0777)
char *searchpath(const char *file);

#ifdef __cplusplus
}
#endif
