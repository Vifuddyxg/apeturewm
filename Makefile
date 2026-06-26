PREFIX       ?= /usr/local
BINDIR       ?= $(PREFIX)/bin
XSESSIONSDIR ?= /usr/share/xsessions

CC       ?= cc
CPPFLAGS ?=
CFLAGS   ?= -Os -std=c99 -Wall -Wextra -pedantic
LDFLAGS  ?=
LDLIBS   ?= -lX11 -lXinerama -lXrandr -lXcomposite -lXrender

BIN      = apeturewm
SRC      = apeturewm.c

all: $(BIN)

$(BIN): $(SRC) config.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(BIN) $(SRC) $(LDFLAGS) $(LDLIBS)

install: $(BIN)
	mkdir -p $(DESTDIR)$(BINDIR)
	install -m 755 $(BIN) $(DESTDIR)$(BINDIR)/$(BIN)
	install -m 755 apeturewm-session $(DESTDIR)$(BINDIR)/apeturewm-session
	mkdir -p $(DESTDIR)$(XSESSIONSDIR)
	install -m 644 apeturewm.desktop $(DESTDIR)$(XSESSIONSDIR)/apeturewm.desktop

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(BIN)
	rm -f $(DESTDIR)$(BINDIR)/apeturewm-session
	rm -f $(DESTDIR)$(XSESSIONSDIR)/apeturewm.desktop

clean:
	rm -f $(BIN)

.PHONY: all install uninstall clean
