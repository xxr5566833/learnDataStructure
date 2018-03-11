#include "stdafx.h"

int p[] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};

int r[10000] = {0};

//ÏÞÖÆlength<=10
void maxvalue(int length)
{
	for(int i = 1 ; i <= length ; i++)
	{
		int max = p[i];
		for(int j = 1 ; j <= length / 2 ; j++)
		{
			int max2 = r[j] + r[i - j];
			if(max2 > max)
			{
				max = max2;
			}
		}
		r[i] = max;
	}
}

int maxvalue2(int length)
{
	if(r[length])
		return r[length];
	int max = p[length];
	for(int i = 1 ; i <= length ; i ++)
	{
		int max2 = p[i] + maxvalue2(length - i);
		if(max2 > max)
		{
			max = max2;
		}
	}
	r[length] = max;
	return max;
}

char result[50] = {0};
int maxlength = 0;
int record[100][100] = {0};
void findMaxLength(char a[], int asize, char b[], int bsize)
{
	for(int i = 0 ; i < asize ; i++)
	{
		for(int j = 0 ; j < bsize ; j++)
		{
			if(a[i] == b[j])
			{
				record[i + 1][j + 1] = record[i][j] + 1;
				
			}
			else{
				int temp1 = record[i][j + 1];
				int temp2 = record[i + 1][j];
				record[i + 1][j + 1] = temp1 > temp2 ? temp1 : temp2;
			}
		}
	}
}

/*int main(int argc, char *argv[])
{
	int length;
	std::cin >> length;
	maxvalue2(length);
	std::cout << maxvalue2(length) << std::endl;

	return 0;
}*/