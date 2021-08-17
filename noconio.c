#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#ifdef STDIN_FILENO
#include <termios.h>
#endif
#include "conio.h"
typedef unsigned char BYTE;
#include "video.h"

void clreol(void) {}
void clrscr(void) {} // printf("\x1b[2J\x1b[H"); }
void gotoxy(int x, int y) {}
void highvideo(void) {}
void lowvideo(void) {}
void normvideo(void) {}
void textbackground(int c) {}
void textcolor(int c) {
  if (c == 14) {
    printf("\x1b[0;38;5;172m");
    return;
  }
  int nc = (c & 2) | ((c & 1) << 2) | ((c & 4) >> 2);
  printf("\x1b[0;%dm", c == 7 ? 0 : 30 + nc);
}
void textattr(int a) { textcolor(a & 15); }
void textmode(int m) {}
int wherex(void) { return 1; }
int wherey(void) { return 1; }
void window(int left, int top, int right, int bottom) {}
int putch(int c) { return putchar(c); }
int cputs(const char *str) { return fputs(str, stdout); }
int cprintf(const char *format, ...) {
  int ret;
  va_list va; va_start(va, format); ret = vprintf(format, va); va_end(va);
  return ret;
}
void delline(void) {}
void insline(void) {}
struct termios input_saved;
static void done_input() {
  tcsetattr(STDIN_FILENO, TCSANOW, &input_saved);
}
static void init_input() {
  static int inited = 0;
  if (inited)
    return;
  inited = 1;
  setbuf(stdin, NULL);
#ifdef STDIN_FILENO
  if (!isatty(STDIN_FILENO))
    return;
  tcgetattr(STDIN_FILENO, &input_saved);
  struct termios tattr = input_saved;
  tcgetattr(STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON|ECHO);
  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
  atexit(done_input);
#endif
}
int kbhit() {
  fd_set rd;
  struct timeval timeout;
  init_input();
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  FD_ZERO(&rd);
  FD_SET(0, &rd);
  return select(1, &rd, NULL, NULL, &timeout) == 1 ? 1 : 0;
}
int getch() {
  init_input();
  fflush(stdout);
  int c = getchar();
  if (c == 27 && kbhit()) {
    while (kbhit())
      c = getchar();
    switch (c) {
      case 'A': return KEY_UP;
      case 'B': return KEY_DOWN;
      case 'C': return KEY_RIGHT;
      case 'D': return KEY_LEFT;
    }
    c = 255;
  }
  if (c == 10) c = 13;
  return c;
}
void gettextinfo(struct text_info *ti) {
  memset(ti, 0, sizeof(*ti));
  ti->attribute = 7;
  ti->screenwidth = 80;
  ti->screenheight = 24;
}
int directvideo;
