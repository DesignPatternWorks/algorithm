// algorithm.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "sort.h"

void testSort(void)
{
	int a[] = { 1,6,8,9,4,5,6,25,19,3,0,2 };
	std::cout << "before sorted print: " << std::endl;
	myPrint(a, ARRAY_SIZE(a));

	std::cout << "sorted process print: " << std::endl;
	//bubbleSort(a, ARRAY_SIZE(a));
	//bubbleSortByIsExistExchange(a, ARRAY_SIZE(a));
	//bubbleSortByRecordLastSwapIndex(a, ARRAY_SIZE(a));
	//quickSort(a, 0, ARRAY_SIZE(a)-1);
	//simpleSelectSort(a, ARRAY_SIZE(a));
	//simpleSelectSort2(a, ARRAY_SIZE(a));
	//simpleSelectSort3(a, ARRAY_SIZE(a));
	//minHeapSort(a, ARRAY_SIZE(a));
	//maxHeapSort(a, ARRAY_SIZE(a));
	//directInsertSort(a, ARRAY_SIZE(a));
	//shellSort(a, ARRAY_SIZE(a));

	int *res = new int[ARRAY_SIZE(a)];
	//mergeSort(a, 0, ARRAY_SIZE(a)-1, res);
	countSort(a, ARRAY_SIZE(a), res);

	std::cout << "after sorted print: " << std::endl;
	//myPrint(a, ARRAY_SIZE(a));
	myPrint(res, ARRAY_SIZE(a));
	delete[]res;
}

int main()
{
	testSort();

    return 0;
}

