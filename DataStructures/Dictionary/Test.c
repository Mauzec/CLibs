//
//  Test.c
//  DataStructure
//
//  Created by Timur Murzakov on 11/10/2022.
//

#include <stdio.h>
#include "Dict.h"

int main(void) {
    struct Dict myDict = dictConsructor(compareStringKeys);
    myDict.insert("Michael Brown", 13, "BSc", 3, &myDict);
    myDict.insert("Elena Wirroon", 13, "MSc", 3, &myDict);
    
    printf("%s\n", (char *)(myDict.search("Michael Brown", 13, &myDict)));
    printf("%s\n", (char *)(myDict.search("Elena Wirroon", 13, &myDict)));
}
