//
//  SearchHelper.h
//  SearchAlgos
//
//  Created by Timur Murzakov on 22/10/2022.
//

#ifndef SearchHelper_h
#define SearchHelper_h

#include <stdio.h>
#include <math.h>

typedef unsigned long long ull;

int binarySearch(ull *array, ull *searching, int *low, int *high);
int jumpSearch(ull *array, int len, ull *searching);

#endif /* SearchHelper_h */
