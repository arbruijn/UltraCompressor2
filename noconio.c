#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "conio.h"

void clreol(void) {}
void clrscr(void) {}
void gotoxy(int x, int y) {}
void highvideo(void) {}
void lowvideo(void) {}
void normvideo(void) {}
void textattr(int a) {}
void textbackground(int c) {}
void textcolor(int c) {}
void textmode(int m) {}
int wherex(void) { return 0; }
int wherey(void) { return 0; }
void window(int left, int top, int right, int bottom) {}
int putch(int c) { return putchar(c); }
int cputs(const char *str) { return puts(str); }
int cprintf(const char *format, ...) {
  int ret;
  va_list va; va_start(va, format); ret = vprintf(format, va); va_end(va);
  return ret;
}
void delline(void) {}
void insline(void) {}
int kbhit() {
  fd_set rd;
  struct timeval timeout;
  timeout.tv_sec = timeout.tv_usec = 0;
  FD_ZERO(&rd);
  FD_SET(0, &rd);
  return select(1, &rd, NULL, NULL, &timeout) == 1 ? 1 : 0;
}
int getch() {
  return getchar();
}
void gettextinfo(struct text_info *ti) {
  memset(ti, 0, sizeof(*ti));
}
int directvideo;
