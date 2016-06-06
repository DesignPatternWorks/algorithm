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
/* ��������*/
/*
ð������
��������
*/
/************************************************************************/


/* ð������*/
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

/* �Ľ���ð������1
����ĳһ���Ƿ��н����ļ�¼��û������Ϊ�Ѿ�������ɣ�����û��������ɣ���������
*/
void bubbleSortByIsExistExchange(int a[], int len)
{
	bool isExitExchange = true; // ��һ�μٶ����ڽ���
	int tmpLen = len-1; //�����ڽ�������һ��forѭ�������ĳ���,
						//��ʼ��Ϊlen-1,��Ϊforѭ����0��ʼ��������������i+1
	while (isExitExchange)  
	{
		isExitExchange = false; //Ĭ���ǲ����ڽ���

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

/*�Ľ���ð������2
���Ӽ�¼ĳһ�˱������һ�ν�����λ�ã���һ�δ�ͷ��ʼ������ʱ��Ϳ��ԴӼ�¼��λ������Ϊ���ȿ�ʼ��Ծ�Ž�����������Ҫÿ�γ���ֻ�ݼ�1
*/

void bubbleSortByRecordLastSwapIndex(int a[], int len)
{
	int lastSwapInex = len - 1; //�����ڽ�������һ��forѭ�������ĳ���,��ʼ��Ϊlen-1
	int swapFlag = lastSwapInex; //swapFlag: �Ƿ���������ı�־

	while (swapFlag)
	{
		lastSwapInex = swapFlag; // ������һ�μ�¼����󽻻����������±���forѭ���ĳ���
		swapFlag = 0;  // Ĭ����0��������
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


/*��������
���� + �ݹ�
1. ȷ����׼ֵ(һ�������е�һ��λ�á����һ��λ�û��м�λ��(�Ƚ�����һ�����м�λ���Ǹ�Ԫ��))
2. �����к��濪ʼ��ǰ��Ԫ�أ���С�ڻ�׼ֵ�򽻻�֮���������ǰ�򲽽���ֱ���ҵ�һ������������ֵ��
3. ������ǰ�濪ʼ�����Ԫ�أ������ڻ�׼ֵ�򽻻�֮(Ԫ������һ�εĽ��������Ľ�����н���)�����������󲽽���
   ֱ���ҵ�һ������������ֵ��
4. �ظ�2~3������ֱ����׼ֵ��ߵ�Ԫ�ؾ������ڻ�׼ֵ����׼ֵ�ұߵ�Ԫ�ؾ���С�ڻ�׼ֵ����Ϊ����벿�ֺ��Ұ벿�֡�
5. �ֱ����벿�ֺ��Ұ벿���ظ�1~4�Ĳ���
*/

/*���о���1~4������,�����ػ�׼ֵ��λ��*/
int getPartionIndex(int a[], int left, int right)
{
	int stardardValue = a[left]; // ��ʼ����׼ֵΪ���е�һ��λ�õ�ֵ
	int i = left; // ��ʼi,j
	int j = right;

	while (i < j) // ѭ����������
	{
		while ((i < j) && (a[j] >= stardardValue)) //�Ӻ���Ԫ�ؿ�ʼ��ǰ������δ�ҵ�����������������
		{
			j--;
		}
		mySwap(a[i], a[j]);  //�ҵ���һ��С��stardardValue���򽻻�

		while ((i < j) && (a[i] <= stardardValue)) //��ǰ��Ԫ�ؿ�ʼ��������δ�ҵ�����������������
		{
			i++;
		}
		mySwap(a[i], a[j]); //�ҵ���һ������stardardValue���򽻻�
	}
	myPrint(a, right, i);
	return i;
}

void quickSort(int a[], int left, int right)
{
	if (left < right)
	{
		int stardardValueIndex = getPartionIndex(a, left, right); //��ȡ��׼λ�ã�ʹ��׼λ����������Ȼ�׼���ұ������Ȼ�׼С
		quickSort(a, left, stardardValueIndex - 1); // ������ߵĲ���
		quickSort(a, stardardValueIndex + 1, right); // �����ұߵĲ���
	}
}



/************************************************************************/
/* ѡ������                                                                     */
/************************************************************************/
/*
�򵥵�ѡ������
*/

//��ȡ����Ϊlen������a[] ������index��ʼ��len-1��Χ���е���Сֵ������
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

//��i ~ len��ѡ����Сֵ���ŵ�����Ϊi��λ��(i = 0 ~ len�����ѭ��)��
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

//�ڲ�ѭ����i+1 ~ len��������i���бȽϣ�ѡ����Сֵ���ŵ�����Ϊi��λ��(i = 0 ~ len�����ѭ��)��
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

//��Ԫѡ������ÿ�δ�i ~ len-i��ѡ�����ֵ����Сֵ��Ȼ��ֱ����i��len-i-1��λ��(i = 0 ~ len/2)
void simpleSelectSort3(int a[], int len)
{
	int minValueIndex = 0;
	int maxValueIndex = 0;

	for (int i = 0; i < len/2; i++) // iֻ��0~len/2
	{
		minValueIndex = i;
		maxValueIndex = i;

		for (int j = i+1; j < len-i; j++) //����i~len-i��ȡ���ֵ����Сֵ����
		{
			if (a[j] > a[maxValueIndex])
			{
				maxValueIndex = j;
				continue; // ������ڵ�ǰ���ֵ������û��Ҫȥ����Ƚ���Сֵ��
			}

			if (a[j] < a[minValueIndex])
			{
				minValueIndex = j;
			}
		}

		if (minValueIndex != i)
		{
			mySwap(a[i], a[minValueIndex]); // ��ȡ����Сֵ��a[i]����
		}
		if (maxValueIndex != len-i-1)
		{
			mySwap(a[len-i-1], a[maxValueIndex]); // ��ȡ�����ֵ��a[len-i-1]����
		}
		myPrint(a, len, i);
	}
}


/*
������(���ѣ����ڵ�ֵ�����ӽڵ�ֵ�󣬶Ѷ�Ϊ���ֵ�� ��С�ѣ� ���ڵ�ֵ�����ӽڵ�ֵС���Ѷ�Ϊ��Сֵ)
����ѡ������
*/

/*
��С������
*/

// ���µ�����С�ѣ���ǰλ��index, ���Һ��ӽڵ�ֱ�Ϊ2*index+1��2*index+2
// ��Сֵ�ϸ�����
void downAdjustMinHeap(int a[], int len, int index)
{
	int sonIndex = 2 * index + 1;
	int tmp = a[index]; // ������һ��

	while (sonIndex < len)
	{
		if ((sonIndex+1 < len) && (a[sonIndex+1] < a[sonIndex])) // ��ȡ���Һ��ӽڵ�Ľ�Сֵ������
		{
			sonIndex++;
		}

		if (a[sonIndex] >= tmp)    // �����ӽ�㲻�ȵ�ǰֵС�����˳�
		{
			break;
		}

		// �����ӽ��ȵ�ǰֵС���򽻻�֮
		a[index] = a[sonIndex]; // �����ڶ���
		index = sonIndex;

		sonIndex = 2 * index + 1; //�����������ӽ��Ƚ�
	}

	a[index] = tmp;  // ����������,ע�⣬�˴�����Ϊindex,��sonIndex����ΪsonIndex�Ѿ�������һ��sonIndex = 2*index + 1�ˣ���
}


// ������С�ѣ��Ӷ���������ķ�Ҷ�ӽڵ�(�ܹ�len/2-1����Ҷ�ӽڵ�)��ʼ��������ʹ��(ֱ������Ϊ0)���µ�����С�ѵķ���
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
��С������(�Ӵ�С˳��)
1.������С��
2.�����Ѷ�(��Сֵ)��ĩβλ��
3.�������µ�����С��(������ĩβλ��)
4.ѭ��2~3����(ĩβλ�ò��ϱ�С)
*/
void minHeapSort(int a[], int len)
{
	buildMinHeap(a, len);
	for (int i = len-1; i >=1; i--)
	{
		mySwap(a[0], a[i]);
		downAdjustMinHeap(a, i, 0); // ÿ�ζ��ǴӸ��ڵ�0
		myPrint(a, len, i);
	}
}

/*
��������
*/

// ���µ������ѣ���ǰλ��index, ���Һ��ӽڵ�ֱ�Ϊ2*index��2*index+1
// ���ֵ�ϸ�����
void downAdjustMaxHeap(int a[], int len, int index)
{
	int leftSonIndex = 2*index;
	int rightSonIndex = 2*index + 1;
	int largerSonIndex = index; //Ĭ�Ͻϴ�ֵΪ��ǰ���ڵ�

	if ((leftSonIndex <= index) && (a[leftSonIndex] > a[largerSonIndex])) // �Ƚ����ӣ���ȡ�ϴ�ֵ������
	{
		largerSonIndex = leftSonIndex;
	}
	if ((rightSonIndex <= index) && (a[rightSonIndex] > a[largerSonIndex]))// �Ƚ��Һ��ӣ���ȡ�ϴ�ֵ������
	{
		largerSonIndex = rightSonIndex;
	}

	if (largerSonIndex != index) //�ǵ�ǰ���ڵ��򽻻�֮���Ҽ����Ƚ�������ӽڵ�
	{
		mySwap(a[index], a[largerSonIndex]);
		downAdjustMaxHeap(a, len, largerSonIndex); // �ݹ����������ӽڵ�
	}

}

// �������ѣ��Ӷ���������ķ�Ҷ�ӽڵ�(�ܹ�len/2����Ҷ�ӽڵ�)��ʼ��������ʹ��(ֱ������Ϊ0)���µ������ѵķ���
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
��������(��С����˳��)
1.��������
2.�����Ѷ�(���ֵ)��ĩβλ��
3.�������µ�������(������ĩβλ��)
4.ѭ��2~3����(ĩβλ�ò��ϱ�С)
*/
void maxHeapSort(int a[], int len)
{
	buildMaxHeap(a, len);
	for (int i = len-1; i >=1; i--)
	{
		mySwap(a[0], a[i]);
		downAdjustMaxHeap(a, i, 0); // ÿ�ζ��ǴӸ��ڵ�0
		myPrint(a, len, i);
	}
}

/************************************************************************/
/* ��������                                                                 
��һ����¼���뵽һ���Ѿ�����õ������У��Ӷ��õ�һ���µģ���¼��+1����������
���Ƚ��������е�һ��Ԫ�ص����������У�Ȼ��ӵڶ���Ԫ�ؿ�ʼ����������в��룬ֱ��������������Ϊֹ
*/
/************************************************************************/

/*ֱ�ӵĲ�������
���ڱ���ʼ�Ӻ���ǰ�Ƚ�
*/
void directInsertSort(int a[], int len)
{
	for (int i = 1; i < len; i++)
	{
		if (a[i] < a[i-1]) // �ڱ�ǰһ��Ԫ�ر��ڱ�������к��Ʋ���
		{
			int tmp = a[i]; // �ݴ浱ǰ�ڱ�ֵ
			int index = i - 1; // �ݴ浱ǰ�ڱ�ǰһ��Ԫ�ص�ֵ
			a[i] = a[i-1]; // ����һλ��ǰ�ڱ�ֵ��ǰһ��Ԫ��

			while (a[index] > tmp)  // ����ǰ�ڱ�ֵǰ��������Ԫ�ر��ڱ�ֵ�����ڱ�ֵǰ�����еĽϴ�Ԫ������ѭ������
			{
				a[index + 1] = a[index];
				index--;
			}
			a[index + 1] = tmp; // ��ǰ�ڱ�ֵ�������Ϊֹ��ʹ��ǰ�ڱ�ֵǰһ��Ԫ�ظպò�������ֵ
 		}
		myPrint(a, len, i);
	}
}

/*
ͨ�õĲ�������
ֱ�Ӳ���������dk = 1;
*/
void shellInsertSort(int a[], int len, int dk)
{
	for (int i = dk; i < len; i++)
	{
		if (a[i] < a[i-dk]) // �ڱ�ǰdk�����Ԫ�ر��ڱ�������к��Ʋ���
		{
			int tmp = a[i];  // �ݴ浱ǰ�ڱ�ֵ
			int index = i - dk; // �ݴ浱ǰ�ڱ�ǰdk�����Ԫ�ص�ֵ
			a[i] = a[i-dk]; // ����dkλ��ǰ�ڱ�ֵ��ǰdk�����Ԫ��

			while (a[index] > tmp) // ����ǰ�ڱ�ֵǰ��������Ϊdk������Ԫ�ر��ڱ�ֵ�����ڱ�ֵǰ�����еĽϴ�Ԫ������ѭ������
			{
				a[index + dk] = a[index];
				index -= dk;
			}
			a[index + dk] = tmp; // ��ǰ�ڱ�ֵ�������Ϊֹ��ʹ��ǰ�ڱ�ֵǰdk�����Ԫ�ظպò�������ֵ
		}
	}
}

/*
ϣ������
����������ֱ�Ӳ�������ֱ������Ϊ1
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
/* �鲢����
�ȵݹ����в�ɶ���������У�ֱ��ÿ��������һ��Ԫ�أ�Ȼ���ٺϲ���������
*/
/************************************************************************/

//�ϲ�������������a[len_a]��b[len_b]��������������res[]��
void commonMergeSortedSequence(int a[], int len_a, int b[], int len_b, int res[])
{
	int index = 0;
	int i = 0;
	int j = 0;

	while (i < len_a && j < len_b)
	{
		if (a[i] < b[j]) //����д����С��aԪ��
		{
			res[index++] = a[i++];
		}
		else          //����д����С��bԪ��
		{
			res[index++] = b[j++];
		}
	}

	while (i < len_a) // ����д���ʣ���aԪ��
	{
		res[index++] = a[i++];
	}

	while (j < len_b) // ����д���ʣ���bԪ��
	{
		res[index++] = b[j++];
	}	
}

/*
�鲢����
*/
//�ϲ���������a[left, mid)�� a[mid, right)��������������res[]��,��ʼ��left = 0, right = len-1
void mergeArray(int a[], int left, int mid, int right, int res[])
{
	int i = left; // i ��[left,mid]����mid
	int j = mid+1;  // j ��[mid+1,right]����right
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

	// ���ϲ����res[]����a[left,right),����a[]�����Ա�����ݹ�ʹ��
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
		mergeSort(a, left, mid, res); // �ݹ�鲢������ߵ���������
		mergeSort(a, mid+1, right, res); //�ݹ� �鲢�����ұߵ���������
		mergeArray(a, left, mid, right, res); // �ϲ��������ߺ��ұ���������
	}
}

/************************************************************************/
/* ��������
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
	int *countArray = new int[maxValue+1]; //  ��������
	int i = 0;

	for (i = 0; i < maxValue+1; i++)
	{
		countArray[i] = 0;    // ��ʼ����������Ϊ0
	}

	for (i = 0; i < len; i++)
	{
		countArray[a[i]]++; // ����a[]��ÿ��Ԫ�صĸ�������������飬������ΪԪ��ֵ
	}

	for (i = 1; i < maxValue+1; i++)
	{
		countArray[i] += countArray[i - 1]; // �ۼӼ������飬���ռ��������б��治С��Ԫ��ֵ�ļ���������������ȻΪԪ��ֵ
	}

	for (i = 0; i < len; i++)
	{
		int element = a[i]; // ��ǰ������Ԫ��a[i]ֵ
		int sortIndex = countArray[element] - 1; // ��ǰԪ��a[i]��������������������е�λ������
		res[sortIndex] = element; // ����ǰԪ��a[i]����������������������е���Ӧλ����
		countArray[element]--;  // ÿ�η���һ���󣬸�����һ����֮
		myPrint(a, len, sortIndex);
	}

	delete []countArray;
}