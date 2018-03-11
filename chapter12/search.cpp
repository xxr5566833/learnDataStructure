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
	//经常忘了写这里，思路要清晰，什么时候找到了，什么时候没找到
	return false;
}

