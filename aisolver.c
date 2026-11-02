#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wordbank.h"

bool wordMatcher(char* word, int wordlength, char* missedLetters, int missedCount, char pattern[]){

    for(int i = 0; i < wordlength;i++){
        for(int j = 0; j < missedCount;j++){
            if(word[i] == missedLetters[j])
                return false;
        }
    }

    return true;
}

int main(){
    readList();     
    int count = getCount();

    char missedLetters[26];
    int missedCount = 0;

    static char* candidates[60000];
    int picksCount = 0;
    
    for (int i = 0; i < count; i++) {
        char* word = getWord(i);
        int wordlength = strlen(word);

        if (wordMatcher(word, wordlength, missedLetters, missedCount)) { 
            candidates[picksCount] = word;
            picksCount++;
        }
    }
}