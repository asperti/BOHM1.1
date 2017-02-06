YFLAGS = -dv

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
	bohm.a(lambda_parser.o) \
	bohm.a(lambda_lexan.o) \
	bohm.a(main.o) \
	bohm.a(copy.o) \
	bohm.a(sthandler.o) \
	bohm.a(scope_analysis.o) \
	bohm.a(inspect.o) \
	bohm.a(graphgenerator.o) \
	bohm.a(destroyer.o) \
	bohm.a(loader.o) \
	bohm.a(reducer.o) \
	bohm.a(m_stack.o) \
	bohm.a(readback.o) \
	bohm.a(garbage.o) \
	bohm.a(menu.o) \
	bohm.a(save.o) \
	bohm.a(crashhandler.o) \
	bohm.a(errorhandler.o) \
	bohm.a(numberhandler.o) \
	bohm.a(dynallhandler.o) \
	bohm.a(filehandler.o) \
	bohm.a(stringhandler.o)

all: bohm

debug:
	$(MAKE) CFLAGS="-g -Wall -Werror"

bohm: bohm.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ bohm.a -ll -ly

bohm.a: $(OBJS)

$(OBJS): y.tab.h

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
	-rm -f bohm bohm.a *.o
	-rm -f lambda_parser.c lambda_lexan.c y.*
	-rm -f TAGS tags
