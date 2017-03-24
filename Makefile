CC = gcc
LDFLAGS =
CFLAGS = -Wall -Ofast -fstrict-aliasing -march=native
OBJECTS = lighterfluid.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

lighterfluid: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
	@chmod 755 $@
	@chmod u+s $@
	

debug:	CFLAGS= -Wall -O0 -g  -fstrict-aliasing -march=native
debug: 	$(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o lighterfluid-$@ $(LDFLAGS)


clean:
	@echo cleaning oop
	@rm -f $(OBJECTS)
purge:
	@echo purging oop
	@rm -f $(OBJECTS)
	@rm -f lighterfluid
	@rm -f lighterfluid-debug
install:
	@echo installing to /usr/bin
	@cp lighterfluid /usr/bin/lighterfluid
	@chmod 755 /usr/bin/lighterfluid
	@chmod u+s /usr/bin/lighterfluid
uninstall:
	@echo uninstalling
	@rm -f /usr/bin/lighterfluid
