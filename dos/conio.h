#ifndef CONIO_H_
#define CONIO_H_

#ifdef __cplusplus
extern "C" {
#endif

void clreol(void);
void clrscr(void);
void gotoxy(int x, int y);
void highvideo(void);
void lowvideo(void);
void normvideo(void);
void textattr(int a);
void textbackground(int c);
void textcolor(int c);
void textmode(int m);
int wherex(void);
int wherey(void);
void window(int left, int top, int right, int bottom);
int putch(int c);
int cputs(const char *str);
int cprintf(const char *format, ...);
void delline(void);
void insline(void);
int kbhit();
int getch();

struct text_info { int attribute, screenwidth, screenheight, currmode; };
void gettextinfo(struct text_info *);

enum COLORS {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA,
    YELLOW, WHITE
};

#define BLINK       128

extern int directvideo;

enum text_modes { LASTMODE=-1, BW40=0, C40, BW80, C80, MONO=7, C4350=64 };

#ifdef __cplusplus
}
#endif

#endif
