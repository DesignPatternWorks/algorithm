#include "stdafx.h"
#include "sort.h"

void mySwap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void myPrint(int a[], int len, int loop)
{
	std::cout << "loop[" << loop << "]: ";
	for (int i = 0; i < len; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}

/************************************************************************/
/* 交换排序*/
/*
冒泡排序：
快速排序：
*/
/************************************************************************/


/* 冒泡排序*/
void bubbleSort(int a[], int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len-i-1; j++)
		{
			if (a[j] > a[j+1])
			{
				mySwap(a[j], a[j+1]);
			}
		}
		myPrint(a, len, i);
	}
}

/* 改进的冒泡排序1
增加某一趟是否有交换的记录，没有则认为已经排序完成，否则没有排序完成，继续交换
*/
void bubbleSortByIsExistExchange(int a[], int len)
{
	bool isExitExchange = true; // 第一次假定存在交换
	int tmpLen = len-1; //若存在交换，下一次for循环遍历的长度,
						//初始化为len-1,因为for循环从0开始，且数组索引有i+1
	while (isExitExchange)  
	{
		isExitExchange = false; //默认是不存在交换

		for (int i = 0; i < tmpLen; i++) 
		{
			if (a[i] > a[i+1])
			{
				mySwap(a[i], a[i+1]);
				isExitExchange = true;
			}
		}
		myPrint(a, len);
		tmpLen--;
	}
}

/*改进的冒泡排序2
增加记录某一趟遍历最后一次交换的位置，下一次从头开始遍历的时候就可以从记录的位置索引为长度开始跳跃着交换，而不需要每次长度只递减1
*/

void bubbleSortByRecordLastSwapIndex(int a[], int len)
{
	int lastSwapInex = len - 1; //若存在交换，下一次for循环遍历的长度,初始化为len-1
	int swapFlag = lastSwapInex; //swapFlag: 是否继续交换的标志

	while (swapFlag)
	{
		lastSwapInex = swapFlag; // 根据上一次记录的最后交换索引，更新本次for循环的长度
		swapFlag = 0;  // 默认是0，不继续
		for (int i = 0; i < lastSwapInex; i++)
		{
			if (a[i] > a[i+1])
			{
				mySwap(a[i], a[i+1]);
				swapFlag = i;
			}
		}	
		myPrint(a, len);
	}
}


/*快速排序
分治 + 递归
1. 确定基准值(一般是序列第一个位置、最后一个位置或中间位置(先交换第一个和中间位置那个元素))
2. 从序列后面开始向前找元素，若小于基准值则交换之，否则继续前向步进，直到找到一个满足条件的值；
3. 从序列前面开始向后找元素，若大于基准值则交换之(元素与上一次的交换操作的结果进行交换)，否则继续向后步进，
   直到找到一个满足条件的值；
4. 重复2~3操作，直到基准值左边的元素均不大于基准值，基准值右边的元素均不小于基准值，分为了左半部分和右半部分。
5. 分别对左半部分和右半部分重复1~4的操作
*/

/*进行经过1~4步操作,并返回基准值的位置*/
int getPartionIndex(int a[], int left, int right)
{
	int stardardValue = a[left]; // 初始化基准值为序列第一个位置的值
	int i = left; // 初始i,j
	int j = right;

	while (i < j) // 循环继续条件
	{
		while ((i < j) && (a[j] >= stardardValue)) //从后面元素开始向前遍历，未找到满足条件继续步进
		{
			j--;
		}
		mySwap(a[i], a[j]);  //找到了一个小于stardardValue，则交换

		while ((i < j) && (a[i] <= stardardValue)) //从前面元素开始向后遍历，未找到满足条件继续步进
		{
			i++;
		}
		mySwap(a[i], a[j]); //找到了一个大于stardardValue，则交换
	}
	myPrint(a, right, i);
	return i;
}

void quickSort(int a[], int left, int right)
{
	if (left < right)
	{
		int stardardValueIndex = getPartionIndex(a, left, right); //获取基准位置，使基准位置左边数不比基准大，右边数不比基准小
		quickSort(a, left, stardardValueIndex - 1); // 快排左边的部分
		quickSort(a, stardardValueIndex + 1, right); // 快排右边的部分
	}
}



/************************************************************************/
/* 选择排序                                                                     */
/************************************************************************/
/*
简单的选择排序
*/

//获取长度为len的序列a[] 从索引index开始到len-1范围序列的最小值的索引
int getMinValueIndex(int a[], int len, int index)
{
	int minValue = a[index];
	int minValueInex = index;

	for (int i = index + 1; i < len; i++)
	{
		if (a[i] < minValue)
		{
			minValue = a[i];
			minValueInex = i;
		}
	}

	return minValueInex;
}

//从i ~ len中选择最小值，放到索引为i的位置(i = 0 ~ len（外层循环)）
void simpleSelectSort(int a[], int len)
{
	int minValueInex = 0;

	for (int i = 0; i< len; i++)
	{
		minValueInex = getMinValueIndex(a, len, i);
		if (minValueInex != i)
		{
			mySwap(a[i], a[minValueInex]);
		}
		myPrint(a, len, i);
	}
}

//内层循环从i+1 ~ len中依次与i进行比较，选择最小值，放到索引为i的位置(i = 0 ~ len（外层循环)）
void simpleSelectSort2(int a[], int len)
{
	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (a[j] < a[i])
			{
				mySwap(a[j], a[i]);
			}
		}
		myPrint(a, len, i);
	}
}

//二元选择排序，每次从i ~ len-i中选择最大值和最小值，然后分别放入i和len-i-1的位置(i = 0 ~ len/2)
void simpleSelectSort3(int a[], int len)
{
	int minValueIndex = 0;
	int maxValueIndex = 0;

	for (int i = 0; i < len/2; i++) // i只需0~len/2
	{
		minValueIndex = i;
		maxValueIndex = i;

		for (int j = i+1; j < len-i; j++) //遍历i~len-i获取最大值和最小值索引
		{
			if (a[j] > a[maxValueIndex])
			{
				maxValueIndex = j;
				continue; // 满足大于当前最大值条件就没必要去下面比较最小值了
			}

			if (a[j] < a[minValueIndex])
			{
				minValueIndex = j;
			}
		}

		if (minValueIndex != i)
		{
			mySwap(a[i], a[minValueIndex]); // 获取的最小值与a[i]交换
		}
		if (maxValueIndex != len-i-1)
		{
			mySwap(a[len-i-1], a[maxValueIndex]); // 获取的最大值与a[len-i-1]交换
		}
		myPrint(a, len, i);
	}
}


/*
堆排序(最大堆：父节点值均比子节点值大，堆顶为最大值； 最小堆： 父节点值均比子节点值小，堆顶为最小值)
树形选择排序
*/

/*
最小堆排序
*/

// 向下调整最小堆：当前位置index, 左右孩子节点分别为2*index+1和2*index+2
// 最小值上浮过程
void downAdjustMinHeap(int a[], int len, int index)
{
	int sonIndex = 2 * index + 1;
	int tmp = a[index]; // 交换第一步

	while (sonIndex < len)
	{
		if ((sonIndex+1 < len) && (a[sonIndex+1] < a[sonIndex])) // 获取左右孩子节点的较小值的索引
		{
			sonIndex++;
		}

		if (a[sonIndex] >= tmp)    // 若孩子结点不比当前值小，则退出
		{
			break;
		}

		// 若孩子结点比当前值小，则交换之
		a[index] = a[sonIndex]; // 交换第二步
		index = sonIndex;

		sonIndex = 2 * index + 1; //继续后续孩子结点比较
	}

	a[index] = tmp;  // 交换第三步,注意，此处索引为index,非sonIndex（因为sonIndex已经运算了一次sonIndex = 2*index + 1了）。
}


// 建立最小堆：从堆中最下面的非叶子节点(总共len/2-1个非叶子节点)开始依次往上使用(直到索引为0)向下调整最小堆的方法
void buildMinHeap(int a[], int len)
{
	for (int i = len/2-1; i >=0; i--)
	{
		downAdjustMinHeap(a, len, i);
	}
	std::cout << "build min heap result: ";
	myPrint(a, len);
}


/*
最小堆排序：(从大到小顺序)
1.建立最小堆
2.交换堆顶(最小值)和末尾位置
3.向下重新调整最小堆(不包括末尾位置)
4.循环2~3步骤(末尾位置不断变小)
*/
void minHeapSort(int a[], int len)
{
	buildMinHeap(a, len);
	for (int i = len-1; i >=1; i--)
	{
		mySwap(a[0], a[i]);
		downAdjustMinHeap(a, i, 0); // 每次都是从根节点0
		myPrint(a, len, i);
	}
}

/*
最大堆排序
*/

// 向下调整最大堆：当前位置index, 左右孩子节点分别为2*index和2*index+1
// 最大值上浮过程
void downAdjustMaxHeap(int a[], int len, int index)
{
	int leftSonIndex = 2*index;
	int rightSonIndex = 2*index + 1;
	int largerSonIndex = index; //默认较大值为当前父节点

	if ((leftSonIndex <= index) && (a[leftSonIndex] > a[largerSonIndex])) // 比较左孩子，获取较大值的索引
	{
		largerSonIndex = leftSonIndex;
	}
	if ((rightSonIndex <= index) && (a[rightSonIndex] > a[largerSonIndex]))// 比较右孩子，获取较大值的索引
	{
		largerSonIndex = rightSonIndex;
	}

	if (largerSonIndex != index) //非当前父节点则交换之，且继续比较下面的子节点
	{
		mySwap(a[index], a[largerSonIndex]);
		downAdjustMaxHeap(a, len, largerSonIndex); // 递归调用下面的子节点
	}

}

// 建立最大堆：从堆中最下面的非叶子节点(总共len/2个非叶子节点)开始依次往上使用(直到索引为0)向下调整最大堆的方法
void buildMaxHeap(int a[], int len)
{
	for (int i = len/2; i >= 0; i--)
	{
		downAdjustMaxHeap(a, len, i);
	}
	std::cout << "build max heap result: ";
	myPrint(a, len);
}

/*
最大堆排序：(从小到大顺序)
1.建立最大堆
2.交换堆顶(最大值)和末尾位置
3.向下重新调整最大堆(不包括末尾位置)
4.循环2~3步骤(末尾位置不断变小)
*/
void maxHeapSort(int a[], int len)
{
	buildMaxHeap(a, len);
	for (int i = len-1; i >=1; i--)
	{
		mySwap(a[0], a[i]);
		downAdjustMaxHeap(a, i, 0); // 每次都是从根节点0
		myPrint(a, len, i);
	}
}

/************************************************************************/
/* 插入排序                                                                 
将一个记录插入到一个已经排序好的序列中，从而得到一个新的，记录数+1的有序序列
即先将有序序列第一个元素当成有序序列，然后从第二个元素开始依次逐个进行插入，直到整个序列有序为止
*/
/************************************************************************/

/*直接的插入排序
从哨兵开始从后向前比较
*/
void directInsertSort(int a[], int len)
{
	for (int i = 1; i < len; i++)
	{
		if (a[i] < a[i-1]) // 哨兵前一个元素比哨兵大则进行后移操作
		{
			int tmp = a[i]; // 暂存当前哨兵值
			int index = i - 1; // 暂存当前哨兵前一个元素的值
			a[i] = a[i-1]; // 后移一位当前哨兵值的前一个元素

			while (a[index] > tmp)  // 若当前哨兵值前面多个序列元素比哨兵值大，则哨兵值前面序列的较大元素依次循环后移
			{
				a[index + 1] = a[index];
				index--;
			}
			a[index + 1] = tmp; // 当前哨兵值插入合适为止，使当前哨兵值前一个元素刚好不大于其值
 		}
		myPrint(a, len, i);
	}
}

/*
通用的插入排序
直接插入排序中dk = 1;
*/
void shellInsertSort(int a[], int len, int dk)
{
	for (int i = dk; i < len; i++)
	{
		if (a[i] < a[i-dk]) // 哨兵前dk距离的元素比哨兵大则进行后移操作
		{
			int tmp = a[i];  // 暂存当前哨兵值
			int index = i - dk; // 暂存当前哨兵前dk距离的元素的值
			a[i] = a[i-dk]; // 后移dk位当前哨兵值的前dk距离的元素

			while (a[index] > tmp) // 若当前哨兵值前面多个距离为dk的序列元素比哨兵值大，则哨兵值前面序列的较大元素依次循环后移
			{
				a[index + dk] = a[index];
				index -= dk;
			}
			a[index + dk] = tmp; // 当前哨兵值插入合适为止，使当前哨兵值前dk距离的元素刚好不大于其值
		}
	}
}

/*
希尔排序：
减少增量的直接插入排序，直到增量为1
*/
void shellSort(int a[], int len)
{
	int dk = len / 2; //dk = len/2,len/4....,1;
	while (dk >=1)
	{
		shellInsertSort(a, len, dk);
		dk /= 2;
		myPrint(a, len, dk);
	}
}

/************************************************************************/
/* 归并排序
先递归序列拆成多个有序序列，直到每个序列有一个元素，然后再合并有序序列
*/
/************************************************************************/

//合并两个有序序列a[len_a]和b[len_b]到最终有序序列res[]中
void commonMergeSortedSequence(int a[], int len_a, int b[], int len_b, int res[])
{
	int index = 0;
	int i = 0;
	int j = 0;

	while (i < len_a && j < len_b)
	{
		if (a[i] < b[j]) //结果中存入较小的a元素
		{
			res[index++] = a[i++];
		}
		else          //结果中存入较小的b元素
		{
			res[index++] = b[j++];
		}
	}

	while (i < len_a) // 结果中存入剩余的a元素
	{
		res[index++] = a[i++];
	}

	while (j < len_b) // 结果中存入剩余的b元素
	{
		res[index++] = b[j++];
	}	
}

/*
归并排序
*/
//合并有序序列a[left, mid)和 a[mid, right)到最终有序序列res[]中,初始化left = 0, right = len-1
void mergeArray(int a[], int left, int mid, int right, int res[])
{
	int i = left; // i 从[left,mid]包括mid
	int j = mid+1;  // j 从[mid+1,right]包括right
	int index = 0;

	while (i <= mid && j <= right)
	{
		if (a[i] < a[j])
		{
			res[index++] = a[i++];
		}
		else
		{
			res[index++] = a[j++];
		}
	}

	while (i <= mid)
	{
		res[index++] = a[i++];
	}
	while (j <= right)
	{
		res[index++] = a[j++];
	}

	// 将合并结果res[]赋给a[left,right),保持a[]有序，以便下面递归使用
	for (i = 0; i < index; i++)
	{
		a[left + i] = res[i];
	}
	myPrint(res, index);
}

void mergeSort(int a[], int left, int right, int res[])
{
	if (left  < right)
	{
		int mid = (left + right)/2;
		mergeSort(a, left, mid, res); // 递归归并排序左边的有序序列
		mergeSort(a, mid+1, right, res); //递归 归并排序右边的有序序列
		mergeArray(a, left, mid, right, res); // 合并有序的左边和右边有序序列
	}
}

/************************************************************************/
/* 计数排序
*/
/************************************************************************/

int getMaxValue(int a[], int len)
{
	int maxValue = a[0];
	for (int i = 0; i < len; i++)
	{
		if (a[i] > maxValue)
		{
			maxValue = a[i];
		}
	}
	return maxValue;
}

void countSort(int a[], int len, int res[])
{
	int maxValue = getMaxValue(a, len);
	int *countArray = new int[maxValue+1]; //  计数数组
	int i = 0;

	for (i = 0; i < maxValue+1; i++)
	{
		countArray[i] = 0;    // 初始化计数数组为0
	}

	for (i = 0; i < len; i++)
	{
		countArray[a[i]]++; // 计数a[]中每个元素的个数存入计数数组，且索引为元素值
	}

	for (i = 1; i < maxValue+1; i++)
	{
		countArray[i] += countArray[i - 1]; // 累加计数数组，最终计数数组中保存不小于元素值的计数个数，索引依然为元素值
	}

	for (i = 0; i < len; i++)
	{
		int element = a[i]; // 当前待排序元素a[i]值
		int sortIndex = countArray[element] - 1; // 当前元素a[i]在最终排序后有序序列中的位置索引
		res[sortIndex] = element; // 将当前元素a[i]放在最终排序后有序序列中的相应位置上
		countArray[element]--;  // 每次放入一个后，个数减一调整之
		myPrint(a, len, sortIndex);
	}

	delete []countArray;
}