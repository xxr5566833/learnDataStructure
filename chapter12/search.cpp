#include "stdafx.h"

bool binarySearch(int a[], int size, int key)
{
	int left = 0;
	int right = size - 1;
	while(left <= right)
	{
		int mid = (left + mid) / 2;
		if(a[mid] == key)
		{
			return true;
		}
		else{
			a[mid] > key ? right = mid - 1 : left = mid + 1;
		}
	}
	//��������д���˼·Ҫ������ʲôʱ���ҵ��ˣ�ʲôʱ��û�ҵ�
	return false;
}

