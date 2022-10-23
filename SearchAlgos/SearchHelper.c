//
//  SearchHelper.c
//  SearchAlgos
//
//  Created by Timur Murzakov on 22/10/2022.
//
#include "SearchHelper.h"
/*--------------------------------------*/
//          PRIVATE FUNCTIONS           //
/*--------------------------------------*/
ull min(ull a, ull b) {
    if (b < a)
        return b;
    else
        return a;
}
/*--------------------------------------*/
//          PUBLIC FUNCTIONS            //
/*--------------------------------------*/
// O (logN)
int binarySearch(ull *array, ull *searching, int *low, int *high) {
    while (*low <= *high) {
        int mid = (*low + *high) / 2;
        
        if (*searching == array[mid])
            return mid;
        else if (*searching > array[mid])
            *low = mid + 1;
        else
            *high = mid - 1;
    }
    return -1;
}
// O (N ** 0.5)
int jumpSearch(ull *array, int len, ull *searching) {
    int sqrtLen = sqrt(len);
    int start = 0,
        end = sqrtLen;
    while (start < len && array[end-1] < *searching ) {
        start = end;
        end += sqrtLen;
        if (end >= len)
            end = len;
    }
    for (int i = start; i < end; i++) {
        if (array[i] == *searching)
            return i;
    }
    return -1;
}
