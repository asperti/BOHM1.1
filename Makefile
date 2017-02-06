# makefile for BOHM

CFLAGS = -O 
#CFLAGS = -g
LDLIBS = -ll -ly
YFLAGS = -d

# No user serviceable parts below this line

# each time one of the following is modified, everything is recompiled
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
	utility/crashhandler.c \
	utility/errorhandler.c \
	utility/numberhandler.c \
	utility/dynallhandler.c \
	utility/filehandler.c \
	utility/stringhandler.c

YLSRC = $(SRC) \
	lambda_parser.y \
	lambda_lexan.l

GENSRC = $(SRC) \
	y.tab.c \
	lex.yy.c

OBJS = \
	main.o \
	y.tab.o \
	lex.yy.o \
	copy.o \
	sthandler.o \
	scope_analysis.o \
	inspect.o \
	graphgenerator.o \
	destroyer.o \
	loader.o \
	reducer.o \
	m_stack.o \
	readback.o \
	garbage.o \
	menu.o \
	save.o \
	utility/crashhandler.o \
	utility/errorhandler.o \
	utility/numberhandler.o \
	utility/dynallhandler.o \
	utility/filehandler.o \
	utility/stringhandler.o

opt: $(OBJS) $(SUPPORT)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) \
	-o opt $(LDLIBS)

# The two following productions are identical
y.tab.c: lambda_parser.y
	$(YACC) $(YFLAGS) lambda_parser.y

y.tab.h: lambda_parser.y
	$(YACC) $(YFLAGS) lambda_parser.y

lex.yy.c: lambda_lexan.l y.tab.h
	$(LEX) $(LFLAGS) lambda_lexan.l

# the default .c.o rule puts its object in the wrong directory
.c.o:
	$(COMPILE.c) -o $@ $<

copy.o: copy.c $(SUPPORT)

destroyer.o: destroyer.c $(SUPPORT)

garbage.o: garbage.c $(SUPPORT)

graphgenerator.o: graphgenerator.c $(SUPPORT)

inspect.o: inspect.c $(SUPPORT)

lex.yy.o: lex.yy.c $(SUPPORT) y.tab.h

loader.o: loader.c $(SUPPORT)

m_stack.o: m_stack.c $(SUPPORT)

main.o: main.c $(SUPPORT)

menu.o: menu.c $(SUPPORT)

#rback.o: rback.c $(SUPPORT)

readback.o: readback.c $(SUPPORT)

reducer.o: reducer.c $(SUPPORT)

save.o: save.c $(SUPPORT)

scope_analysis.o: scope_analysis.c $(SUPPORT)

sthandler.o: sthandler.c $(SUPPORT) y.tab.h

y.tab.o: y.tab.c $(SUPPORT)

utility/crashhandler.o: utility/crashhandler.c $(SUPPORT)

utility/dynallhandler.o: utility/dynallhandler.c $(SUPPORT)

utility/errorhandler.o: utility/errorhandler.c $(SUPPORT)

utility/filehandler.o: utility/filehandler.c $(SUPPORT)

utility/numberhandler.o: utility/numberhandler.c $(SUPPORT)

utility/stringhandler.o: utility/stringhandler.c $(SUPPORT)

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
	-rm -f y.tab.h y.tab.c lex.yy.c
	-rm -f opt *.o utility/*.o
	-rm -f TAGS tags
