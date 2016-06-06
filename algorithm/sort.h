#ifndef _SORT_H_
#define _SORT_H_


#include <iostream>
#define  ARRAY_SIZE(a)  sizeof(a)/sizeof(a[0])

void myPrint(int a[], int len, int loop = 0);
void bubbleSort(int a[], int len);
void bubbleSortByIsExistExchange(int a[], int len);
void bubbleSortByRecordLastSwapIndex(int a[], int len);
void quickSort(int a[], int left, int right);
void simpleSelectSort(int a[], int len);
void simpleSelectSort2(int a[], int len);
void simpleSelectSort3(int a[], int len);
void minHeapSort(int a[], int len);
void maxHeapSort(int a[], int len);
void directInsertSort(int a[], int len);
void shellSort(int a[], int len);
void mergeSort(int a[], int left, int right, int res[]);
void countSort(int a[], int len, int res[]);

#endif
