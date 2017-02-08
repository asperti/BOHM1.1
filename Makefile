YFLAGS = -dv

OBJS = \
	bohm.a(parser.o) \
	bohm.a(lexer.o) \
	bohm.a(main.o) \
	bohm.a(copy.o) \
	bohm.a(symbol.o) \
	bohm.a(inspect.o) \
	bohm.a(graph.o) \
	bohm.a(destroy.o) \
	bohm.a(loader.o) \
	bohm.a(reducer.o) \
	bohm.a(stack.o) \
	bohm.a(readback.o) \
	bohm.a(garbage.o) \
	bohm.a(menu.o) \
	bohm.a(save.o) \
	bohm.a(crash.o) \
	bohm.a(error.o) \
	bohm.a(dynall.o) \
	bohm.a(file.o) \
	bohm.a(string.o)

all: bohm
	./bohm <examples/tartaglia

debug: clean
	$(MAKE) CFLAGS="-g -Wall -Werror"

bohm: bohm.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< -ll -ly

bohm.a: $(OBJS)

$(OBJS): bohm.h y.tab.h

lexer.c: y.tab.h

y.tab.h: parser.c

clean:
	-rm -f bohm bohm.a *.o
	-rm -f parser.c lexer.c y.*
