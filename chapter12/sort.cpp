#include "stdafx.h"


//ʹ�������н���ʱ�������������������ͬһ���������ڽ�������Ԫ��ʱ��Ϊע�⣩����ô�����������0

//���޸���һ��partition����������ָ��i֮ǰ��Ԫ�ض�С��key��ָ��j֮���Ԫ�ض�����key������right��i��Ԫ�ػ�һ�¼���
//֮ǰ��partition������ʱ�������õĽ���
//�ڿ�����󣬷��ֿ�����ԭ����partition�����Ľ�����һ�����ϸ��жϣ���������������±�һ������ô�Ͳ�������
void quickSort(int a[], int left, int right)
{
	//�������������Ҫ���a�Ƿ�Ϊnull
	if(!a)
		return ;
	if(left >= right)
		return ;
	//�����������keyӦ���Ǵ����������ȡ��һ����һ�������һ��
	std::default_random_engine e;
	std::uniform_int_distribution<unsigned> u(left, right);
	int randomindex = u(e);
	int key = a[randomindex];
	a[randomindex] = a[right];
	a[right] = key;
	//���� i��jӦ����left������
	int i = left - 1;
	int j = right;
	//���� j���right - 1��right���������һ����Чλ�õ�ָ��
	while(i < j)
	{
		//��ʱ�㷨�Ĳ���������[0, i)һ�� <key ��(j, n)һ�����ڵ���key
		//��ô���i == jʱ��a[i]һ����һ��������ڵ���key��Ԫ�أ����Ժ���ֱ����iλ�õ�Ԫ�������һ��Ԫ��������
		//����ʦ���㷨�Ĳ�������ĶԷ����㷨������
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
		//��ʱi��Ӧ�˴���key�����֣�j��Ӧ��С��key������
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
		//�˴�����Ҫ���϶�a[i]�ļ�飬��Ϊ��һ����֤a��ÿ��Ԫ�ض��ڷ�Χ��
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

//���԰ѱ�־λ����forѭ����
//!!ԭ��ÿһ�˶���0 �� size - 1ɨ�裬����ʵ���ϣ�ÿһ��ɨ�趼����Ǹ�����Ԫ�ط������һ��λ�ã����������Ĳ����!!
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
//�������ϴ���ôд����д��һ�飬����֮ǰ���뷨�ã�
//�ڶ���дʱ����ֱ�Ӱ������ɲ�������дȥ�ˣ���ʵ���ϺͲ�������ͬ
//��Ϊ�����Ǻϲ������Ѿ��ź�������飬����ÿһ��ֻ��Ҫ�Ƚ����������ͷ���ɣ�����Ҫ��֮ǰ��ȫ���Ƚ�
//������һ�£�֮ǰ�Ĳ��������Ȼ����Ҫ����Ϊa�������ź���ģ�������ȫ����Ҫ��a��������ұ߿�ʼ�Ƚϣ�a��������ұ�һ����a�����ͷԪ��Ҫ��

//һ�ܺ��ٿ��������ø����ռ�ɣ���Ȼ����㷨�ĸ��ӶȾ͵�O(n2)��
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

//ѡ��������ÿһ�ζ�ѡ�� [i, size - 1]��������С���Ǹ�Ԫ�أ�������i����Ԫ�ؽ���
//�Ͳ�������Ĳ�֮ͬ�����ڣ���������ÿһ��ѭ������֤[0, i]���źõģ���ѡ�������Ǳ�֤[0, i]һ�������������ǰiС��Ԫ��
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
		//ÿһ�ζ���֤[0,i]���źõ�
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
//����֮ǰд��insertSort���Ա�һ�£���Ȼ������С��
//֮ǰ1.�����������¿��ٿռ�

//��������ݹ��
//ֻ��Ҫ֪����ǰ��Ҫ���������ҽ缴��
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

//�����Ƕ�������ظ������������ݽṹ
//���׽ڵ�����Ϊ�˷�ֹ���᷵��-1����������ʹ����������д��
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
//����д��һ�鷢�֣�����ԭ���Ĵ���һģһ������������˵��һ��˼���Ǻ���Ҫ�ģ�Ҳ�Ǻ��Ѹı��
//��һ��Ҫô��ԣ�������ͱ�����ܶ�ܶ����ܸĹ��������Բ�ҪС�������������˼ά
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
//��������ֻ��Ҫ��ÿһ����Ҷ�ӽ��������ά��һ�¼���
void buildMaxHeap(int a[], int heapsize)
{
	for(int i = (heapsize >> 1) - 1 ; i >= 0 ; i --)
	{
		maxHeapify(a, heapsize, i);
	}
}
//�������������maxheapify���̣���ÿһ�ε����ֵ�������
//exchange�Ͳ���Ҫ����һ��������
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