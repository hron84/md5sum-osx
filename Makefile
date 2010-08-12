CC = gcc
CFLAGS = -arch i386 -arch x86_64 -arch ppc -arch ppc64 -Wall -pedantic -O2 -g -ggdb -pipe
LIBS = -lcrypto
LDFLAGS = $(CFLAGS)

SOURCES = md5sum.c md5.c
OBJECTS = ${SOURCES:.c=.o}

all: md5sum

clean:
	-rm -f *.o md5sum

md5sum: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<
