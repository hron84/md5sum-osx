#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <openssl/md5.h>

#include "md5.h"

#define BUFSIZE 4096

char *md5sum(const char *fileName) {
    MD5_CTX ctx;
    unsigned char *result = malloc(MD5_DIGEST_LENGTH);
    char *hexresult;
    unsigned char *buf = malloc(BUFSIZE);
    char hbuf[3];
    int fd;
    int rbytes = 0;
    int i;
    
    memset(result   , 0, MD5_DIGEST_LENGTH);
        
    memset(buf      , 0, BUFSIZE);
    
    MD5_Init(&ctx);
    
	if(!strncmp("-", fileName, 1) || !strncmp("/dev/stdin", fileName, 10)) {
		fd = STDIN_FILENO;
	} else {
	    fd = open(fileName, O_RDONLY);
    
		if(fd < 0) {
	        if(errno == 2) {
	            fprintf(stderr, "ERROR: %s: File not found\n", fileName);
	        } else {
	            fprintf(stderr, "ERROR: Unexpected error happened: %s(%d)\n", strerror(errno), errno);
	        }
	        free(result);
	        return NULL;
	    }
	}
    
    while( (rbytes = read(fd, buf, BUFSIZE) ) > 0) {
        MD5_Update(&ctx, buf, rbytes);
        memset(buf   , 0, BUFSIZE);
    }
    
    MD5_Final(result, &ctx);
    
    hexresult = malloc(2*MD5_DIGEST_LENGTH +1);
    memset(hexresult, 0, 2*MD5_DIGEST_LENGTH+1);
    
    for(i = 0; i < MD5_DIGEST_LENGTH; i++) {
        /*fprintf(stderr, "DEBUG: h: %02x\n", result[i]);*/
        snprintf(hbuf, 3, "%02x", result[i]);
        /*fprintf(stderr, "DEBUG: hbuf: %s\n", hbuf);*/
        strncat(hexresult, hbuf, 2);
    }

    free(result);
    free(buf);
    return hexresult;
}
