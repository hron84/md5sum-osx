#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "sha512.h"
#include "util.h"
#include "version.h"

#define PROGRAM_NAME "sha512sum"

int printSHA512(const char *fileName) {
    char *sha512 = sha512sum(fileName);
    if(sha512) {
        printf("%s  %s\n", sha512, fileName);
        return 1;
    } else {
        return 0;
    }
}

int checkSHA512(const char *sumFile) {
    FILE *fp;
    char line[1024];
    char *sha512, *storedSHA512;
    char *file = malloc(FILENAME_MAX), *filebuf = file;
    char *b;
    
    int fileok = 0, fileerr = 0, filetotal = 0, lineno = 0;
    
    if(!strncmp("-", sumFile, 1) || !strncmp("/dev/stdin", sumFile, 10)) {
		fp = stdin;
	} else {
		fp = fopen(sumFile, "r");
	}

    if(!fp) {
        fprintf(stderr, "ERROR: Cannot open sumfile: %s(%d)\n", strerror(errno), errno);
        free(filebuf);
        return 1;
    }
    
    /*fprintf(stderr, "DEBUG: Entering to reading file...\n");*/
    while(fgets(line, 1024, fp)) {
        /*fprintf(stderr, "DEBUG: line='%s'\n", line);*/
        lineno++;
        storedSHA512 = strtok(line, " ");
        if(storedSHA512 == NULL) {
            /* Maybe an empty line given */
            continue;
        }
        if(!strncmp("#", storedSHA512, 1)) {
            continue;
        }

        memset(file, 0, FILENAME_MAX);
        
        while((b = strtok(NULL, " ")) != NULL) {            
            strncat(file, " ", 2);
            strncat(file, b, strlen(b) + 1);
        }
        
        /* We remove space and asterisk from beginning of string */
        ltrim(&file, ' ');
        ltrim(&file, '*');
        
        chomp(file);
        
        if(!file || strlen(file) < 1) {
            fprintf(stderr, "WARNING: invalid formatted line given at %s:%d\n", sumFile, lineno);
            fprintf(stderr, "WARNING: but keep going...");
            continue;
        }
        
        chomp(storedSHA512);
        chop(storedSHA512, ' ');
        
        sha512 = sha512sum(file);
        filetotal++;
                
        if(!sha512 || strncmp(sha512, storedSHA512, 32)) {
            fileerr++;
            printf("%s: FAILED\n", file);
        } else {
            fileok++;
            printf("%s: OK\n", file);
        }
        free(sha512);
    }
    
    free(filebuf);
    
    if(fileerr > 0) {
        printf("WARNING: %d of %d did NOT match\n", fileerr, filetotal);
        return 1;
    } else {
        return 0;
    }
}

void printBanner() {
    printf("%s for OS X %s\n", PROGRAM_NAME, PROGRAM_VERSION);
    printf("Copyright (c) 2010-2012 Gabor Garami. Some rights reserved.\n");
}

void printUsage() {
    printBanner();
    printf("\n");
    printf("Usage: %s file1 file2\n", PROGRAM_NAME);
    printf("       %s -c sumfile\n", PROGRAM_NAME);
}
 

int main(int argc, char **argv) {
    int i, ret;
    const char *fileName;
    const char *sumFile;
	int got_stdin = 0;
    
    struct stat x; /* Not really used */    
    
    if(argc < 2 || !strncmp("--help", argv[1], 6)) {
        printUsage();
        return 1;
    }
    
    if(!strncmp("-v", argv[1], 2) || !strncmp("--version", argv[1], 9)) {
        printBanner();
        return 0;
    }
    
    if(!strncmp("-c", argv[1], 2)) {
        sumFile = argv[2];
        argc -= 2;
        argv +=2;
        ret = checkSHA512(sumFile);
    
    } else {
        for(i = 1; i < argc; i++) {
            fileName = argv[i];
			if(!strncmp("-", fileName, 1) || !strncmp("/dev/stdin", fileName, 10)) {
				if(got_stdin) {
					fprintf(stderr, "WARNING: stdin twice in command line, skipping...\n");
                    fflush(stderr);
					continue;
				} else {
					got_stdin = 1;
				}
			} else {
	            if(stat(fileName, &x) < 0) {
	                fprintf(stderr, "ERROR: file cannot be opened: %s : %s\n", fileName, strerror(errno));
	                fflush(stderr);
	                continue;
	            }
			}
            ret = printSHA512(fileName);
        }
       
    }
    return ret; 
}
