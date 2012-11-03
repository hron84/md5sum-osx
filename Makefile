CC = gcc
CFLAGS = -arch i386 -arch x86_64 -Wall -pedantic -O0 -g -ggdb -gdwarf-2 -pipe
LDFLAGS = $(CFLAGS)

UNAME := $(shell uname)

MD5_SOURCES = md5sum.c md5.c util.c
MD5_OBJECTS = ${MD5_SOURCES:.c=.o}
MD5_LIBS = -lcrypto


SHA256_SOURCES = sha256sum.c sha256.c util.c
SHA256_LIBS = -lcrypto

ifeq ($(UNAME),Darwin)
CFLAGS += -I.
SHA256_SOURCES += external/sha2.c
SHA256_LIBS =
endif

SHA256_OBJECTS = ${SHA256_SOURCES:.c=.o}


all: md5sum sha256sum

clean:
	-rm -f *.o md5sum sha256sum external/*.o

tests:
	sh test/test.sh

md5sum: $(MD5_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(MD5_OBJECTS) $(MD5_LIBS)

sha256sum: $(SHA256_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $(SHA256_OBJECTS) $(SHA256_LIBS)

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<
