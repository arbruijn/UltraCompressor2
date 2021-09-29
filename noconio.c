#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>
#ifdef STDIN_FILENO
#include <termios.h>
#endif
#include "conio.h"
typedef unsigned char BYTE;
#include "video.h"

static struct text_info ti = { 7, 80, 24 };
static int wintop, winbottom;

static void done_output() {
	if (wintop > 1)
		printf("\x1b[r\x1b[%d;%dH", ti.cury, ti.curx);
	if (ti.attribute != 7)
		printf("\x1b[m");
}

static void upd_win_size() {
#ifdef TIOCGSIZE
	struct ttysize ts;
	ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
	ti.screenwidth = ts.ts_cols;
	ti.screenheight = ts.ts_lines;
#elif defined(TIOCGWINSZ)
	struct winsize ts;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
	ti.screenwidth = ts.ws_col;
	ti.screenheight = ts.ws_row;
#endif
}

static int output_inited;
static void init_output() {
	if (output_inited)
		return;
	output_inited = 1;
	signal(SIGWINCH, upd_win_size);
	upd_win_size();
	atexit(done_output);
}

void clreol(void) { printf("\x1b[K"); }
void clrscr(void) {
	printf("\x1b[2J");
	gotoxy(1, 1);
}
void gotoxy(int x, int y) {
	printf(x == 1 && y == 1 ? "\x1b[H" : "\x1b[%d;%dH", y, x);
	ti.curx = x;
	ti.cury = y;
}
void highvideo(void) {
	textattr(ti.attribute | 8);
}
void lowvideo(void) {
	textattr(ti.attribute & ~8);
}
void normvideo(void) {
	textattr(7);
}
void textbackground(int c) {
	textattr(((c & 0xf) << 4) | (ti.attribute & 0xf));
}
void textcolor(int c) {
	textattr((ti.attribute & 0xf0) | (c & 0xf));
}
static int xlatcolor(int c) {
	return (c & 2) | ((c & 1) << 2) | ((c & 4) >> 2);
}
void textattr(int a) {
	char buf[64];
	if (a == ti.attribute)
		return;
	int cur = ti.attribute;
	ti.attribute = a;
	if (a == 7) {
		printf("\x1b[m");
		return;
	}
	strcpy(buf, "\x1b[");
	if (!(a & 8) && (cur & 8)) {
		strcat(buf, "0;");
		cur = 7;
	}
	if ((a ^ cur) & 0x70) {
		if (!(a & 0xf0)) {
			strcat(buf, "0;");
			cur = 7;
		} else
			sprintf(buf + strlen(buf), "%d;", 40 + xlatcolor((a & 0x70) >> 4));
	}
	if ((a & 0xf) == 14 && (cur & 0xf) != 14) {
	    strcat(buf, "38;5;172;");
	} else {
		if ((a & 8) && (!(cur & 8) || ((cur & 0xf) == 14)))
			strcat(buf, "1;");
		if ((a ^ cur) & 0x7) {
			sprintf(buf + strlen(buf), "%d;", 30 + xlatcolor(a & 7));
		}
	}
	buf[strlen(buf) - 1] = 'm';
	fputs(buf, stdout);
}
void textmode(int m) {}
int wherex(void) { return ti.curx; }
int wherey(void) { return ti.cury; }
void window(int left, int top, int right, int bottom) {
	printf("\x1b[%d;%dr", top, bottom);
	wintop = top;
	winbottom = bottom;
}
int putch(int c) {
	init_output();
	if (c == 24)
		fputs("\xe2\x86\x91", stdout);
	else if (c == 25)
		fputs("\xe2\x86\x93", stdout);
	else
		putchar(c);
	switch (c) {
		case 13:
			ti.curx = 1;
			break;
		case 10:
			if (ti.cury < ti.screenheight)
				ti.cury++;
			break;
		case 7:
		case 127:
			break;
		case 8:
			if (ti.curx > 1)
				ti.curx--;
			break;
		default:
			if (ti.curx < ti.screenwidth) {
				ti.curx++;
			} else {
				ti.curx = 1;
				if (ti.cury < ti.screenheight)
					ti.cury++;
			}
	}
	return c;
}
int cputs(const char *str) {
	char c;
	int n;
	while ((c = *str++)) {
		putch(c);
		n++;
	}
	return n;
}
int cprintf(const char *format, ...) {
  int ret;
  char buf[1024];
  va_list va;
  va_start(va, format);
  vsnprintf(buf, sizeof(buf), format, va);
  va_end(va);
  return cputs(buf);
}
void delline(void) { printf("\x1b[%dH\n\x1b[%dH", winbottom, ti.cury); }
void insline(void) { printf("\x1b[%dH\x1b""M\x1b[%dH", wintop, ti.cury); }
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
    int n = 0;
    while (kbhit()) {
      c = getchar();
      if (c >= '0' && c <= '9')
        n = n * 10 + (c - '0');
    }
    switch (c) {
      case 'A': return KEY_UP;
      case 'B': return KEY_DOWN;
      case 'C': return KEY_RIGHT;
      case 'D': return KEY_LEFT;
      case 'H': return KEY_HOME;
      case 'F': return KEY_END;
      case '~':
        switch (n) {
          case 5: return KEY_PUP;
          case 6: return KEY_PDOWN;
        }
    }
    c = 255;
  }
  if (c == 10) c = 13;
  return c;
}
void gettextinfo(struct text_info *pti) {
	init_output();
	*pti = ti;
}
int directvideo;
