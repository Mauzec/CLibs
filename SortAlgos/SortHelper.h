//
//  SortHelper.h
//  SortAlgos
//
//  Created by Timur Murzakov on 18/10/2022.
//

#ifndef SortHelper_h
#define SortHelper_h

#include <stdlib.h>

// Defining of "constructors" of functions
#define makeSelectionSort(T) \
void selectionSort##T(T *array, int len) { \
    for (int i = 0; i < len; i++) { \
        int minIndex = i; \
        for (int j = i + 1; j < len; j++) { \
            if (array[i] > array[j]) { \
                minIndex = j;\
            } \
        } \
        if (minIndex != i) { \
            T tmp = array[i]; \
            array[i] = array[minIndex]; \
            array[minIndex] = tmp; \
        }\
    } \
}

#define makeInsertionSort(T) \
void insertionSort##T(T *array, int len) { \
    for (int i = 1; i < len; i++) { \
        T key = array[i]; \
        int j = i - 1; \
        for (; j >= 0 && array[j] > key; j--) { \
            array[j + 1] = array[j]; \
        } \
        array[j + 1] = key; \
    }\
}

#define makeBubbleSort(T) \
void bubbleSort##T(T *array, int len) { \
    for (int i = 0; i < len; i++) { \
        for (int j = 0; j < len - i - 1; j++) \
            if (array[j] > array[j + 1]) { \
                T tmp = array[j]; \
                array[j] = array[j + 1]; \
                array[j + 1] = tmp; \
            } \
    } \
}

#define makeQuickSort(T) \
int partition##T(T *array, int low, int high) { \
    T pivot = array[high]; \
    int i = low - 1; \
    for (int j = low; j < high; j++) { \
        if (array[j] < pivot) { \
            i++; \
            T tmp = array[i]; \
            array[i] = array[j]; \
            array[j] = tmp; \
        } \
    } \
    T tmp = array[i+1]; \
    array[i+1] = array[high]; \
    array[high] = tmp; \
    \
    return i + 1; \
} \
void quickSort##T(T *array, int low, int high) { \
    if (low >= high || low < 0) \
        return; \
    int piv = partition##T(array, low, high); \
    quickSort##T(array, low, piv - 1); \
    quickSort##T(array, piv + 1, high); \
}

// good with small values
#define makeCocktailShackerSort(T) \
void cocktailShakerSort##T(T *array, int len) { \
    char swapped = 1; \
    int start = 0, end = len - 1; \
    while (swapped) { \
        swapped = 0; \
        for (int i = start; i < end; i++) { \
            if (array[i] > array[i+1]) { \
                T tmp = array[i]; \
                array[i] = array[i + 1]; \
                array[i + 1] = tmp; \
                swapped = 1; \
            } \
        } \
        if (!swapped) \
            break; \
        swapped = 0; \
        end -= 1; \
        for (int i = end - 1; i >= start; i--) { \
            if (array[i] > array[i + 1]) { \
                T tmp = array[i]; \
                array[i] = array[i + 1]; \
                array[i + 1] = tmp; \
                swapped = 1; \
            } \
        } \
    start += 1; \
} \
}

#define makeMergeSort(T) \
void merge##T(T *array, int left, int mid, int right) { \
    const int lenLeft = mid - left + 1; \
    const int lenRight = right - mid; \
\
    T *leftArray = (T *)malloc(sizeof(T) * lenLeft); \
    T *rightArray = (T *)malloc(sizeof(T) * lenRight); \
\
    for (int i = 0; i < lenLeft; i++) \
        leftArray[i] = array[left + i]; \
    for (int i = 0; i < lenRight; i++) \
        rightArray[i] = array[mid + 1 + i]; \
\
    int indexLeft = 0, indexRight = 0, indexResult = left; \
\
    for (;indexLeft < lenLeft && indexRight < lenRight; indexResult++) { \
        if (leftArray[indexLeft] <= rightArray[indexRight]) { \
            array[indexResult] = leftArray[indexLeft]; \
            indexLeft += 1; \
        } else { \
            array[indexResult] = rightArray[indexRight]; \
            indexRight += 1; \
        } \
    } \
\
    for (;indexLeft < lenLeft; indexLeft++, indexResult++) { \
        array[indexResult] = leftArray[indexLeft]; \
    } \
    for (;indexRight < lenRight; indexRight++, indexResult++) { \
        array[indexResult] = rightArray[indexRight]; \
    } \
\
    free(leftArray); \
    free(rightArray); \
} \
void mergeSort##T(T *array, int left, int right) { \
    if (left >= right) \
        return; \
\
    int mid = left + (right - left) / 2; \
\
    mergeSort##T(array, left, mid); \
    mergeSort##T(array, mid + 1, right); \
    merge##T(array, left, mid, right); \
}

#endif /* SortHelper_h */
