YFLAGS = -dv

SUPPORT = \
	e/crashhandler.e \
	e/dynallhandler.e \
	e/save.e \
	e/copy.e \
	e/errorhandler.e \
	e/filehandler.e \
	e/garbage.e \
	e/graphgenerator.e \
	e/inspect.e \
	e/lambda_lexan.e \
	e/lambda_parser.e \
	e/listinghandler.e \
	e/loader.e \
	e/m_stack.e \
	e/menu.e \
	e/numberhandler.e \
	destroyer.c \
	e/readback.e \
	e/reducer.e \
	e/scope_analysis.e \
	e/sthandler.e \
	e/stringhandler.e \
	h/const.h \
	h/crashmsgs.h \
	h/errormsgs.h \
	h/iolibrary.h \
	h/keywords.h \
	h/types.h \
	y.tab.h \
	Makefile

SRC = \
	copy.c \
	destroyer.c \
	save.c \
	readback.c \
	garbage.c \
	loader.c \
	reducer.c \
	m_stack.c \
	scope_analysis.c \
	graphgenerator.c \
	main.c \
	sthandler.c \
	menu.c \
	inspect.c \
	crashhandler.c \
	errorhandler.c \
	numberhandler.c \
	dynallhandler.c \
	filehandler.c \
	stringhandler.c

YLSRC = $(SRC) \
	lambda_parser.y \
	lambda_lexan.l

GENSRC = $(SRC) \
	lambda_parser.c \
	lambda_lexan.c

OBJS = \
	lib.a(lambda_parser.o) \
	lib.a(lambda_lexan.o) \
	lib.a(main.o) \
	lib.a(copy.o) \
	lib.a(sthandler.o) \
	lib.a(scope_analysis.o) \
	lib.a(inspect.o) \
	lib.a(graphgenerator.o) \
	lib.a(destroyer.o) \
	lib.a(loader.o) \
	lib.a(reducer.o) \
	lib.a(m_stack.o) \
	lib.a(readback.o) \
	lib.a(garbage.o) \
	lib.a(menu.o) \
	lib.a(save.o) \
	lib.a(crashhandler.o) \
	lib.a(errorhandler.o) \
	lib.a(numberhandler.o) \
	lib.a(dynallhandler.o) \
	lib.a(filehandler.o) \
	lib.a(stringhandler.o)

all: opt

debug:
	$(MAKE) CFLAGS="-g -Wall -Werror"

opt: lib.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ lib.a -ll -ly

lib.a: $(OBJS)

$(OBJS): $(SUPPORT)

y.tab.h: lambda_parser.c

# lint the whole code.  Expect a lot of warnings!
lint: $(GENSRC)
	$(LINT.c) $(GENSRC)

# rebuild the TAGS file for emacs
etags: 
	etags $(YLSRC)

# rebuild the tags file for vi
ctags: 
	ctags $(YLSRC)

clean:
	-rm -f opt lib.a *.o
	-rm -f lambda_parser.c lambda_lexan.c y.*
	-rm -f TAGS tags
