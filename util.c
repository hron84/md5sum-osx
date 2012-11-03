#include <string.h>
#include "util.h"

void chop(char *victim, char what) {
    
    while(*victim != what && *victim != '\0') victim++;
    if(*victim == what) {
        *victim = '\0';
    }
    
}

void chomp(char *victim) {
    chop(victim, '\r');
    chop(victim, '\n');
}

void ltrim(char **victim, char what) {
    int i;
    
    for(i = 0; i < strlen(*victim); i++) {
        if(**victim == what) {
            ++*victim;
        }
        
        /* Preventing to enter into the string */
        if(**victim != what) {
            break;
        }
    }
}
