// sortDemo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include "tree.h"
#include "graph.h"
#include "cycle.h"


void printArr(int arr[], int size) {
	if (nullptr == arr || size <= 0) {
		return;
	}
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int min(int x, int y) {
	return x < y ? x : y;
}

/************************************************************************/
/* 冒泡排序                                                                     */
/************************************************************************/
void bubbleSort(int arr[], int size) {
	if (nullptr == arr || size < 2) {
		return;
	}
	int tmp = 0;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (arr[j] > arr[j + 1]) {
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

/************************************************************************/
/* 选择排序                                                                     */
/************************************************************************/
void selectSort(int arr[], int size) {
	if (nullptr == arr || size < 2) {
		return;
	}
	for (int i = 0; i < size-1; i++) {
		//找最小元素
		int min = i;
		for (int j = i+1; j < size; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		//交换
		int tmp = arr[i];
		arr[i] = arr[min];
		arr[min] = tmp;
	}
}

/************************************************************************/
/* 插入排序                                                                     */
/************************************************************************/
void insertSort(int arr[], int size) {
	if (nullptr == arr || size < 2) {
		return;
	}
	int i, j, current;
	i = j = current = 0;
	for (i = 1; i < size; i++) {
		current = arr[i];
		j = i - 1; //当前数据的索引是i，已有的有序数组的索引是[0, i-1]
		while ((j>=0) && (arr[j] > current)){
			//从有序数组的最大索引开始比较，比当前current大的数据，往后挪一位
			arr[j + 1] = arr[j];
			j--;
		}
		//直到找到正确的位置，把当前值current插入
		arr[j + 1] = current;
	}
}

/************************************************************************/
/* 希尔排序                                                                     */
/************************************************************************/
void shellSort(int arr[], int size) {
	if (nullptr == arr || size < 2){
		return;
	}
	int current = 0;
	for (int gap = size >> 1; gap >= 1; gap >>= 1) {
		for (int i = gap; i < size; i++) {
			current = arr[i];
			int j = i - gap;
			while ((j >= 0) && (arr[j] > current)) {
				arr[j + gap] = arr[j];
				j -= gap;
			}
			arr[j + gap] = current;
		}
	}
}

/************************************************************************/
/* 归并排序（有问题）                                                                     */
/************************************************************************/
//void mergeSort(int arr[], int len){
//	int *a = arr;
//	int *b = (int*)malloc(len * sizeof(int));
//	memset(b, NULL, len * sizeof(int));
//	int seg, start;
//	for (seg = 1; seg < len; seg += seg) {
//		for (start = 0; start < len; start += seg * 2) {
//			int low = start, mid = min(start + seg, len), high = min(start + seg, len);
//			int k = low;
//			int start1 = low, end1 = mid;
//			int start2 = mid, end2 = high;
//			while (start1 < end1 && start2 < end2)
//				b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
//			while (start1 < end1)
//				b[k++] = a[start1++];
//			while (start2 < end2)
//				b[k++] = a[start2++];
//		}
//		int *temp = a;
//		a = b;
//		b = temp;
//	}
//	if (a != arr) {
//		for (int i = 0; i < len; i++) {
//			b[i] = a[i];
//		}
//		b = a;
//	}
//	free(b);
//}
/************************************************************************/
/* 归并排序（递归法）                                                                     */
/************************************************************************/
int* _merge(int left[], int leftSize, int right[], int rightSize, int& resSize) {
	int* res = new int[leftSize + rightSize];
	memset(res, 0, sizeof(int)*(leftSize + rightSize));
	int index = 0;
	int leftIndex, rightIndex;
	leftIndex = rightIndex = 0;
	for (int i = 0; i < leftSize&& i < rightSize; i++) {
		if (left[i] < right[i]) {
			res[index++] = left[i];
			leftIndex++;
		}else {
			res[index++] = right[i];
			rightIndex++;
		}
	}
	//左侧剩余数据
	for (int j = leftIndex; j < leftSize; j++)
	{
		res[index++] = left[j];
	}
	//右侧剩余数据
	for (int j = rightIndex; j < rightSize; j++)
	{
		res[index++] = right[j];
	}
	//返回合并后的数组和个数
	resSize = index;
	return res;
}
int* _mergeSort(int arr[], int size, int& retSize) {
	if (nullptr == arr ) {
		return nullptr;
	}
	if (size < 2)
	{
		int* ret = new int[size];
		memcpy(ret, arr, size * sizeof(int));
		retSize = size;
		return ret;
	}
	int mid = size / 2;
	int leftSize, rightSize;
	leftSize = rightSize = 0;
	int* left = _mergeSort(arr, mid, leftSize);
	int* right = _mergeSort(arr + mid, size - mid, rightSize);
	int resSize = 0;
	int* res = _merge(left, leftSize, right, rightSize, resSize);
	if (nullptr != left)
	{
		delete[] left;
	}
	if (nullptr != right)
	{
		delete[] right;
	}
	retSize = resSize;
	return res;
}
void mergeSort(int arr[], int size)
{
	if (nullptr == arr || size < 2)
	{
		return;
	}
	int retSize = 0;
	int* ret = _mergeSort(arr, size, retSize);
	if (nullptr != ret || retSize == size)
	{
		for (int i=0; i<retSize; i++)
		{
			arr[i] = ret[i];
		}
		delete[] ret;
	}
}

/************************************************************************/
/* 快速排序                                                                     */
/************************************************************************/
int _partition(int arr[], int low, int high) {
	int pivot = arr[low];
	while (low < high) {
		//当队尾的元素大于等于基准数据时，向前挪动high指针
		while (low < high && arr[high] >= pivot) {
			--high;
		}
		//如果队尾元素小于pivot，需要将其赋值给low
		arr[low] = arr[high];
		//当队首元素小于等于pivot时，向前挪动low指针
		while (low < high && arr[low] <= pivot) {
			++low;
		}
		//当队首元素大于pivot时，需要将其赋值给high
		arr[high] = arr[low];
	}
	//跳出循环是low=high，此时的low或high就是pivot的正确索引位置，
	//需要把pivot赋值给arr[low]
	arr[low] = pivot;
	return low;
}
void _qSort(int arr[], int low, int high) {
	if (low < high) {
		int pivot = _partition(arr, low, high);
		_qSort(arr, low, pivot - 1);
		_qSort(arr, pivot + 1, high);
	}
}
void quickSort(int arr[], int size) {
	if (nullptr == arr || size < 2) {
		return;
	}
	_qSort(arr, 0, size - 1);
}

/************************************************************************/
/* 计数排序                                                                     */
/************************************************************************/
int _getMaxValue(int arr[], int size) {
	int max = arr[0];
	for (int i=1; i<size; i++)
	{
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}
void countSort(int arr[], int size) {
	if (nullptr == arr || size < 2) {
		return;
	}
	int max = _getMaxValue(arr, size);
	int bucketsNum = max + 1;
	int *buckets = (int*)malloc(bucketsNum * sizeof(int));
	memset(buckets, 0, bucketsNum * sizeof(int));
	for (int i = 0; i < size; i++) {
		buckets[arr[i]] += 1;
	}
	int index = 0;
	for (int j = 0; j < bucketsNum; j++) {
		for (; buckets[j] > 0; buckets[j]--) {
			arr[index++] = j;
		}
	}
	free(buckets);
	buckets = nullptr;
}

/************************************************************************/
/* 桶排序                                                                     */
/************************************************************************/
typedef struct {
	int* pData;
	int c; //当前位置
	int size; //当前元素个数
	int len; //缓冲区大小
}BucketItem;
void bucketSort(int arr[], int size, int bucketSize) {
	if (nullptr == arr || size < 2) {
		return;
	}
	int min, max;
	min = max = arr[0];
	//获取数列的最小值、最大值
	for (int i = 0; i < size; i++) {
		if (arr[i] < min)
		{
			min = arr[i];
		}
		else if (arr[i] > max) {
			max = arr[i];
		}
	}
	int bucketNum = (max - min) / bucketSize + 1;
	BucketItem* buckets = (BucketItem*)malloc(bucketNum * sizeof(BucketItem));
	for (int i = 0; i < bucketNum; i++) {
		buckets[i].pData = (int*)malloc(bucketSize * sizeof(int));
		memset(buckets[i].pData, 0, bucketSize * sizeof(int));
		buckets[i].c = 0;
		buckets[i].size = 0;
		buckets[i].len = bucketSize;
	}
	for (int i = 0; i < size; i++) {
		int id = (arr[i] - min) / bucketSize;
		if (id<bucketNum)
		{
			buckets[id].pData[buckets[id].c++] = arr[i];
			buckets[id].size++;
		}
	}
	int index = 0;
	for (int i = 0; i < bucketNum; i++) {
		if (0 == buckets[i].size) {
			continue;
		}
		insertSort(buckets[i].pData, buckets[i].size);
		for (int j = 0; j < buckets[i].size; j++) {
			arr[index++] = buckets[i].pData[j];
		}
		free(buckets[i].pData);
	}
	free(buckets);
}

/************************************************************************/
/* 基数排序                                                                     */
/************************************************************************/
int _maxBit(int arr[], int size) {
	int max = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	int d = 1;
	int p = 10;
	while (max >= p) {
		max /= 10;
		++d;
	}
	return d;
}
void radixSort(int arr[], int size) {
	if (nullptr == arr || size < 2) {
		return;
	}
	int d = _maxBit(arr, size);
	int radix = 1;
	int mod = 10;
	for (int i = 1; i <= d; i++)
	{
		BucketItem* buckets = (BucketItem*)malloc(10 * sizeof(BucketItem));
		memset(buckets, 0, 10 * sizeof(BucketItem));
		//分配空间
		for (int a = 0; a < 10; a++)
		{
			buckets[a].pData = (int*)malloc(size * sizeof(int));
			buckets[a].len = size;
			buckets[a].c = buckets[a].size = 0;
		}
		for (int j = 0; j < size; j++) 
		{
			int k = arr[j] / radix % 10;
			buckets[k].pData[buckets[k].c++] = arr[j];
			buckets[k].size++;
		}
		radix *= 10;
		int* tmpRes = new int[size];
		memset(tmpRes, 0, size * sizeof(int));
		int tmpIndex = 0;
		for (int p = 0; p < 10; p++)
		{
			for (int q = 0; q < buckets[p].size; q++)
			{
				tmpRes[tmpIndex++] = buckets[p].pData[q];
			}
		}
		for (int i = 0; i < size; i++)
		{
			arr[i] = tmpRes[i];
		}
		free(tmpRes);
		tmpRes = nullptr;
		for (int i = 0; i < 10; i++)
		{
			free(buckets[i].pData);
		}
		free(buckets);
	}

}

/************************************************************************/
/* 堆排序                                                                     */
/************************************************************************/
void _swap(int* a, int* b)
{
	if (nullptr == a || nullptr == b)
	{
		return;
	}
	int tmp = *b;
	*b = *a;
	*a = tmp;
}
//堆化函数
void _heapify(int arr[], int size, int index)
{
	if (nullptr == arr || size < 2 || index >= size)
	{
		return;
	}
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	int largest = index;
	if (left < size && arr[left]>arr[largest])
	{
		largest = left;
	}
	if (right<size && arr[right]>arr[largest])
	{
		largest = right;
	}
	if (largest != index)
	{
		_swap(&arr[index], &arr[largest]);
		_heapify(arr, size, largest);
	}
}
void _buildMaxHeaper(int arr[], int size)
{
	for (int i = size / 2; i >= 0; i--)
	{
		_heapify(arr, size, i);
	}
}
void heapSort(int arr[], int size)
{
	if (nullptr == arr || size < 2)
	{
		return;
	}
	//构建最大堆，最大堆构建完成后，第0个元素就是待排序数组中的最大元素
	_buildMaxHeaper(arr, size);
	for (int i=size-1; i>=0; i--)
	{
		//每次都进行第0号（最大），第n-1号（元素）元素进行交换
		_swap(&arr[0], &arr[i]);
		//交换后，把剩下的堆0~（n-1-i）进行调整，（由于最后一个元素已经有序，所有需要减1个）
		size--;
		_heapify(arr, size, 0);
	}
}

//void _maxheapify(int arr[], int start, int end)
//{
//	//建立父节点指标和子节点指标
//	int dad = start;
//	int son = dad * 2 + 1;
//	while (son <= end)
//	{
//		//先比较两个子节点大小，选择最大的
//		if (son + 1 <= end && arr[son] < arr[son + 1])
//		{
//			son++;
//		}
//		//如果父节点大于子节点代表调整完毕，直接跳出函数
//		if (arr[dad] > arr[son])
//		{
//			return;
//		}
//		else
//		{
//			//否则交换父子内容再继续子节点和顺节点比较
//			_swap(&arr[dad], &arr[son]);
//			dad = son;
//			son = dad * 2 + 1;
//		}
//	}
//}
//void heapSort(int arr[], int size)
//{
//	if (nullptr == arr || size < 2)
//	{
//		return;
//	}
//	//初始化，i从最后一个父节点开始调整
//	for (int i=size/2-1; i>=0; i--)
//	{
//		_maxheapify(arr, i, size - 1);
//	}
//	//先将第一个元素和已经排好元素的前一位做交换，再从新调整，直到排序完毕
//	for (int i=size-1; i>0; i--)
//	{
//		_swap(&arr[0], &arr[i]);
//		_maxheapify(arr, 0, i - 1);
//	}
//}





int main() {
	int arr[] = { 43, 34, 656, 767, 323, 3, 545, 76, 11, 434, 776, 4343, 54, 432 };
	int size = sizeof(arr) / sizeof(int);
	std::cout << "sort before:" << std::endl;
	printArr(arr, size);
	//mergeSort(arr, size);
	//bubbleSort(arr, size);
	//selectSort(arr, size);
	//insertSort(arr, size);
	//shellSort(arr, size);
	//quickSort(arr, size);
	//countSort(arr, size);
	//bucketSort(arr, size, 5);
	//radixSort(arr, size);
	//heapSort(arr, size);
	//mergeSort(arr, size);

	MGraph g;
	createGraphNew(g, false);
	bool hasCycle = checkCycleFrTopo(&g); //checkCycleFrDfs(&g);
	std::cout << "图是否有环：" << hasCycle << std::endl;

	GraphAdjList ga;
	createALGraph(&ga, true);
	bool hasCycle = criticalPath(&ga); // checkCycleFrDGraph(&ga);

	std::cout << "有向图是否有环：" << hasCycle << std::endl;

	/*std::cout << "sort after:" << std::endl;
	printArr(arr, size);

	std::cout << "输入字符创建二叉树" << std::endl;
	BiTree t = nullptr;
	createBiTree(t);

	std::cout << "二叉树前序遍历：" << std::endl;
	preOrderTraverse(t);
	std::cout << std::endl;
	
	std::cout << "二叉树中序遍历：" << std::endl;
	inOrderTraverse(t);
	std::cout << std::endl;

	std::cout << "二叉树后序遍历：" << std::endl;
	postOrderTraverse(t);
	std::cout << std::endl;

	destroyBiTree(t);*/
	system("pause");
	return 0;
}

