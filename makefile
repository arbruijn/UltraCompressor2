#	ofletch.cpp 

SRC = archio.cpp \
	bitio.cpp \
	comoterp.cpp \
	compint.cpp \
	comp_tt.cpp \
	contains.cpp \
	convert.cpp \
	dampro.cpp \
	delta.cpp \
	dirman.cpp \
	diverse.cpp \
	exit.cpp \
	fletch.cpp \
	handle.cpp \
	list.cpp \
	llio.cpp \
	main.cpp \
	mem.cpp \
	menu.cpp \
	neuroman.cpp \
	superman.cpp \
	tagman.cpp \
	test.cpp \
	treeenc.cpp \
	treegen.cpp \
	ultracmp.cpp \
	version.cpp \
	video.cpp \
	views.cpp \
	vmem.cpp \
	vol.cpp \
	xorblock.cpp \
	nospawn.cpp \
	nuke.cpp \
	factor.c

OBJ = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRC)))
#INCLUDE = $(HOME)/binwin/ow2/h
#export INCLUDE

COMFLAGS += -ggdb -pedantic
#COMFLAGS += -m32
CC = clang
CXX = clang++
#COMFLAGS += -fsanitize=address
COMFLAGS += -fsanitize=undefined

CXXFLAGS += $(COMFLAGS) -I dos -I . -Wno-write-strings
# -DUE2
CFLAGS += $(COMFLAGS) -I dos
#CFLAGS += -m32 -I tc -I . -Wno-write-strings -Dfar=""
LDFLAGS += $(COMFLAGS)
#LDLIBS += -lncurses

TCSRC = tc/rest.c \
tc/setdisk.c \
tc/getdisk.c \
tc/ctype.c \
tc/delay.c \
tc/dos2unix.c \
tc/endian.c \
tc/endianFile.c \
tc/findfirst.c \
tc/freeTurbo.c \
tc/getdateSystem.c \
tc/getftime.c \
tc/gettime.c \
tc/random.c \
tc/strlwr.c \
tc/strupr.c \
tc/TurboCVariables.c \
tc/TurboTrap.c \
tc/TurboX.c

TCCON = \
tc/getche.c \
tc/getchTurbo.c \
tc/ResizeTurboC.c \
tc/putch.c \
tc/delline.c \
tc/movetext.c \
tc/normvideo.c \
tc/cgets.c \
tc/clreol.c \
tc/clrscr.c \
tc/ConioResizeCallback.c \
tc/cprintf.c \
tc/cputs.c \
tc/gotoxy.c \
tc/insline.c \
tc/kbhit.c \
tc/wherex.c \
tc/wherey.c \
tc/window.c \
tc/highvideo.c \
tc/lowvideo.c \
tc/textattr.c \
tc/textbackground.c \
tc/textcolor.c \
tc/textmode.c

#TCSRC += $(TCCON)
TCSRC += noconio.c

TCGR = \
tc/XXXaspectratio.c \
tc/textwidth.c \
tc/arc.c \
tc/bar.c \
tc/circle.c \
tc/clearXXXX.c \
tc/closegraph.c \
tc/outtextxy.c \
tc/putpixel.c \
tc/puttext.c \
tc/rectangle.c \
tc/registerbgidriver.c \
tc/registerbgifont.c \
tc/sector.c \
tc/setbkcolor.c \
tc/setcolor.c \
tc/_setcursortype.c \
tc/setfillXXXX.c \
tc/setgraphbufsize.c \
tc/setlinestyle.c \
tc/setpalette.c \
tc/setrgbpalette.c \
tc/settextstyle.c \
tc/setviewport.c \
tc/setwritemode.c \
tc/setXXXXpage.c \
tc/getpixel.c \
tc/gettext.c \
tc/gettextinfo.c \
tc/gettextsettings.c \
tc/getviewsettings.c \
tc/graphdefaults.c \
tc/grapherrormsg.c \
tc/graphresult.c \
tc/_graphXXXmem.c \
tc/initgraph.c \
tc/line.c \
tc/pieslice.c \
tc/detectgraph.c \
tc/drawpoly.c \
tc/ellipse.c \
tc/fillellipse.c \
tc/getarccoords.c \
tc/getdrivername.c \
tc/getgraphmode.c \
tc/getimage.c \
tc/getmaxcolor.c \
tc/getmaxmode.c \
tc/getmaxx.c \
tc/getmodename.c \
tc/getmoderange.c \
tc/getpalette.c \
tc/installuserdriver.c \
tc/installuserfont.c

TCSRC = noconio.c dosfuns.c
TCOBJ = $(patsubst %.c,%.o,$(TCSRC))

all: uc

uc: $(OBJ) $(TCOBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

#%.obj: %.cpp
#	~/binwin/ow2/binl/wpp386 -I=. $<

clean:
	rm -f *.o tc/*.o

superbin.c: super.bin
	xxd -i $< > $@

