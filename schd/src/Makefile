
#PREFIX ?= /usr
SBINDIR ?= $(PREFIX)/sbin
CFLAGS += -I.  -fPIC
NLLIBNAME = libubus
LIBS += -lubus -lubox
LIBS += $(shell $(PKG_CONFIG) --libs $(NLLIBNAME))
CFLAGS += $(shell $(PKG_CONFIG) --cflags $(NLLIBNAME))
OBJS = ubus.o schd.o signal.o service.o
all: schd


%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<
	
schd: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o schd

install:
#	install -D schd $(TARGET)/sbin/schd
#	$(STRIP) $(TARGET)/bin/schd
	$(MKDIR) $(DESTDIR)$(SBINDIR)
	$(INSTALL) -m 0755 schd $(DESTDIR)$(SBINDIR)
	
.PHONY: clean install

clean:
	rm  -rf *.o  schd
