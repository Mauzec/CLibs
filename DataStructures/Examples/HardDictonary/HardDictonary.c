//
//  HardDictonary.c
//  DataStructure
//
//  Created by Timur Murzakov on 12/10/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../Dictionary/Dict.h"

struct Dict createPerson(char *fullname, int age, int salary, char *specialty) {
    struct Dict info = dictConsructor(compareStringKeys);
    info.insert("Salary", 6, &salary, sizeof(salary), &info);
    info.insert("Age", 3, &age, sizeof(age), &info);
    info.insert("Specialty", 9, specialty, strlen(specialty), &info);
    
    struct Dict person = dictConsructor(compareStringKeys);
    person.insert(fullname, strlen(fullname), &info, sizeof(struct Dict), &person);
    
    return person;
}

int main(void) {
    struct Dict headers = dictConsructor(compareStringKeys);
    
    struct Dict person = createPerson("Ms Harlet", 49, 202950, "Director");
    
    headers.insert("Headers", 7, &person, sizeof(struct Dict), &headers);
    
    // receive a person info
    struct Dict *myHeaders = (struct Dict *)(headers.search("Headers", 7, &headers));
    struct Dict *myPerson = (struct Dict *)(myHeaders->search("Ms Harlet", 10, myHeaders));
    
    printf("//--Mrs Harlet--//\n");
    printf("Salary: %d\n", *(int *)(myPerson->search("Salary", 6, myPerson)));
    printf("Age: %d\n", *(int *)(myPerson->search("Age", 3, myPerson)));
    printf("Specialty: %s\n", (char *)(myPerson->search("Specialty", 9, myPerson)));
}
