//
//  RomanToInteger.c
//  DataStructure
//
//  Created by Timur Murzakov on 12/10/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../Dictionary/Dict.h"

// it gets a string to check
int romanToInt(char *s, struct Dict *alphabet) {
    int sums = 0;
    for (int i = 0; i < strlen(s); i++) {
        int *searchableA = (int *)alphabet->search(&s[i], sizeof(char), alphabet);
        int *searchableB = (int *)alphabet->search(&s[i+1], sizeof(char), alphabet);
        if (searchableB && *searchableA < *searchableB) {
            sums -= *searchableA;
        } else {
            sums += *searchableA;
        }
    }
    
    return sums;
}

void createRomanToInt(char key, int value, struct Dict *dict) {
    dict->insert(&key, sizeof(key), &value, sizeof(value), dict);
}


int main() {
    struct Dict romans = dictConsructor(compareStringKeys);
    
    int *value = (int *)malloc(sizeof(int));
    char *key = (char *)malloc(sizeof(char));
    
    *key = 'I'; *value = 1;
    romans.insert(&key, sizeof(key), &value, sizeof(value), &romans);
    
    
    createRomanToInt('I', 1, &romans);
    createRomanToInt('V', 5, &romans);
    createRomanToInt('X', 10, &romans);
    createRomanToInt('L', 50, &romans);
    createRomanToInt('C', 100, &romans);
    createRomanToInt('D', 500, &romans);
    createRomanToInt('M', 1000, &romans);
    
    printf("%d\n", romanToInt("LIXI", &romans));
}

