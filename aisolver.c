#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wordbank.h"
#include <string.h>

bool wordMatcher(char* word, char* missedLetters, int missedCount, char* pattern){
       int length = strlen(pattern);
       
       //rule one match length
       if(strlen(word) != length)
            return false;

       for (int i = 0; i < length; i++) {

            // Rule 2: Revealed positions must match
            if (pattern[i] != '_' && pattern[i] != word[i])
                return false;

            // Rule 3: Revealed letters cannot be hidden
            if (pattern[i] == '_') {
                for (int j = 0; j < length; j++) {
                    if (pattern[j] != '_' && word[i] == pattern[j]) {
                        return false;
                    }
                }
            }

            

            // Rule 4: No missed letters
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
    
    char pattern[] = "ne_erland";

    char missedLetters[26];
    int missedCount = 0;

    static char* candidates[60000];
    int picksCount = 0;
    
    for (int i = 0; i < count; i++) {
        char* word = getWord(i);

        if (wordMatcher(word, missedLetters, missedCount, pattern )) { 
            candidates[picksCount] = word;
            picksCount++;
        }
    }


}