#include "stdafx.h"


//使用异或进行交换时，如果两个被交换的是同一个变量（在交换数组元素时尤为注意），那么这个变量会变成0

//又修改了一下partition函数，现在指针i之前的元素都小于key，指针j之后的元素都大于key，最后把right和i的元素换一下即可
//之前的partition函数有时会做无用的交换
//在看了书后，发现可以在原来的partition方法的交换那一步加上个判断，如果交换的两个下标一样，那么就不交换了
void quickSort(int a[], int left, int right)
{
	//正规的做法还需要检查a是否为null
	if(!a)
		return ;
	if(left >= right)
		return ;
	//正规的做法，key应该是从数组中随机取的一个不一定是最后一个
	std::default_random_engine e;
	std::uniform_int_distribution<unsigned> u(left, right);
	int randomindex = u(e);
	int key = a[randomindex];
	a[randomindex] = a[right];
	a[right] = key;
	//错误： i和j应该由left决定！
	int i = left - 1;
	int j = right;
	//错误： j最大到right - 1，right这里是最后一个有效位置的指针
	while(i < j)
	{
		//此时算法的不变性满足[0, i)一定 <key 而(j, n)一定大于等于key
		//那么最后i == j时，a[i]一定是一个满足大于等于key的元素，所以后面直接拿i位置的元素与最后一个元素做交换
		//邓老师的算法的不变性真的对分析算法很有用
		while(i < j )
		{
			i++;
			if(a[i] >= key)
				break;
		}
		while(i < j)
		{
			j--;
			if(a[j] < key)	
				break;
		}
		//此时i对应了大于key的数字，j对应了小于key的数字
		if(i  < j)
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	a[right] = a[i];
	a[i] = key;
	quickSort(a, left, i - 1);
	quickSort(a, i + 1, right);
}


void countSort(int a[], int size, int range)
{
	int count[50] = {0};
	for(int i = 0 ; i < range ; i++)
	{
		count[i] = 0;
	}
	for(int i = 0 ; i < size ; i ++)
	{
		//此处还需要加上对a[i]的检查，因为不一定保证a中每个元素都在范围内
		count[a[i]] += 1;
	}
	for(int i = 1 ; i < size ; i++)
	{
		count[i] = count[i] + count[i - 1];
	}
	int b[50] = {0};
	for(int i = 0 ; i < size ; i++)
	{
		b[count[a[i]] - 1] = a[i];
		count[a[i]] = count[a[i]] - 1;
	}
	for(int i = 0 ; i < 13 ; i++)
	{
		std::cout << b[i] << std::endl;
	}

}

//可以把标志位放在for循环里
//!!原来每一趟都从0 到 size - 1扫描，可是实际上，每一趟扫描都会把那个最大的元素放在最后一个位置！，还是理解的不够深啊!!
void bubbleSort(int a[], int size)
{
	for(bool sorted = false ; sorted = ! sorted ; size--)
	{
		for(int i = 0 ; i < size - 1 ; i++)
		{
			if(a[i] > a[i + 1])
			{
				int temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = a[i];
				sorted = false;
			}
		}
	}
}

/*void merge(int a[], int left, int right)
{
	int mid = (left + right) / 2;
	int j = mid;
	while(j <= right)
	{
		int key = a[j];
		int i = j - 1;
		while(i >= left && a[i] > key)
		{
			a[i + 1] = a[i];
			i --;
		}
		a[i + 1] = key;
		j++;

	}
}*/
//在忘记上次怎么写后又写了一遍，发现之前的想法好，
//第二次写时，就直接把它当成插入排序写去了，但实际上和插入排序不同
//因为这里是合并两个已经排好序的数组，所以每一次只需要比较两个数组的头即可，不需要和之前的全部比较
//又想了一下，之前的插入排序果然不需要，因为a数组是排好序的，所以完全不需要从a数组的最右边开始比较，a数组的最右边一定比a数组的头元素要大

//一周后再看：还是用辅助空间吧，不然这个算法的复杂度就到O(n2)了
void merge(int a[], int left, int right)
{
	int mid = (left + right) / 2;
	int i = left;
	int j = mid + 1;
	while(i < j && j <= right)
	{
		int key1 = a[i];
		int key2 = a[j];
		if(key1 > key2){
			for(int k = j ; k > i ; k --)
				a[k] = a[k -1];
			a[i] = key2;
			j++;
		}
		i++;
	}
	
}

void mergeSort(int a[], int left, int right)
{
	if(left < right){
		int mid = (left + right) / 2;
		mergeSort(a, left, mid);
		mergeSort(a, mid+1, right);
		merge(a, left, right);
	}
}

//选择排序是每一次都选择 [i, size - 1]区间内最小的那个元素，让它和i处的元素交换
//和插入排序的不同之处在于，插入排序每一次循环都保证[0, i]是排好的，而选择排序是保证[0, i]一定是整个数组的前i小的元素
void selectSort(int a[], int size)
{
	if(size <= 1 || !a)
		return ;
	for(int i = 0 ; i < size - 1 ; i++)
	{
		int minindex = i;
		int min = a[i];
		for(int j = i + 1 ; j < size ; j++)
		{
			if(a[j] < min)
			{
				minindex = j;
				min = a[j];
			}
		}
		if(minindex != i)
		{
			int temp = a[i];
			a[i] = a[minindex];
			a[minindex] = temp;
		}

	}
}


void insertSort(int a[], int size)
{
	for(int i = 1; i < size ; i++)
	{
		//每一次都保证[0,i]是排好的
		int key = a[i];
		int j = i - 1;
		while(j >= 0 && a[j] > key)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}
//这是之前写的insertSort，对比一下，果然进步不小啊
//之前1.总是想着重新开辟空间

//插入排序递归版
//只需要知道当前需要排序的最大右界即可
void insertSortRecursion(int a[], int right)
{
	if(right <= 0 || !a)
		return ;
	insertSortRecursion(a, right - 1);
	int key = a[right];
	int j = right - 1;
	while(j >= 0 && a[j] > key)
	{
		a[j + 1] = a[j];
		j--;
	}
	a[j + 1] = key;
}

void selectSortRecursion(int a[],int left, int right)
{
	if(!a || right <= 0 || left >= right)
		return ;
	int min = a[left];
	int minindex = left;
	for(int i = left + 1 ; i <= right ; i++)
	{
		if(min > a[i])
		{
			min = a[i];
			minindex = i;
		}
	}
	a[minindex] = a[left];
	a[left] = min;
	selectSortRecursion(a, left + 1, right);
}

//下面是堆排序及相关辅助方法和数据结构
//父亲节点这里为了防止不会返回-1，所以这里使用了这样的写法
inline int parent(int i)
{
	return (i + 1) >> 1 < 1 ? 0 : ((i + 1) >> 1) - 1;
}

inline int left(int i)
{
	return ((i + 1) << 1) - 1;
}

inline int right(int i)
{
	return (i + 1) << 1;
}
//重新写了一遍发现，和我原来的代码一模一样几乎，所以说第一遍思考是很重要的，也是很难改变的
//第一遍要么想对，如果想错就必须想很多很多遍才能改过来，所以不要小看你曾经犯错的思维
void maxHeapify(int a[], int heapsize, int index)
{
	while(1)
	{
		int leftindex = left(index);
		int rightindex = right(index);
		int rootvalue = a[index];
		int maxvalue = rootvalue;
		int maxindex = index;
		if(leftindex < heapsize && a[leftindex] >= a[index])
		{
			maxindex = leftindex;
			maxvalue = a[leftindex];
		}
		if(rightindex < heapsize && a[rightindex] >= a[index])
		{
			maxindex = rightindex;
			maxvalue = a[rightindex];
		}
		if(maxindex != index)
		{
			a[maxindex] = a[maxindex] ^ a[index];
			a[index] = a[maxindex] ^ a[index];
			a[maxindex] = a[maxindex] ^ a[index];
			index = maxindex;
		}
		else{
			break;
		}
	
	}
}
//记起来了只需要把每一个非叶子结点用最大堆维护一下即可
void buildMaxHeap(int a[], int heapsize)
{
	for(int i = (heapsize >> 1) - 1 ; i >= 0 ; i --)
	{
		maxHeapify(a, heapsize, i);
	}
}
//堆排序就是利用maxheapify过程，把每一次的最大值放在最后
//exchange就不需要另外一个数组了
void heapsort(int a[], int size)
{
	buildMaxHeap(a, size);
	for(int i = size - 1; i >= 1 ; i--)
	{
		a[0] = a[0] ^ a[i];
		a[i] = a[0] ^ a[i];
		a[0] = a[0] ^ a[i];
		maxHeapify(a, i, 0);
	}
}



/*int main(int argc, char* argv[])
{
	
	int a[] = {8, 7, 6, 5, 4, 3, 2, 1};
	bubbleSort(a, 8);
	for(int i = 0 ; i < 8 ; i++)
	{
		std::cout << a[i] << std::endl;
	}
	return 0;
}*/