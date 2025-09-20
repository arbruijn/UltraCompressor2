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
	nuke.cpp \
	factor.c

OBJ = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SRC)))

COMFLAGS += -ggdb -pedantic
#CC = clang
#CXX = clang++
#COMFLAGS += -fsanitize=address
#COMFLAGS += -fsanitize=undefined
#COMFLAGS += -fsanitize=memory
COMFLAGS += -O3

CXXFLAGS += $(COMFLAGS) -I support -I . -I .. -Wno-write-strings
CFLAGS += $(COMFLAGS) -I support -I . -I ..
LDFLAGS += $(COMFLAGS)

SUPPORTSRC = support/termconio.c support/dosfuns.c support/spawnvars.c
SUPPORTOBJ = $(patsubst %.c,%.o,$(SUPPORTSRC))

all: uc

uc: $(OBJ) $(SUPPORTOBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -f *.o support/*.o

superbin.c: super.bin
	xxd -i $< > $@
