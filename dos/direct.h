#ifdef __cplusplus
extern "C" {
#endif
int getdisk(void);
int setdisk(int drive);
int _getdcwd(int drive, char *path, int size);
#ifdef __cplusplus
}
#endif

