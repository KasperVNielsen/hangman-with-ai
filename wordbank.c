#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wordbank.h"

static int count = 0;             
static char wordlist[466471][64];   

void readList(){
   
    if (count == 0) {                 
        FILE *fptr = fopen("words2.txt", "r");
        if (fptr == NULL) { printf("no file\n"); exit(1); }
        while (count < 466471 && fgets(wordlist[count], 64, fptr) != NULL) {
            wordlist[count][strcspn(wordlist[count], "\n")] = '\0'; 
            count++;
        }
        
        fclose(fptr);
    }
}

int getCount(){
    return count;
}

char* getWord(int index){
    if (index < 0 || index >= count){
         printf("index not correct");
         return NULL;         
    }
    return wordlist[index];   
}


